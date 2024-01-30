#!/bin/bash


debut=$(date +%s)
fichier=$1

awk -F';' 'NR > 1 { print $1  }' $fichier  > "temp/id.csv"
awk -F';' 'NR > 1 { print $2  }' $fichier  > "temp/step.csv"
awk -F';' 'NR > 1 { print $3 "\0" }' $fichier  > "temp/depart.csv"
awk -F';' 'NR > 1 { print $4 "\0" }' $fichier  > "temp/arrive.csv"

chmod 777 temp/id.csv
chmod 777 temp/step.csv
chmod 777 temp/depart.csv
chmod 777 temp/depart.csv

./t


fin=$(date +%s)
duree=$(( $fin - $debut ))

echo "Temps d'exécution : $duree secondes"


exit 0
