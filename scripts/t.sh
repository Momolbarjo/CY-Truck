#!/bin/bash


debut=$(date +%s)
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
	 
	}' $fichier >"tmp_t1.csv"


fin=$(date +%s)
duree=$(( $fin - $debut ))

echo "Temps d'exécution : $duree secondes"


exit 0
