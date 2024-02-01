#!/bin/bash

# Début du chronomètre du temps d'éxécution
debut=$(date +%s)

# Affectations des arguments
fichier=$1
sortie=temp/tmp_s2.csv

# Traitement de data.csv avec l'utilisation de AWK
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

# Execution du programme en C utilisant le fichier créé précédemment avec le AWK
progc/src/./main_s

# Verification du fichier de sortie
if [ ! -f $sortie ];then
	exit 1
fi

# Création du graphique du traitement effectué
gnuplot <<- EOF
    reset
    set terminal pngcairo size 1920,1080
    set output 'images/s.png'
    set datafile separator ':'
    set title "Option -s : Distance = f(Route)" 
    set yrange [ 0 : * ] 
    set xtics nomirror  rotate by -45  font ",9"
    set ytics font ",9"
    set ylabel "DISTANCE (Km)" font ",10"
    set xlabel "ROUTE ID" font ",10" 
    
    plot '$sortie' using 0:3:4  with filledcurves fc rgb "#80E0A080"title 'Distance Max/Min (Km) ', \
         "" using 5:xticlabels(1) smooth mcspline  lw 2 title 'Distance average (Km)'
                       
EOF

# Fin et affichage du chronomètre (temps d'éxécution)
fin=$(date +%s)
duree=$(( $fin - $debut ))
echo "Temps d'exécution : $duree secondes"

# Affichage du graphique
xdg-open images/s.png

exit 0
