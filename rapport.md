---
title: Perfectionnement à la programmation C
subtitle: TP6 - Compter les mots
date: 13 février 2023
colorlinks: true
author:
    - Nicolas SEBAN
    - Amir POUYANFAR
lang: fr # texlive-lang-french / texlive-babel-french
geometry: margin=2.5cm
header-includes:
    - \usepackage{graphicx}
    - \usepackage{fancyhdr}
    # https://ctex.org/documents/packages/layout/fancyhdr.pdf
    - \pagestyle{fancy}
    - \rhead{}
    - \lhead{}
    - \renewcommand{\headrulewidth}{0pt}
    - \renewcommand{\footrulewidth}{0.2pt}
    - \lfoot{\includegraphics[height=0.8cm]{logos/namedlogoUGE.png}}
    - \rfoot{\includegraphics[height=1cm]{logos/logoLIGM.png}}
...

\pagebreak

# Introduction

L'objectif de ce TP est de compter le nombre d'occurrences de chaque mot dans un texte, et de les afficher selon trois ordres de tris différents : apparition, lexicographique et nombre d'occurrences.

# Réponses

## Exercice 1

### Liste des options demandées par la spécification

- ``-a, --lexico`` : trier les mots de la réponse dans l'ordre lexicographique.

- ``-n, --occ`` : trier les mots de la réponse d'après leur nombre d’occurrences de manière décroissante.

- ``-s MOT, --apres=MOT`` : Affiche les mots suivants ``MOT``.

- ``-p MOT, --avant=MOT``: Affiche les mots avant ``MOT``.

- ``-e N, --expr=N`` : Affiche chaque expression composée de N mots extraite du texte, tout en ignorant les séparateurs.

- ``-test`` : Lance les tests unitaires.

Nous avons également ajouté les options suivantes :

- ``-c, --croissant`` : Force le trie des mots dans l'ordre croissant.

- ``-d, --decroissant`` : Force le trie des mots dans l'ordre décroissant.

- ``-f, --apparition`` : Trie les mots dans l'ordre d'apparition (par défaut)

- ``-h, --help`` : Affiche l'aide.

Nous avons fait le choix d'utiliser la fonction ``getopt_long`` pour la gestion des options, car elle simplifie énormément le *parsing* des arguments, et permet de gérer, en prime, les options longues.

Cependant, pour respecter la spécification, nous utilisons sa variante ``getopt_long_only`` qui permet de gérer les options longues sans les préfixer par ``--``, car l'énoncé demande que l'option lançant les tests unitaires soit ``-test``, et non ``--test``.

\pagebreak

### Découpage du projet

- ``ABR`` : Manipulation de l'arbre binaire de recherche de chaînes de caractères. Elle contient les fonctions usuelles du traitement des arbres, respectivement pour initialiser, allouer un nœud, chercher un mot, teste d'appartenance et ajout d'un mot dans un arbre. :
  - ``ABR_initialiser()``
  - ``ABR_alloue_noeud()``
  - ``ABR_cherche_mot()``
  - ``ABR_appartient()``
  - ``ABR_ajouter_mot()``

- ``algo`` : Contient les fonctions de calculs des statistiques demandées par la spécification, chacune de ces fonctions itère sur le fichier d'entrée, et appelle les fonctions de manipulation de l'arbre binaire de recherche :
  - ``ALG_mots_avant_x()`` : compte les mots avant un mot donné.
  - ``ALG_mots_apres_x()`` : compte les mots après un mot donné.
  - ``ALG_compter_mots()`` : compte les occurrences de mots.
  - ``ALG_expressions()`` : compte le nombre d'expressions de $n$ mots adjacents dans un texte.

- ``tableau`` : Manipulation de tableaux de pointeurs sur les nœuds de l'arbre binaire de recherche. Elle contient notamment :
  - ``TAB_arbre_en_tab()`` : *Aplatit* l'arbre binaire de recherche sous forme d'un tableau de pointeurs sur les nœuds de l'arbre, selon un parcours infixe.
  - ``TAB_tri()`` : Trie le tableau de pointeurs selon l'ordre voulu.
  - ... et d'autres fonctions de comparaison pour ``qsort``.

