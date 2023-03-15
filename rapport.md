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

## Exercice 3

## Exercice 4

# Remarques

Nous avions commencé à utiliser un tableau dynamique pour gérer l'ensemble, cependant après considération de la complexité (Recherche : O(n)) nous sommes parti sur une structure d'arbre afin d'améliorer les performances du programme (Recherche en moyenne en complexité logarithmique).

Ainsi la fonction principale du programme (compter les mots), possède une complexité $O(n \times log(n))$ :

- Ajout : $log(n)$
- Test d'appartenance : $log(n)$
- Aplatissement de l'arbre : $O(n)$
- Tri avec ``qsort`` : $O(n \times log(n))$
