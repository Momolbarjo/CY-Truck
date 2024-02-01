#!/bin/bash

executable_parent="progc/src"

executables=("noEnter" "main_s" "main_t")


for executable in "${executables[@]}"; do
    chemin_complet="$executable_parent/$executable"
    if [ ! -f "$chemin_complet" ]; then
        echo "L'exécutable $executable n'est pas présent. Compilation en cours..."
        
        # Compiler le code source
        make -C progc
        
        # Vérifier si la compilation s'est bien déroulée
        if [ $? -ne 0 ]; then
            echo "Erreur lors de la compilation."
            exit 1
        fi
    fi
done

if [ ! -x "$0" ]; then
   echo "Vous ne disposez pas des droits , merci de vous authentifier"
   exit 1
fi

if [ ! -d "temp" ]; then
    mkdir temp

else
    rm -rf temp/*
fi

if [ ! -d "images" ]; then
    mkdir images
fi


declare -A options

if [ "$#" -ge 2 ] && [ "$#" -lt 9 ] && [ "${1##*.}" = "csv" ]; then

    if [ ! -f "data/$1" ]; then
    	echo "Erreur : le fichier doit etre present dans le dossier data."
    	exit 1
    fi
    
    datafile=$1
    
    shift
    for opt in "$@"
    do
        if [ "$opt" = "-h" ]; then
            echo "Usage: $0 .csv parametres (-d1,-d2,-l,-s,-t,-r)"
            exit 0
        fi
        if [ "${options[$opt]}" = "true" ]; then
            echo "Erreur : L'option $opt ne peut pas être utilisée plusieurs fois."
            exit 1
        fi
        options[$opt]=true
    done

    for opt in "$@"
    do
        case $opt in
            -d1 | -d2 | -l | -s | -t)
                sh "scripts/${opt#-}.sh" "data/$datafile"
                ;;
            -r)
                chmod 000 "$0"
                ;;
            *)
                echo "Option inconnue : $opt"
                ;;
        esac
    done
else
    echo "Usage: $0 .csv parametres (max 7)"
    exit 1
fi

exit 0
