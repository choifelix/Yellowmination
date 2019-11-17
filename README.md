# Yellownimation
par Félix Choi et Antoine Somsay, fait le 25/01/2019 dans le cadre d'un projet académique en Programmation Orientée Objet en C++.

Les images et sons utilisés dans ce projet ne proviennent pas des auteurs. Aucuns crédits ne leurs sont attribués.

Version du projet : 1.0

Yellownimation est un programme d'animation qui affiche (avec du son) des personnages liés à du jaune dans 2 équipes différentes et se battent entre eux. Les personnages possèdent des caractéristiques (vies, attaque, défense...) et se déplacent comme des ballons sur le terrain. Ils peuvent, si mana suffisante, lancer des attaques ultimes ravageuses.

Le support utilisé pour le son et l'affichage est la bibliothèque SFML 2.5.1. Il faut penser à l'installer avant, et de préciser si nécessaire dans le makefile le chemin où est installé SFML:

`-I//.../SFML-2.5.1/include` pour la ligne des fichiers objets,
`-L/.../SFML-2.5.1/lib -lsfml-graphics  -lsfml-window -lsfml-system` pour la ligne de l'exécutable.

La compilation se fait dans le répertoire version_1.0


 **Site officiel de sfml**
 https://www.sfml-dev.org/download-fr.php
 
 **Pour profiter de notre animation**
 
 - Installer sfml
 - Telecharger le depot.
 - Aller a l'adresse suivante dans le depot :  `src/version_1.0`
 - Tapez la commande suivante: `make re`
 - Vous allez voir beaucoup de warning, C'EST NORMAL
 

La structure de base du code provient de Cecile BRAUNSTEIN du Laboratoire Lip6.

Les fonts ne nous appartiennent pas. La license est dans le dossier `interface/font/`

Les musiques et sons proviennent pour la plupart de youtube, et ont été modifiés et adaptés au projet.

Les codes de tests et la beta ont été laissé pour les curieux.

Le diagram uml a ete fait sur **Umbrello** : https://umbrello.kde.org/


 
 
