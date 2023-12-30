#!/bin/bash

debut=$(date +%s)

fichier=$1
fichierdeSortie="temp/tmp_d1.csv"

awk -F';' 'NR>1{
    nom_prenom = $6
    valeur = $1
    somme[nom_prenom ":" valeur] = 1
} END {
    for (i in somme) {
        nom_prenom = substr(i, 1, index(i, ":") - 1)
        count[nom_prenom]++
    }
    for (nom_prenom in count) {
        print count[nom_prenom] " : " nom_prenom
    }
}' $fichier | sort -nr -k1,1 | head > "$fichierdeSortie"

gnuplot <<- EOF
    reset
    set terminal pngcairo size 1000,900
    set output 'temp/tmp_d1.png'
    set datafile separator ':'
    set style data histogram
    set boxwidth 0.7
    set style fill solid
    set xtics rotate out
    set y2tics rotate out 
    set y2range [ 0 : 250 ]
    set ytics nomirror
    unset ytics # desactivation de l'axe y1 pour utiliser l'axe y2.
    set xtics  font ",9"
    set y2tics font ",9"
    set y2label "NB ROUTES" font ",10"
    set ylabel "Option -d1 : Nb routes = f(Driver)" font ",10"
    set xlabel "DRIVER NAMES" rotate by 180 font ",10"
    set term png  size 900,800
    plot 'temp/tmp_d1.csv' using 1:xtic(2)  notitle with boxes axes x1y2 # graphique tracé à l'aide des axes x1 et y2.
EOF

convert temp/tmp_d1.png -rotate 90 images/d1.png # rotation de 90 degrés de tmp.png pour avoir un histogramme horizontale 
xdg-open images/d1.png # ouverture du png qui contient le graphique

fin=$(date +%s)
duree=$(( $fin - $debut ))
echo "Temps d'exécution : $duree secondes"

exit 0
