# CY-TRUCK

## Description
CY-TRUCK est un programme en shell, GNUplot, et en C qui permet de générer divers graphiques à partir de données contenues dans un fichier CSV. Ce projet à  pour but de présenter des informations sur les performances des conducteurs, les trajets les plus longs, et les villes les plus traversées, entre autres.

## Fonctionnalités
- **-d1**: Affiche les 10 premiers conducteurs avec le plus de trajets.
- **-d2**: Affiche les 10 premiers conducteurs avec la plus grande distance parcourue.
- **-l**: Montre les 10 trajets les plus longs.
- **-t**: Liste les 10 villes les plus traversées.
- **-s**: Génère des statistiques sur les étapes.
- **-h**: Affiche l'aide, expliquant les options disponibles.
- **Options Bonus**:
  - **-r**: Retire les droits sur le script principal, nécessitant une ré-authentification.

## Prérequis
Pour utiliser CY-TRUCK, assurez-vous d'avoir installé :
- `make`
- `GNUplot`
- `Zenity`
- `ImageMagick`

## Installation
Clonez le dépôt ou téléchargez les fichiers, puis placez votre fichier CSV dans le dossier `data`. Ouvrez un terminal à la racine du projet pour commencer.

## Utilisation
Pour démarrer le programme, exécutez :

```
bash main_script 'nomdevotrefichier.csv' [options]
```


### Authentification avec Zenity
À la première utilisation, une procédure d'authentification est requise. CY-TRUCK utilise **Zenity** facilitant l'entrée sécurisée des informations d'authentification.

Pour vous authentifier, exécutez :

```
bash others/autorization/auto.sh
```

Une fenetre s'ouvrira vous demandant d'appuyer sur une touche pour continuer. Ensuite, une fenêtre d'authentification apparaîtra pour entrer les informations suivantes :
- **Nom d'utilisateur** : admin
- **Mot de passe** : miaou

Après une authentification réussie, vous pouvez utiliser toutes les options du programme. Utilisez `-r` pour vous déconnecter et sécuriser l'accès.


