#!/bin/bash

rhythmbox-client --play

cat others/ansi/truck.ansi.txt
echo "Appuyer sur une touche.." 
sleep 1
progc/./noEnter

rhythmbox-client --quit

sleep 1

LOGS=$(zenity --password --username)

USERNAME=$(echo "$LOGS" | cut -d'|' -f1)
PASSWORD=$(echo "$LOGS" | cut -d'|' -f2)


if [ "$USERNAME" = "admin" ] && [ "$PASSWORD" = "miaou" ]; then
	zenity --info --title="Connexion réussie" --text="Bienvenue, chef."
	chmod 777 script.sh
else
	zenity --error --title="Echec de la connexion" --text="Nom d'utilisateur et/ou mot de passe incorrecte."
	
fi

clear

exit 0

