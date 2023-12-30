#!/bin/bash

if [ ! -d "temp" ]; then
    mkdir temp

else
    rm -rf temp/*
fi

if [ ! -d "images" ]; then
    mkdir images
fi

declare -A options

if [ "$#" -ge 2 ] && [ "$#" -lt 9 ] && [ "${1##*.}" = "csv" ]; then # https://www.math-linux.com/linux/bash/article/comment-extraire-le-nom-et-l-extension-d-un-fichier-en-bash

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
