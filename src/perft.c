#include "../include/perft.h"


// get time in milliseconds
int get_time_ms() {
    #ifdef WIN64
        return GetTickCount();
    #else
        struct timeval time_value;
        gettimeofday(&time_value, NULL);
        return time_value.tv_sec * 1000 + time_value.tv_usec / 1000;
    #endif
}

long nb_feuilles = 0;

void perft(int profondeur) {
    // à implémenter
}

void test_perft(int profondeur) {
    // à implémenter
}

void exec_perft(int profondeur) {
    // à implémenter
}