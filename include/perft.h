#ifndef PERFT_H
#define PERFT_H


#include <stdlib.h>

#ifdef WIN64
    #include <windows.h>
#else
    # include <sys/time.h>
#endif

#include "coups.h"


// obtenir le temps actuel en milisecondes
int get_time_ms();

extern long nb_feuilles;

void perft(int profondeur);

void test_perft(int profondeur);

void exec_perft(int profondeur);


#endif