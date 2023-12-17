#!/bin/bash

rhythmbox-client --play

cat truck.ansi.txt
echo "Waiting for a key to be pressed..." 
./noEnter

rhythmbox-client --quit

////https://ostechnix.com/zenity-create-gui-dialog-boxes-in-bash-scripts///
LOGS=$(zenity --password --username)

USERNAME=$(echo "$LOGS" | cut -d'|' -f1)
PASSWORD=$(echo "$LOGS" | cut -d'|' -f2)


if [ "$USERNAME" = "admin" ] && [ "$PASSWORD" = "miaou" ]; then
	zenity --info --title="Connexion réussie" --text="Bienvenue, $USERNAME."
else
	zenity --error --title="Echec de la connexion" --text="Nom d'utilisateur et/ou mot de passe incorrecte."
	exit 0
fi

clear

echo "1.Instructions"

exit 0

