#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "UNO.h"

/*
- NOTE: FOR NOW, WINNING JUST SKIPS THE PLAYER, WINNER CAN STILL BE INTERACTED WITH, FIX LATER IF YOU WANT To HAVE MULTIPLE WINNER
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
     //Card that was last placed, wild is temp

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

    //setup podium
    int numWinners = 0; //
    Podium *podium = malloc(numPlayers *sizeof(Podium));


    //setup players
    initializePlayers(players, numPlayers);

    //deal starting cards
    dealDeckStart(players, numPlayers, deck, &deckTop);

    //place top card
    Card topCard = deck[deckTop++];
    
    //for testing purposes
    //printAllDecks(players, numPlayers);

    //ACTUAL GAME
    int returnID; //ID of card played
    int deckReset = 0; //If deck was reset
    while (winner == 0) {
        //make some space so people don't see the private space
        for (int i = 0; i < 15; i++) {
            printf("\n");
        }

        //print Direction, card counts, whose turn it is, and top card.
        printPublicUI(numPlayers, order, &topCard, players, currentTurn);

        //if deck is shuffled
        if (deckReset) {
            printf("Deck was reset.\n");
            deckReset = 0;
        }

        printf("%d cards left in deck.", 108 - deckTop); 

        printf("\n\n\n\n\n\n------------------------------\nPrivate Section - Only Current Player Should View\n------------------------------\n");


        returnID = userTurn(players, numPlayers, &players[currentTurn], &topCard); //play turn, and return the ID of card played

        //logic for UNO(one card) it's gonna be manual
        if (checkUno(&players[currentTurn]) && returnID != 0 && returnID != -1 && returnID != -2) {
            screamUNO(&players[currentTurn], deck, deckTop, currentTurn, players);
        }

        //check for win
        checkWin(&players[currentTurn], &numWinners, podium, &winner);


        if(returnID > 0 && returnID < 10) {//if normal cards, progress turns as normal
        currentTurn += order;
        } else if (returnID == 10) { //skip
            currentTurn += order * 2;
        } else if (returnID == 11) { //reverse
            order *= -1;
            currentTurn += order;
        } else if (returnID == 12) { //draw 2
            draw(2, (currentTurn + order) % numPlayers, players, &deckTop, deck);
            currentTurn += 2*order; //skip turn of drawing person
        } else if (returnID == 13) { //wild card
            chooseColor(&topCard, returnID);
            currentTurn += order;
        } else if (returnID == 14) { //draw 4
            chooseColor(&topCard, returnID);
            draw(4, (currentTurn + order) % numPlayers, players, &deckTop, deck);
            currentTurn += 2*order;

        } else if (returnID == 0) { //self draw 1
            draw(1, currentTurn, players, &deckTop, deck);

        }else if (returnID == -1) {
            resetDeck(deck, &deckTop);
            //no change to turn, deck reset;
            deckReset = 1;
            
        } else if (returnID == -2) {
            currentTurn++;
            //TEMPORARY WORKAROUND FOR WINNER, TURN SKIP, FIX LATER
        }
        else {
            printf("If you're seeing this something went wrong...\n");
        }
        

        //automatic logic for running out of cards
        if (deckTop > 107) {
            resetDeck(deck, &deckTop);
            deckReset = 1;
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

    //print winners
    printWinners(numWinners, podium);


    free(players);
    return 0;
}
