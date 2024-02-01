#!/bin/bash

# Répertoire contenant les exécutables
executable_parent="progc/src"

# Noms des exécutables
executables=("noEnter" "main_s" "main_t")

# Vérifier la présence des exécutables et les compiler si nécessaire
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

# Vérifier si le script a les droits d'exécution
if [ ! -x "$0" ]; then
   echo "Vous ne disposez pas des droits, merci de vous authentifier"
   exit 1
fi

# Création du répertoire temporaire
if [ ! -d "temp" ]; then
    mkdir temp
else
    # Si le répertoire existe, supprimer son contenu
    rm -rf temp/*
fi

# Création du répertoire pour les images s'il n'existe pas
if [ ! -d "images" ]; then
    mkdir images
fi

# Initialiser un tableau associatif pour les options
declare -A options

# Vérifier le nombre d'arguments et le type du fichier d'entrée
if [ "$#" -ge 2 ] && [ "$#" -lt 9 ] && [ "${1##*.}" = "csv" ]; then

    if [ ! -f "data/$1" ]; then
        echo "Erreur : le fichier doit être présent dans le dossier data."
        exit 1
    fi
    
    datafile=$1
    
    shift
    # Traiter chaque option passée en paramètre
    for opt in "$@"; do
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

    # Exécuter les scripts correspondants aux options spécifiées
    for opt in "$@"; do
        case $opt in
            -d1 | -d2 | -l | -s | -t)
                sh "scripts/${opt#-}.sh" "data/$datafile"
                ;;
            -r)
                # Réduire les permissions du script
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
