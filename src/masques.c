#include "../include/masques.h"


/*******************************************************************************\
 ===============================================================================
 
            Définition des masques de d'attaque de chaque type de pièce
 
 ===============================================================================
\*******************************************************************************/


// =========================== ATTAQUES STATIQUES ============================

BB attaques_pions[2][64];
BB attaques_cavaliers[64];
BB attaques_rois[64];

BB pas_colonne_a;
BB pas_colonne_ab;
BB pas_colonne_h;
BB pas_colonne_hg;

void generer_bb_pas_colonne() {
    // à implémenter
}

void generer_attaques_pion() {
    // à implémenter
}

void generer_attaques_cavalier() {
    // à implémenter
}

void generer_attaques_roi() {
    // à implémenter
}

void generer_masques_d_attaque_statiques() {
    // à implémenter
}

// =========================== ATTAQUES DYNAMIQUES ============================

BB masque_d_attaque_dynamique_fou(int square, BB bloqueurs) {
    // à implémenter
    return 0ULL;
}

BB masque_d_attaque_dynamique_tour(int square, BB bloqueurs) {
    // à implémenter
    return 0ULL;
}

BB masque_d_attaque_dynamique_dame(int square, BB bloqueurs) {
    // à implémenter
    return 0ULL;
}