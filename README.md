# Voltorbataille
Recréation du jeu *Voltorbataille* (*Voltorb Flip* en anglais) tiré de Pokémon Heart Gold / Soul Silver avec le moteur de jeu **cocos2d-x**.

*NOTE : le jeu n'est pas entièrement terminé. Il est pour l'instant impossible de gagner... Dommage.*
## Principe du jeu
Ce jeu est un mixte entre de la chance et de la technique. Le but du jeu est de découvrir toutes les cases ayant une valeur supérieure à 1 sans découvrir de Voltorbe car le cas échéant la partie est perdue.

Pour ce faire vous devez vous servir des indices à votre disposition : sur chaque colonne et chaque ligne est affiché :
- La somme des points obtenables dans cette ligne / colonne.
- Le nombre de Voltorbe situés dans cette ligne / colonne.
### Calcul est points
Vous commencez avec 0 point. La valeur de la première case retournée s'ajoute à votre score. Votre score est ensuite multiplié par la valeur de chaque case retournée. *Ainsi retourner une case de valeur 1 n'augmentera pas votre score.*
## Screens (version Windows)
### Écran d'accueil
![Écran d'acceuil](https://image.prntscr.com/image/SIWTHnLAR1u8vooDutHqhg.png)
### Début de partie
![Début de partie](https://image.prntscr.com/image/NR3AwZLzQdeJgCKbYLsoEg.png)
### Partie perdue
![Partie perdue](https://image.prntscr.com/image/9Ii4GfbgQG2We_xXiAZTdw.png)