- ``mot`` : Manipulation de chaînes de caractères :
  - ``MOT_est_correct()`` : Vérifie si un mot est correct dans le cadre du TP. Par exemple un mot qui comporte des chiffres n'est pas considéré correct.
  - ``MOT_normaliser()`` : Courte fonction mettant toutes les lettres d'un mot, en minuscule, en utilisant la fonction ``tolower()`` du module ``ctype.h``.

\pagebreak

## Exercice 2

Nous avons écrit le module `test`, permettant de tester les fonctions importantes de notre projet, c'est à dire les fonctions énumérées dans l'exercice 1 (ci-dessus).

Afin d'éviter la redondance de conditions pour réaliser les tests, et ne pas utiliser la macro ``assert``, nous avons créé une macro ``test_assert`` qui prend en paramètre une condition.
Celle-ci affiche un message d'erreur avec l'emplacement de ligne problématique si la condition n'est pas vérifiée, et qui à la place de terminer le programme, retourne ``0`` à la fonction de test unitaire appelante, afin que la fonction ``test()`` retourne ``0`` dès que l'un des tests échoue.

Nous avons fait le choix d'afficher les tests d'assertions corrects pour plus de verbosité.

Il aurait peut-être été plus judicieux de ne pas s'arrêter au premier test échoué, mais de continuer les tests, et de retourner le nombre de tests échoués, afin de pouvoir afficher un message d'erreur plus complet, mais nous avons préféré suivre l'énoncé.

Enfin comme demandé dans l'énoncé, nous avons déclaré en ``static`` les fonctions de tests unitaires dans le fichier ``test.c`` afin de ne pas les rendre accessibles aux autres modules.

# Complexité

Au premier abord, nous avions utilisé un tableau dynamique pour gérer l'ensemble, cependant après considération de la complexité (recherche en $O(n)$) nous avons changé pour une structure d'arbre afin d'améliorer les performances du programme (recherche en moyenne en complexité logarithmique).

Pour cela nous avons ajouté aux nœuds deux attributs supplémentaires : ``nb_occ`` et ``apparition``. Le premier permet de compter le nombre d'occurrences d'un mot (s'il existe déjà, nous seulement incrémentons cette valeur, sans nouvelles allocations), et le second permet de garder l'ordre d'apparition des mots dans le texte (à chaque ajout d'un nouveau nœud (mot), nous le numérotons avec la taille de l'arbre).

On ainsi les performances suivantes :

- Ajout : $log(n)$
- Test d'appartenance : $log(n)$
- Aplatissement de l'arbre : $O(n)$
- Tri avec ``qsort`` : $O(n \cdot log(n))$ (utilisé pour le tri par ordre d'apparition et nombre d'occurrences)

Ces opérations étant réalisées dans cet ordre, nous avons ainsi que la fonction principale du programme (compter les mots), possède une complexité $O(n \cdot log(n))$ où $n$ est le nombre de mots dans le texte. De même, pour les autres fonctions car on a : $O(n \cdot log(n)) + O(n \cdot log(n)) = O(n \cdot log(n))$.

On remarque que ce programme reste toujours moins efficace qu'une implémentation avec un dictionnaire qui serait très simple à gérer en Python, mais qui nécessiterait d'implémenter une table de hachage en C, ce que nous n'avons pas étudié en cours. En effet, l'insertion et le test d'appartenance dans un dictionnaire ont une complexité en $O(1)$.

Une autre idée pourrait être d'utiliser un arbre lexicographique, de manière à ce que la profondeur de l'arbre soit au maximum de la taille du plus long mot, ce qui permettrait d'obtenir un temps linéaire à la taille de chaque mot pour l'insertion et le test d'appartenance, mais aussi d'éviter la gestion de collisions nécessaire pour une table de hachage.

# Conclusion

Ce TP nous a permis de mettre en pratique les notions vues en cours d'algorithmie des arbres, d’appréhender le *Test Driven Development* mais aussi l'occasion d'utiliser à plein potentiel la bibliothèque ``getopt`` et sa variante ``getopt_long``.
