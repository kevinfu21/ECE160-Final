#include <stdio.h>
#include <string.h>
#include "UNO.h"

void test2() {
    printf("f2 test\n");
}

int getInt() {
    int num;
    scanf("%d", &num);
    printf("\n");
    return num;
}

//set up number the player 
void initializePlayers(Player player[], int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        player[i].ID = i;
        player[i].handSize = 0;
        printf("Player %d, what's your name? (1 word only)\nName: ", i + 1);
        char temp[50];
        scanf("%s", temp);
        strcpy(player[i].name, temp);
    }
}

void printPublicUI(int numPlayers, int order, Card *topCard, Player players[], int currentTurn) {
    printf("------------------------------\n");
    //print direction
    char direction[10];
    if (order == -1) {
        strcpy(direction, "Reverse");
    }
    else {
        strcpy(direction, "Forward");
    }
    printf("Direction: %s\n", direction);

    //print number of cards each player has
    for (int i = 0; i < numPlayers; i++) {
        printf("Player %d: %s - %d card(s).\n", i + 1, players[i].name, players[i].handSize);
    }

    //print player's turn
    printf("\nPlayer %d, %s, your turn!\n", currentTurn, players[currentTurn].name);

    //print top card
    printf("Top card: ");
    printHand(topCard, 1);
}

//print user turn UI, players[] and numPLayers is unused, moved to publicUI. Changed to int to return ID.
int userTurn(Player players[], int numPlayers, Player *player, Card *topCard){
    int choice;

    //print player's hand
    printf("Your Cards: \n");
    printHand(player->hand, player->handSize);

    printf("Which card would you like to play? (enter index 1-%d or type 0 to draw.): ", player->handSize);
    do{
        scanf("%d", &choice);
        if (choice == 0) {
            return 0;
        }
    } while((choice < 1 || choice > player->handSize) || !validTurn(player->hand[choice-1], topCard));

    int ID = player->hand[choice-1].ID;
    *topCard = player->hand[choice - 1];
    organizeHand(player, choice-1);
    //Check if card follows rule, play card, remove from playersDeck

    return ID;
}