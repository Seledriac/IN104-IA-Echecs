#include "../include/uci.h"


/****************************************************************\
 ================================================================
 
            Variables contrôlées par l'interface UCI
 
 ================================================================
\****************************************************************/


int flag_quit = 0; // flag donnant l'ordre d'arrêter le moteur, reçu pendant la recherche du meilleur coup
int stopped = 0; // flag qui indique si le moteur est arrivé à court de temps de calcul pendant sa recherche
int inc = 0; // incrément de temps par coup pour le joueur actuel
int time = -1; // temps imparti pour le restant de la partie pour le joueur actuel
int movestogo = 40; // nombre de coups sur lesquels répartir le temps de calcul
int movetime = -1; // temps imparti pour le calcul du meilleur coup donné par l'interface UCI
int starttime = 0; // temps (en ms) auquel a commencé le calcul
int stoptime = 0; // temps (en ms) avant lequel doit s'arrêter le calcul
int timeset = 0; // flag pour indiquer si la recherche du meilleur coup se fait sous la contrainte du temps

void reset_time_var() {
    flag_quit = 0;
    stopped = 0;
    inc = 0;
    time = -1;
    movestogo = 40;
    movetime = -1;
    starttime = 0;
    stoptime = 0;
    timeset = 0;
}


/*******************************************************\
 ========================================================
 
            FONCTIONS I/O (provenant de VICE)
 
 ========================================================
\*******************************************************/


int input_waiting() {
    #ifndef WIN64
        fd_set readfds;
        struct timeval tv;
        FD_ZERO (&readfds);
        FD_SET (fileno(stdin), &readfds);
        tv.tv_sec=0; tv.tv_usec=0;
        select(16, &readfds, 0, 0, &tv);
        return (FD_ISSET(fileno(stdin), &readfds));
    #else
        static int init = 0, pipe;
        static HANDLE inh;
        DWORD dw;
        if (!init) {
            init = 1;
            inh = GetStdHandle(STD_INPUT_HANDLE);
            pipe = !GetConsoleMode(inh, &dw);
            if (!pipe) {
                SetConsoleMode(inh, dw & ~(ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT));
                FlushConsoleInputBuffer(inh);
            }
        }
        if (pipe) {
           if (!PeekNamedPipe(inh, NULL, 0, NULL, &dw, NULL)) return 1;
           return dw;
        }
        else {
           GetNumberOfConsoleInputEvents(inh, &dw);
           return dw <= 1 ? 0 : dw;
        }
    #endif
}

void read_input() {
    int bytes;
    char input[256] = "", *endc;
    if (input_waiting()) {
        do {
            bytes = read(fileno(stdin), input, 256);
        } while (bytes < 0);        
        endc = strchr(input,'\n');
        if (endc)
            *endc = 0;
        if (strlen(input) > 0) {
            if (!strncmp(input, "stop", 4)) {
                stopped = 1;
            }
            if (!strncmp(input, "quit", 4)) {
                stopped = 1;
                flag_quit = 1;
            }
        }
    }
}

int communicate() {
    read_input();
    if (timeset == 1 && get_time_ms() > stoptime) {
		stopped = 1;
	}
    return stopped;
}


/*************************************\
 ======================================
 
            PROTOCOLE UCI
 
 ======================================
\*************************************/


int get_coup_str(char *coup_gui) {
    int square_depart = (coup_gui[0] - 'a') + 8 * (8 - (coup_gui[1] - '0'));
    int square_arrivee = (coup_gui[2] - 'a') + 8 * (8 - (coup_gui[3] - '0'));
    int promotion = 0;
    if (coup_gui[4] == 'q' || coup_gui[4] == 'r' || coup_gui[4] == 'b' || coup_gui[4] == 'n') {
        promotion = trait == noirs ? char_piece[(int)coup_gui[4]] : char_piece[(int)coup_gui[4]] - 6; 
    }
    coups coups_possibles[1];
    generer_coups(coups_possibles);
    int coup;
    for (int i = 0; i < coups_possibles->nb_coups; i++) {
        coup = coups_possibles->tab_coups[i];
        if (get_coup_square_depart(coup) == square_depart &&
            get_coup_square_arrivee(coup) == square_arrivee &&
            get_coup_promotion(coup) == promotion) {
            copie_echiquier();
            if (executer_coup(coup)) {
                restauration_echiquier();
                return coup;
            } else
                return 0;
        }
    }
    return 0;
}

// parse et exécute la commande UCI "position".
// exemples : position startpos 
//            position startpos moves e2e4 e7e5
//            position fen r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1
//            position fen r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 moves e2a6 e8g8
void parse_position(char *instruction) {
    // à implémenter
}

// parse et exécute la commande UCI de recherche de meilleur coup : "go"
// exemples : go depth 6
//            go wtime 300000 btime 300000 movestogo 30
//            go wtime 300000 btime 300000 movestogo 30
void parse_go(char *instruction) {
    reset_time_var();
    instruction += 3;
    int profondeur = MAX_PROFONDEUR;
    char *option;
    if ((option = strstr(instruction, "winc")) && trait == blancs)
        inc = atoi(option + 5);
    if ((option = strstr(instruction, "binc")) && trait == noirs)
        inc = atoi(option + 5);
    if ((option = strstr(instruction, "wtime")) && trait == blancs)
        time = atoi(option + 6);
    if ((option = strstr(instruction, "btime")) && trait == noirs)
        time = atoi(option + 6);
    if ((option = strstr(instruction, "movestogo")))
        movestogo = atoi(option + 10);
    if ((option = strstr(instruction, "movetime")))
        movetime = atoi(option + 9);
    if (strstr(instruction, "depth") != NULL)
        profondeur = atoi(instruction + 6);
    if (movetime != -1) {
        time = movetime;
        movestogo = 1;
    }
    starttime = get_time_ms();
    if (time != -1) {
        timeset = 1;
        time /= movestogo;
        if (time > 1500) time -= 50;
        stoptime = starttime + time + inc;
    }
    printf("time: %d  start: %u  stop: %u  depth: %d  timeset:%d\n",
            time, starttime, stoptime, profondeur, timeset);
    int score;
    for (int profondeur_actuelle = 1; profondeur_actuelle <= profondeur; profondeur_actuelle++) {
        nb_noeuds_parcourus = 0;
        score = negamax(-VALEUR_MAX, VALEUR_MAX, profondeur_actuelle);
        if (!stopped)
            meilleur_coup = tmp_meilleur_coup;
        else
            break;
        printf("info score cp %d depth %d nodes %lld time %d\n", score, profondeur_actuelle, nb_noeuds_parcourus, get_time_ms() - starttime);
    }
    printf("bestmove ");
    afficher_coup(meilleur_coup);
}

// boucle principale d'interface UCI
void main_uci() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    // à implémenter
}