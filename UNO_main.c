#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "UNO.h"

int main(){
    int numPlayers; //number of players
    int order = 1; //reverse(-1) or not(1)
    int currentTurn = 0; //turn count
    int winner = 0; //while winner == 0, keep game going in the while loop below. 
    //additional settings
    int drawUntilMatch = 0;
    int sevenZero = 0;
    int deckTop = 0;
    
    Card deck[DECK_SIZE]; //deck
    Card topCard = {-1, WILD}; //Card that was last placed

    //creates a shuffled deck
    srand(time(NULL));
    createDeck(deck);
    shuffleDeck(deck);
    //printDeck(deck);

    //prompt user for gamemode and create a pointer of players array
    prompt(&drawUntilMatch, &sevenZero);

    //prompt user for number of players
    printf("Enter number of players(Max %d): ", MAX_PLAYERS);
    numPlayers = getInt();
    Player *players = malloc(numPlayers * sizeof(Player));

    //setup players
    initializePlayers(players, numPlayers);

    //deal starting cards
    dealDeckStart(players, numPlayers, deck, &deckTop);

    //for testing purposes
    //printAllDecks(players, numPlayers);

    //ACTUAL GAME
    int returnID; //ID of card played
    while (winner == 0) {
        //print Direction, card counts, whose turn it is, and top card.
        printPublicUI(numPlayers, order, &topCard, players, currentTurn);

        printf("\n\n\n\n\n\n------------------------------\nPrivate Section - Only Current Player Should View\n------------------------------\n");


        returnID = userTurn(players, numPlayers, &players[currentTurn], &topCard); //play turn, and return the ID of card played


        //winner = checkWin(players[currentTurn]);
        //remember implement skips and reverse later
        if(returnID > 0 || returnID < 10) {//if normal cards, progress turns as normal
        currentTurn += order;
        } else if (returnID == 10) { //skip
            currentTurn += order * 2;
        } else if (returnID == 11) { //reverse
            order *= -1;
            currentTurn += order;
        } else if (returnID == 12) { //draw 2
            //code for drawing cards
        } else if (returnID == 13) { //wild card
            //code for wild
        } else if (returnID == 14) { //draw 4
            //code for draw 4
        } else if (returnID == 0) {
            //code for draw card
        } else {
            printf("If you're seeing this something went wrong...\n");
        }
        
        
        //skipping computer for now
        /*
        else {
            computerTurn(&players[currentTurn], &topCard);
            //winner = checkWin(players[currentTurn]);
            currentTurn++;
        */
        
        //Mod the turns
        currentTurn = currentTurn % numPlayers;

        //make some space so people don't see the private space
        for (int i; i < 30; i++) {
            printf("\n");
        }
    }
    free(players);
    return 0;
}
