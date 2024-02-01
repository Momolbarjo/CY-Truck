#!/bin/bash

debut=$(date +%s)

fichier=$1
fichierdeSortie="temp/tmp_l.csv"

LC_NUMERIC=C awk -F';' 'NR>1{
    id = $1
    nb_km = $5
    id_km[id] += nb_km
    } END {
    for (id in id_km) {
        printf "%s;%f\n", id, id_km[id]
    }
}' $fichier |sort -t';' -k2,2nr -g | head -n 10 |sort -t';' -k1,1nr > "$fichierdeSortie" 

gnuplot <<- EOF
    reset
    set terminal pngcairo size 1280,720
    set output 'images/l.png'
    set datafile separator ';'
    set title "Option -l : Distance = f(Route)" 
    set style data histogram
    set boxwidth 0.7
    set style fill solid
    set yrange [ 0 : * ]
    set xtics  font ",9"
    set ytics font ",9"
    set ylabel "DISTANCE (Km)" font ",10"
    set xlabel "ROUTE ID" font ",10"
    set term png  size 1280,720
    plot 'temp/tmp_l.csv' using 2:xtic(1) notitle with boxes
EOF


fin=$(date +%s)
duree=$(( $fin - $debut ))
echo "Temps d'exécution : $duree secondes"
xdg-open images/l.png # ouverture du png qui contient le graphique

exit 0
