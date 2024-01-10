#!/bin/bash

rhythmbox-client --play

cat others/ansi/truck.ansi.txt
echo "Appuyer sur une touche.." 
progc/src/./noEnter

rhythmbox-client --stop

sleep 1

LOGS=$(zenity --password --username)

nomUtilisateur=$(echo "$LOGS" | cut -d'|' -f1)
motdePasse=$(echo "$LOGS" | cut -d'|' -f2)


if [ "$nomUtilisateur" = "admin" ] && [ "$motdePasse" = "miaou" ]; then
	zenity --info --title="Connexion réussie" --text="Bienvenue, chef."
	chmod 777 main_script.sh
else
	zenity --error --title="Echec de la connexion" --text="Nom d'utilisateur et/ou mot de passe incorrecte."
	
fi

clear


exit 0


