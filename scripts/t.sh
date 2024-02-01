#!/bin/bash

debut=$(date +%s)
sortie=temp/data_t1.csv
fichier=$1


awk -F';' '{
	id_trajet=$1
	id_etape=$2
	ville_depart=$3
	ville_arrivee=$4
	
	if(id_etape==1){
		depart[ville_depart]++
	}
      
        if(verif[id_trajet, ville_depart] == 0){
        	total[ville_depart]++
        	verif[id_trajet, ville_depart]++
      	}
      	
      	if(verif[id_trajet, ville_arrivee] == 0){
        	total[ville_arrivee]++
        	verif[id_trajet, ville_arrivee]++
      	}
      }
      END{
      		for(ville in total){
      			printf"%s,%d,%d\n",ville,total[ville],depart[ville]
      			 
	  }
	 
	}' $fichier >"temp/t1.csv"


progc/src/./main_t > "temp/data_t1.csv"

if [ ! -f $sortie ];then
	exit 1
fi

gnuplot <<- EOF
    reset
    set terminal pngcairo size 1280,720
    set output 'images/t.png'
    set datafile separator ';'
    set title "Option -t : Nb routes  = f(Villes)" 
    set style data histograms
    set boxwidth 1.8 
    set style fill solid 
    set yrange [ 0 : * ]
    set xtics  font ",9"
    set xtics  rotate by -45
    set ytics font ",9"
    set ylabel "NB ROUTES " font ",10"
    set xlabel " NOMS VILLES" font ",10"
    set term png  size 1280,720
    
    plot 'temp/data_t1.csv' using 2:xtic(1)  lt rgb "#406090" title 'Total routes',\
     "" using 3 lt rgb "#BDBDBD" title 'Premiere Ville '
EOF


fin=$(date +%s)
duree=$(( $fin - $debut ))

echo "Temps d'exécution : $duree secondes"
xdg-open images/t.png

exit 0
