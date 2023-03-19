---
title: Perfectionnement à la programmation C
subtitle: TP6 - Compter les mots
date: 13 février 2023
colorlinks: true
author:
    - Nicolas SEBAN
    - Amir POUYANFAR
lang: fr # texlive-lang-french / texlive-babel-french
geometry: margin=3cm
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

# Réponses

## Exercice 1

2.

- ``-a`` : trier les mots de la réponse dans l'ordre lexicographique.

- ``-n`` : trier les mots de la réponse d'après leur nombre d’occurrences de manière décroissante.

- ``-s MOT`` ou ``-p MOT``: Affiche les mots suivants/précédents MOT

- ``-e N`` : afficher une ligne pour chaque expression composée de N mots extraite de X suivie d’espaces, suivies du nombre (en base dix d’occurrences de l’expression en question dans le fichier.

## Exercice 2

Nous avons écrit un module `test`, nous permettant de tester les 
fonctions indispensable de notre travail.


- `test_assert_print()` permet de tester le résultat d'une assertion

- `test_MOT_est_correct()` pour tester la fonction `MOT_est_correct`. Cette dernière ayant pour but de vérifier 
si un mot est corrrect dans le cadre du TP, par exemple un mot qui
comporte des chiffres n'est pas considéré correct.

- `test_MOT_normaliser` pour tester la fonction `MOT_normaliser`, cette dernière étant une petite fonction mettant toutes les lettres d'un mot, en minuscule, en utilisant la fonction `tolower()` du module `ctype.h`.

- `test_TAB_arbre_en_tab()` pour tester la fonction `TAB_arbre_en_tab`. Cette fonction, située dans le module `tableau`, nous permet d'écrire l'arbre lexicographique, sous forme d'un tableau.

- `test_TAB_tri()` pour tester `TAB_tri` dans le module `tableau`.
- `test_ALG_mots_avant_x()`, `test_ALG_mots_apres_x()`, pour tester repectivement les fonctions `ALG_mots_avant_x()` et `ALG_mots_apres_x()`, étant situées dans le module `algo`.

- `test_ALG_compter_mots()` pour tester `ALG_compter_mots()`, cette dernière ayant pour but de compter le nombre d'expressions de n mots.

- `test_ALG_expressions()` pour tester la fonction `ALG_expressions()`, cette dernière ayant pour objectif de compter le nombre d'expression de n mots adjacent dans un texte.

- Les fonctions `test_ABR_initialiser()`, `test_ABR_alloue_noeud()`, `test_ABR_cherche_mot()`, `test_ABR_appartient()` et `test_ABR_ajouter_mot()` pour tester les fonction correspodantes, qui sont les fonctions usuelles du traitement des arbres, respectivement pour initialiser, allouer un noeud, chercher un mot, teste d'appartenance et ajout d'un mot dans un arbre.

# Remarques

Nous avions commencé à utiliser un tableau dynamique pour gérer l'ensemble, cependant après considération de la complexité (Recherche : O(n)) nous sommes parti sur une structure d'arbre afin d'améliorer les performances du programme (Recherche en moyenne en complexité logarithmique).

Ainsi la fonction principale du programme (compter les mots), possède une complexité $O(n \times log(n))$ :

- Ajout : $log(n)$
- Test d'appartenance : $log(n)$
- Aplatissement de l'arbre : $O(n)$
- Tri avec ``qsort`` : $O(n \times log(n))$
