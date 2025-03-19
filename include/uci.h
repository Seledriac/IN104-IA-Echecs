#ifndef UCI_H
#define UCI_H


#include <unistd.h>

#include "echiquier.h"
#include "coups.h"
#include "negamax.h"


#define nom_moteur "nom_moteur" // à éditer
#define nom_auteur "nom1 nom2" // à éditer

#define MAX_PROFONDEUR 64


/****************************************************************\
 ================================================================
 
            Variables contrôlées par l'interface UCI
 
 ================================================================
\****************************************************************/


extern int flag_quit; // flag donnant l'ordre d'arrêter le moteur, reçu pendant la recherche du meilleur coup
extern int stopped; // flag qui indique si le moteur est arrivé à court de temps de calcul pendant sa recherche
extern int inc; // incrément de temps par coup pour le joueur actuel
extern int time; // temps imparti pour le restant de la partie pour le joueur actuel
extern int movestogo; // nombre de coups sur lesquels répartir le temps de calcul
extern int movetime; // temps imparti pour le calcul du meilleur coup donné par l'interface UCI
extern int starttime; // temps (en ms) auquel a commencé le calcul
extern int stoptime; // temps (en ms) avant lequel doit s'arrêter le calcul
extern int timeset; // flag pour indiquer si la recherche du meilleur coup se fait sous la contrainte du temps

void reset_time_var();


/*******************************************************\
 ========================================================
 
            FONCTIONS I/O
 
 ========================================================
\*******************************************************/


int input_waiting();

void read_input();

int communicate();


/*************************************\
 ======================================
 
            PROTOCOLE UCI
 
 ======================================
\*************************************/


int get_coup_str(char *coup_gui);

// parse et exécute la commande UCI "position".
// exemples : position startpos 
//            position startpos moves e2e4 e7e5
//            position fen r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1
//            position fen r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 moves e2a6 e8g8
void parse_position(char *instruction);

// parse et exécute la commande UCI de recherche de meilleur coup : "go"
// exemples : go depth 6
//            go wtime 300000 btime 300000 movestogo 30
//            go wtime 300000 btime 300000 movestogo 30
void parse_go(char *instruction);

// boucle principale d'interface UCI
void main_uci();


#endif