#!/bin/bash

debut=$(date +%s)
fichier=$1

awk -F';' '
function normalize(str) {
    gsub(/[[:space:]]/, "", str);
}

{
    if ($3 != "") {
        ville = normalize($3);
        depart[ville]++;
        total[ville]++;
    }
    if ($4 != "" && $4 != $3) {
        ville = normalize($4);
        total[ville]++;
    }
}
END {
    for (str in count_total) {
        printf "%s,%d,%d\n", str, total[str], depart[str];
    }
}' "$fichier" > resultat.csv

fin=$(date +%s)
duree=$(( $fin - $debut ))

echo "Temps d'exécution de AWK : $duree secondes"

exit 0
