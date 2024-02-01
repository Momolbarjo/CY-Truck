#!/bin/bash

# Mesure du temps d'éxécution
debut=$(date +%s)

# Affectations des arguments
fichier=$1
fichierdeSortie="temp/tmp_d2.csv"

# Traitement du fichier data.csv à l'aide d'un AWK
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
}' $fichier | LC_NUMERIC=C sort -t':' -k1,1nr -g | head -n 10 > "$fichierdeSortie"

# Création du graphique du traitement à l'aide de gnuplot
gnuplot <<- EOF
    reset
    set terminal pngcairo size 1000,900
    set output 'temp/tmp_d2.png'
    set datafile separator ':'
    set style data histogram
    set boxwidth 0.7
    set style fill solid
    set xtics rotate out
    set y2tics rotate out 
    set y2range [ 0 : * ]
    set ytics nomirror
    unset ytics # desactivation de l'axe y1 pour utiliser l'axe y2.
    set xtics  font ",9"
    set y2tics font ",9"
    set y2label "DISTANCE (Km)" font ",10"
    set ylabel "Option -d2 : Distance =f(Driver)" font ",10"
    set xlabel "DRIVER NAMES" rotate by 180 font ",10"
    set term png  size 900,800
    plot 'temp/tmp_d2.csv' using 1:xtic(2)  notitle with boxes axes x1y2 # graphique tracé à l'aide des axes x1 et y2.
EOF

# Conversion et ouverture du graphique
convert temp/tmp_d2.png -rotate 90 images/d2.png # rotation de 90 degrés de tmp.png pour avoir un histogramme horizontale 
xdg-open images/d2.png # ouverture du png qui contient le graphique

# Fin et affichage de la durée d'éxécution
fin=$(date +%s)
duree=$(( $fin - $debut ))
echo "Temps d'exécution : $duree secondes"

exit 0


