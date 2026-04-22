#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "UNO.h"

/*
TO DO - K
- draw glitch, skipping multiple turns when +2 put down
- win detection
- reshuffling
- uno detection
- reverse player count weird
- 

*/

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
        //make some space so people don't see the private space
        for (int i = 0; i < 15; i++) {
            printf("\n");
        }

        //print Direction, card counts, whose turn it is, and top card.
        printPublicUI(numPlayers, order, &topCard, players, currentTurn);

        printf("\n\n\n\n\n\n------------------------------\nPrivate Section - Only Current Player Should View\n------------------------------\n");


        returnID = userTurn(players, numPlayers, &players[currentTurn], &topCard); //play turn, and return the ID of card played

        //testing
        printf("%d", returnID);

        //winner = checkWin(players[currentTurn]);
        //remember implement skips and reverse later
        if(returnID > 0 && returnID < 10) {//if normal cards, progress turns as normal
        currentTurn += order;
        } else if (returnID == 10) { //skip
            currentTurn += order * 2;
        } else if (returnID == 11) { //reverse
            order *= -1;
            currentTurn += order;
        } else if (returnID == 12) { //draw 2
            draw(2, (currentTurn += order) % numPlayers, players, &deckTop, deck);
            currentTurn += 2 * order; //skip turn of drawing person
        } else if (returnID == 13) { //wild card
            chooseColor(&topCard, returnID);
            currentTurn += order;
        } else if (returnID == 14) { //draw 4
            chooseColor(&topCard, returnID);
            draw(2, (currentTurn += order) % numPlayers, players, &deckTop, deck);
            currentTurn += order;

        } else if (returnID == 0) {
            draw(1, currentTurn, players, &deckTop, deck);
            currentTurn += order;
        } else {
            printf("If you're seeing this something went wrong...\n");
        }
        
        
        //skipping computer for now..
        /*
        else {
            computerTurn(&players[currentTurn], &topCard);
            //winner = checkWin(players[currentTurn]);
            currentTurn++;
        */
        
        //Proper turns
        if (currentTurn < 0) {
            currentTurn += numPlayers;
        } else {
        currentTurn = currentTurn % numPlayers;
        }

    }
    free(players);
    return 0;
}
