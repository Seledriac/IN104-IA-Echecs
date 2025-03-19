#ifndef COUPS_H
#define COUPS_H

#include <stdlib.h>
#include <string.h>

#include "masques.h"
#include "echiquier.h"


/*******************************************************************************\
 ===============================================================================
 
            Encodage des coups
 
 ===============================================================================
\*******************************************************************************/


/*
               bits                                 constantes hexadécimales
    
    0000 0000 0000 0000 0011 1111    square de départ        0x3f
    0000 0000 0000 1111 1100 0000    square d'arrivee        0xfc0
    0000 0000 1111 0000 0000 0000    piece                   0xf000
    0000 1111 0000 0000 0000 0000    promotion               0xf0000
    0001 0000 0000 0000 0000 0000    prise                   0x100000
    0010 0000 0000 0000 0000 0000    double push pion        0x200000
    0100 0000 0000 0000 0000 0000    enpassant               0x400000
    1000 0000 0000 0000 0000 0000    roque                   0x800000
*/

#define encoder_coup(depart, arrivee, piece, promotion, prise, double, enpassant, roque) ( \
    (depart) |            \
    ((arrivee) << 6) |    \
    ((piece) << 12) |     \
    ((promotion) << 16) | \
    ((prise) << 20) |     \
    ((double) << 21) |    \
    ((enpassant) << 22) | \
    ((roque) << 23)       \
)
#define get_coup_square_depart(coup) ((coup) & 0x3f)
#define get_coup_square_arrivee(coup) (((coup) & 0xfc0) >> 6)
#define get_coup_piece(coup) (((coup) & 0xf000) >> 12)
#define get_coup_promotion(coup) (((coup) & 0xf0000) >> 16)
#define get_coup_prise(coup) ((coup) & 0x100000)
#define get_coup_double(coup) ((coup) & 0x200000)
#define get_coup_enpassant(coup) ((coup) & 0x400000)
#define get_coup_roque(coup) ((coup) & 0x800000)


/*******************************************************************************\
 ===============================================================================
 
            Exécution des coups
 
 ===============================================================================
\*******************************************************************************/


#define copie_echiquier() \
    BB echiquier_cp[12], occupations_cp[3];                       \
    int trait_cp, enpassant_cp, roque_cp;                         \
    memcpy(echiquier_cp, echiquier, 96);                          \
    memcpy(occupations_cp, occupations, 24);                      \
    trait_cp = trait, enpassant_cp = enpassant, roque_cp = roque; \

#define restauration_echiquier() \
    memcpy(echiquier, echiquier_cp, 96);                          \
    memcpy(occupations, occupations_cp, 24);                      \
    trait = trait_cp, enpassant = enpassant_cp, roque = roque_cp; \

int case_attaquee(int square, int couleur);

extern const int droits_roque[64];

int executer_coup(int coup);


/*******************************************************************************\
 ===============================================================================
 
            Liste des coups possibles et ses fonctions
 
 ===============================================================================
\*******************************************************************************/


#define MAX_COUPS 512

typedef struct {
    int tab_coups[MAX_COUPS];
    int nb_coups;
} coups;

void ajouter_coup(coups *coups, int coup);

void afficher_coup(int coup);

void afficher_coups(coups *coups);


/*******************************************************************************\
 ===============================================================================
 
            Génération des coups possibles
 
 ===============================================================================
\*******************************************************************************/


void generer_coups(coups *coups_possibles);


#endif