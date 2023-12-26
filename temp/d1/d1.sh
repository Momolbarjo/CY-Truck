#!/bin/bash

start=$(date +%s)

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi


datafile=$1
outputfile="temp/d1/tmp.csv"
outputpng="temp/d1/tmp.png"

if [ -e "$outputfile" ]; then
    rm "$outputfile"
fi

if [ -e "$outputpng" ]; then
    rm "$outputpng"
fi


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
}' $datafile | sort -nr -k1,1 | head > "$outputfile"



gnuplot <<- EOF
    reset
    set terminal pngcairo size 1000,900
    set output 'temp/d1/tmp.png'
    set datafile separator ':'
    set style data histogram
    set boxwidth 0.7
    set style fill solid
    set xtics rotate out
    set y2tics rotate out 
    set y2range [ 0 : 250 ]
    set ytics nomirror
    unset ytics
    set xtics  font ",9"
    set y2tics font ",9"
    set y2label "NB ROUTES" font ",10"
    set ylabel "Option -d1 : Nb routes = f(Driver)" font ",10"
    set xlabel "DRIVER NAMES" rotate by 180 font ",10"
    set term png  size 900,800
    plot 'temp/d1/tmp.csv' using 1:xtic(2)  notitle with boxes axes x1y2
EOF


convert temp/d1/tmp.png -rotate 90 images/d1.png
xdg-open images/d1.png

end=$(date +%s)
runtime=$(( $end - $start ))
echo "Temps d'exécution : $runtime secondes"

exit 0

