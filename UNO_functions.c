#include <stdio.h>
#include <stdlib.h>
#include "UNO.h"


void test1() {
    printf("f1 test\n");
}


void prompt(int *drawUntilMatch, int *sz){
    int selection;
    int size;
    do{
        printf("------------------------------\n");
        printf("(1) Start Game\n");
        printf("(2) Gamemodes\n");
        printf("Select: ");

        do{
            scanf("%d", &selection);
            if (!(selection == 1 || selection == 2)) {
                printf("Invalid Input! Try again: ");
            }
        }while(!(selection == 1 || selection == 2));

        if (selection == 2) gamemodes(drawUntilMatch, sz);

    } while (selection != 1);

    printf("Starting...\n------------------------------\n");
    
}

//7-0 or Draw Until Match
void gamemodes(int *playComputers, int *sz){
    int selection;
    do {
        printf("------------------------------\n");
        printf("Play with computer - %s\n", *playComputers ? "On" : "Off");
        printf("Select the gamemode you want to change (1) or to exit (3): ");
        do {
            scanf("%d", &selection);
            if (selection != 1 && selection != 3) {
                printf("Invalid Input! Try again: ");
            }
        } while (selection != 1 && selection != 3);
        
        if (selection == 1)
            *playComputers = !(*playComputers);

    } while (selection != 3);

    printf("Exiting gamemodes... \n");
}


//(I'm going to move this to F2 and make some changes for pvp, original is below. - K)
//User makes a valid move

/*
void userTurn(Player players[], int numPlayers, Player *player, Card *topCard){
    int choice;

    printf("Opponents Card Remaining: \n");
    printOpponentCardCount(players, numPlayers);

    printf("Your Cards: \n");
    printHand(player->hand, player->handSize);

    printf("Which card would you like to play? (enter index 1-%d): ", player->handSize);
    do{
        scanf("%d", &choice);
    } while((choice < 1 || choice > player->handSize) || !validTurn(player->hand[choice-1], topCard));
    *topCard = player->hand[choice - 1];
    organizeHand(player, choice-1);
    //Check if card follows rule, play card, remove from playersDeck
    //Check if its the last 2 card -> input UNO
}
*/

//Set the top of the discard pile
int validTurn(Card userCard, Card *topCard, int computerMove){
    if(topCard->ID == -1 || userCard.color == topCard->color || userCard.color == WILD || userCard.ID == topCard->ID){
        return 1;
    } else {
        if(!computerMove){
            printf("Invalid card! Try again: ");
        }
        return 0;
    }
}

//Organize the player's cards
void organizeHand(Player *player, int positionRemoved){
    player->hand[positionRemoved] = player->hand[player->handSize-1];
    player->handSize--;
}

void printOpponentCardCount(Player players[], int numPlayers){
    for(int i = 1; i < numPlayers; i++){
        printf("Computer %d: %d \n", i, players[i].handSize);
    }
}

int computerTurn(Player *player, Card *topCard, Card deck[], int *deckTop) {
    for (int i = 0; i < player->handSize; i++) {
        if (validTurn(player->hand[i], topCard, 1)) {
            int returnID = player->hand[i].ID;

            *topCard = player->hand[i];
            organizeHand(player, i);

            if (returnID == 13 || returnID == 14) {
                topCard->color = rand() % 4;
            }

            return returnID;
        } 
    }

    // draw if no valid move
    player->hand[player->handSize++] = deck[(*deckTop)++];
    return -2;
}
//drawCards(player); //create a draw card function 
//^^ made it in the cards.c file - K