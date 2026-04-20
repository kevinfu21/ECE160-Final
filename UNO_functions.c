#include <stdio.h>
#include "UNO.h"

void test1() {
    printf("f1 test\n");
}

void prompt(int *drawUntilMatch, int *sz){
    int selection;
    int size;
    do{
        printf("(1) Start Game\n");
        printf("(2) Gamemodes\n");

        do{
            scanf("%d", &selection);
        }while(selection == 1 || selection == 2);

        if (selection == 2) gamemodes(drawUntilMatch, sz);

    } while (selection != 1);

    printf("Starting...\n");
    
}

//7-0 or Draw Until Match
void gamemodes(int *drawUntilMatch, int *sz){
    int selection;
    do{
        printf("Draw Until Match - %s\n", *drawUntilMatch ? "On" : "Off");
        printf("7-0 (Play a 7 swap your hands with another player, play a 0 makes everyone swap hands): - %s\n", *sz ? "On" : "Off");
        printf("Select the gamemode you want to change (1/2) or to exit (3): \n");

        do{
        scanf("%d", &selection);
        }while(selection < 1 || selection > 3);

        if(selection == 1) *drawUntilMatch = !(*drawUntilMatch);
        else if(selection == 2) *sz = !(*sz);
    } while(selection != 3);
    printf("Exiting gamemodes... \n");
}

void initalizePlayers(Player *player, int numPlayers){
    for (int i = 0; i < numPlayers; i++) {
        player[i].handSize = 0;
    }
}

void userTurn(Player *player){
    int choice;
    printf("Your Cards: \n");
    printHand(player->hand, player->handSize);
    printf("Which card would you like to play? (enter index 1-%d): ", player->handSize);
    do{
        scanf("%d", &choice);
    } while(choice < 1 || choice > player->handSize);
    //Check if card follows rule, play card, remove from playersDeck
    //Check if its the last 2 card -> input UNO
}