#include <stdio.h>
#include "UNO.h"

int main(){
    int players;
    int computers;
    int order; //reverse or not
    char color;
    char *current_card;
    int current_turn;
    int winner; //while winner == 0, keep game going in the while loop below. 

    //SETUP STUFF
    /*
    printf("Hello! This is UNO : ).\n");
    prompt(&players, &computers);

    printf("Players: %d\n", players);
    printf("Computers: %d\n", computers);
    */

    test1();
    test2();

    //ACTUAL GAME
    while (winner == 0) {
        //GAME STUFF GOES HERE
    }




    return 0;
}
