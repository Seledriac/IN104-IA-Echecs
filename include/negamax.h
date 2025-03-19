#ifndef NEGAMAX_H
#define NEGAMAX_H


#include "eval.h"
#include "coups.h"
#include "perft.h"
#include "uci.h"


#define UCI 0

#define VALEUR_MAX 50000
#define VALEUR_MAT 49000

int communicate();


/***************************************\
 ========================================
 
            ALGORITHME NEGAMAX
 
 ========================================
\***************************************/


extern int meilleur_coup, tmp_meilleur_coup;
extern int ply;
extern long long nb_noeuds_parcourus;
extern long long nb_noeuds_eval;

int negamax(int alpha, int beta, int profondeur);

void recherche_meilleur_coup(int profondeur);


#endif