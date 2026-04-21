#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "UNO.h"

int main(){
    int numPlayers;
    int order = 1; //reverse or not
    char color;
    char *current_card;
    int currentTurn = 0;
    int winner = 0; //while winner == 0, keep game going in the while loop below. 
    int drawUntilMatch = 0;
    int sevenZero = 0;
    int deckTop = 0;
    Card deck[DECK_SIZE];
    Card topCard = {-1, WILD}; //Card that was last placed

    //creates a shuffled deck
    srand(time(NULL));
    createDeck(deck);
    shuffleDeck(deck);
    //printDeck(deck);

    //prompt user for gamemode and create a pointer of players array
    prompt(&drawUntilMatch, &sevenZero);

    //prompt user for number of players
    printf("Enter number of players: ");
    numPlayers = getInt();
    struct Player *players = malloc(numPlayers * sizeof(Player));

    //setup players
    initializePlayers(players, numPlayers);



    dealDeckStart(players, numPlayers, deck, &deckTop);
    
    //ACTUAL GAME
    while (winner == 0) {
        if (currentTurn == 0) {
            userTurn(players, numPlayers, &players[currentTurn], &topCard);
            //winner = checkWin(players[currentTurn]);
            currentTurn++;
        } else {
            computerTurn(&players[currentTurn], &topCard);
            //winner = checkWin(players[currentTurn]);
            currentTurn++;
        }

        currentTurn = (currentTurn + order + numPlayers) % numPlayers;
    }

    test1();
    test2();



    free(players);
    return 0;
}
