#!/bin/bash

start=$(date +%s)

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi


datafile=$1
outputfile="temp/d2/tmp.csv"
outputpng="temp/d2/tmp.png"

if [ -e "$outputfile" ]; then
    rm "$outputfile"
fi

if [ -e "$outputpng" ]; then
    rm "$outputpng"
fi



LC_NUMERIC=C awk -F';' 'NR>1{
    nom_prenom = $6
    valeur = $5
    if (nom_prenom in somme) {
        somme[nom_prenom] += valeur
    } else {
        somme[nom_prenom] = valeur
    }
} END {
    for (i in somme) {
        printf "%.2f : %s\n", somme[i], i 
    }
}' $datafile | LC_NUMERIC=C sort -t':' -k1,1nr -g | head -n 10 > "$outputfile"


gnuplot <<- EOF
    reset
    set terminal pngcairo size 1000,900
    set output 'temp/d2/tmp.png'
    set datafile separator ':'
    set style data histogram
    set boxwidth 0.7
    set style fill solid
    set xtics rotate out
    set y2tics rotate out 
    set y2range [ 0 : 160000 ]
    set ytics nomirror
    unset ytics
    set xtics  font ",9"
    set y2tics font ",9"
    set y2label "DISTANCE (Km)" font ",10"
    set ylabel "Option -d2 : Distance =f(Driver)" font ",10"
    set xlabel "DRIVER NAMES" rotate by 180 font ",10"
    set term png  size 900,800
    plot 'temp/d2/tmp.csv' using 1:xtic(2)  notitle with boxes axes x1y2
EOF


convert temp/d2/tmp.png -rotate 90 images/d2.png
xdg-open images/d2.png

end=$(date +%s)
runtime=$(( $end - $start ))
echo "Temps d'exécution : $runtime secondes"

exit 0
