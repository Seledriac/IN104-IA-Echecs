#ifndef EVAL_H
#define EVAL_H


#include "bitboards.h"
#include "echiquier.h"


extern const int valeur_piece[12];

extern const int score_pos_pion[64];

extern const int score_pos_cavalier[64];

extern const int score_pos_fou[64];

extern const int score_pos_tour[64];

extern const int score_pos_dame[64];

extern const int score_pos_roi[64];

extern const int square_mirroir[64];

int eval();


#endif