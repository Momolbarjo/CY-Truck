#!/bin/bash

fichier=$1
debut=$(date +%s)

LC_NUMERIC=C awk -F';' 'NR>1 {
    id=$1; 
    distance=$5; 
    if (!(id in min_distances) || (distance < min_distances[id])){
        min_distances[id] = distance
    }
    if (!(id in max_distances) || distance > max_distances[id]){
        max_distances[id] = distance
    } 
    total_distances[id] += distance;
    counts[id]++; 
} 
END {
    for (id in counts) {
        average_distance = (counts[id] > 0) ? total_distances[id] / counts[id] : 0;
        diff_min_max = max_distances[id] - min_distances[id];
        printf "%s\t%.3f\t%.3f\t%.3f\t%.3f\n", id, min_distances[id]+0, max_distances[id]+0, diff_min_max+0, average_distance+0
    }
}' "$fichier" > "temp/tmp_s1.csv"


progc/src/./main_s

gnuplot <<- EOF
    reset
    set terminal pngcairo size 1920,1080
    set output 'images/s.png'
    set datafile separator ':'
    set title "Option -s : Distance = f(Route)" 
    set yrange [ * : * ] 
    set xtics nomirror  rotate by -45  font ",9"
    set ytics font ",9"
    set ylabel "DISTANCE (Km)" font ",10"
    set xlabel "ROUTE ID" font ",10" 
    
    plot 'temp/tmp_s2.csv' using 0:3:4  with filledcurves fc rgb "#80E0A080"title 'Distance Max/Min (Km) ', \
         "" using 5:xticlabels(1) smooth mcspline  lw 2 title 'Distance average (Km)'
         
               
EOF


fin=$(date +%s)
duree=$(( $fin - $debut ))
echo "Temps d'exécution : $duree secondes"
xdg-open images/s.png

exit 0
