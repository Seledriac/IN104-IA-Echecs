#ifndef BITBOARD_H
#define BITBOARD_H


#include <stdio.h>


/*******************************************************************************\
 ===============================================================================
 
            Définition du type bitboard et de ses macros
 
 ===============================================================================
\*******************************************************************************/


#define BB unsigned long long
#define get_bit(bb, square) ((bb) & (1ULL << (square)) ? 1 : 0)
#define set_bit(bb, square) ((bb) |= (1ULL << (square)))
#define pop_bit(bb, square) (get_bit((bb), (square)) ? (bb) ^= (1ULL << (square)) : 0)

void print_bitboard(BB bb);

int nb_bits(BB bb);

int ls1b_index(BB bb);


#endif