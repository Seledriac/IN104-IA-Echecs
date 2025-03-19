#ifndef MASQUES_H
#define MASQUES_H


#include <stdlib.h>

#include "bitboards.h"
#include "echiquier.h"


/*******************************************************************************\
 ===============================================================================
 
            Définition des masques de d'attaque de chaque type de pièce
 
 ===============================================================================
\*******************************************************************************/


// =========================== ATTAQUES STATIQUES ============================

extern BB attaques_pions[2][64];
extern BB attaques_cavaliers[64];
extern BB attaques_rois[64];

extern BB pas_colonne_a;
extern BB pas_colonne_ab;
extern BB pas_colonne_h;
extern BB pas_colonne_hg;

void generer_bb_pas_colonne();

void generer_attaques_pion();

void generer_attaques_cavalier();

void generer_attaques_roi();

void generer_masques_d_attaque_statiques();

// =========================== ATTAQUES DYNAMIQUES ============================

BB masque_d_attaque_dynamique_fou(int square, BB bloqueurs);

BB masque_d_attaque_dynamique_tour(int square, BB bloqueurs);

BB masque_d_attaque_dynamique_dame(int square, BB bloqueurs);


#endif