# Projet IN104 (2025) - Programmation d’une IA pour le jeu d'échecs en C

- Ce repository sert de structure à partir de laquelle vous programmerez votre moteur d'échecs en C à l'aide des fiches 1 à 8.

- Le répertoire ``src`` contient le code source de ce projet. C'est au sein des fichiers source (``.c``) que vous définirez certaines des variables du moteur déclarées dans les fichiers en-tête (``.h``) du répertoire ``include`` et que vous implémenterez les différentes fonctions déclarées dans ces fichiers en-tête.

- Vous testerez les fonctionnalités que vous implémenterez au fur et à mesure de votre avancement à l'aide du point d'entrée (fonction ``main()``) situé dans le fichier ``main.c``

- Pour compiler votre code, vous utiliserez le fichier ``makefile``, au sein duquel vous éditerez les lignes ``16`` et ``17`` afin de produire des exécutables correspondant à vos noms et prénoms. Il vous faudra aussi éditer les lignes ``12`` et ``13`` du fichier ``uci.h``.

- Pour compiler, à la racine du projet, exécuter : ``make DEBUG=1 && bin/nom1_nom2_linux`` (le flag DEBUG pourra être omis lors des phases de test afin d'améliorer les performances du moteur d'échecs).

- Une fois votre moteur d'échecs terminé, vous pourrez tester sa performance à l'aide d'une interface graphique permettant l'exécution de moteurs d'échecs utilisant le protocole UCI, par exemple [Arena Chess GUI](https://www.playwitharena.de/) ou [The Tarrasch Chess GUI](https://www.triplehappy.com/) (conseil : si vous utilisez l'interface Arena Chess GUI, privilégiez la version Linux, qui est plus ergonomique, et comporte plus de fonctionnalités que la version Windows).

## Pré-requis pour la compilation

- ``gcc``, à installer avec la commande ``sudo apt-get install gcc`` sur Ubuntu par exemple.
- ``x86_64-w64-mingw32-gcc``, à installer avec la commande ``sudo apt-get install gcc-mingw-w64`` sur Ubuntu par exemple.