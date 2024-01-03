#!/bin/bash


debut=$(date +%s)

awk -F';' 'NR > 1 { print $3 "\0" }' data.csv > ville.txt
awk -F';' 'NR > 1 { print $4 "\0" }' data.csv > arrive.txt
awk -F';' 'NR > 1 { print $3 "\0"  }' data.csv > depart.txt

chmod 777 arrive.txt
chmod 777 depart.txt

./traitementT

rm ville.txt
rm arrive.txt
rm depart.txt


fin=$(date +%s)
duree=$(( $fin - $debut ))

echo "Temps d'exécution : $duree secondes"


exit 0
