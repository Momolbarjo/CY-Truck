#!/bin/bash


debut=$(date +%s)
fichier=$1

awk -F';' 'NR > 1 { print $3 "\0" }' $fichier > "temp/ville.txt"
awk -F';' 'NR > 1 { print $4 "\0" }' $fichier > "temp/arrive.txt"
awk -F';' 'NR > 1 { print $3 "\0"  }' $fichier  > "temp/depart.txt"

chmod 777 temp/ville.txt
chmod 777 temp/arrive.txt
chmod 777 temp/depart.txt

progc/./traitementT


fin=$(date +%s)
duree=$(( $fin - $debut ))

echo "Temps d'exécution : $duree secondes"


exit 0
