#include <stdio.h>
#include "UNO.h"
#include <stdlib.h>
#include <time.h>

// Create full UNO deck (108 cards) 
void createDeck(Card deck[]) {
    Color colors[] = {RED, GREEN, BLUE, YELLOW, WILD};
    int index = 0;

    //colored cards
    for (int i = 0; i < 4; i++) {
        Color c = colors[i];

        // one 0
        deck[index++] = (Card){0, c};

        // two of 1–9
        for (int v = 1; v <= 9; v++) {
            deck[index++] = (Card){v, c};
            deck[index++] = (Card){v, c};
        }

        // action cards (2 each)
        deck[index++] = (Card){SKIP, c};
        deck[index++] = (Card){SKIP, c};

        deck[index++] = (Card){REVERSE, c};
        deck[index++] = (Card){REVERSE, c};

        deck[index++] = (Card){DRAW2, c};
        deck[index++] = (Card){DRAW2, c};
    }

    // wild cards
    for (int i = 0; i < 4; i++)
        deck[index++] = (Card){WILD_CARD, WILD};

    for (int i = 0; i < 4; i++)
        deck[index++] = (Card){WILD4, WILD};
}

void shuffleDeck(Card deck[]){
    for(int i = DECK_SIZE-1; i > 0; i--){
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

//for testing: print decks by ID and color enum
void printDeck(Card deck[]) {
    for (int i = 0; i < DECK_SIZE; i++) {
        printf("%d %d\t", deck[i].ID, deck[i].color);
    }
}

//for testing: print all player hands
void printAllDecks(Player player[], int numPlayer) {
    for (int i = 0; i < numPlayer; i++) {
        printf("Player %s's deck: ", player[i].name);
        printDeck(player[i].hand);
        printf("\n");
    }
}

//print cards, tab separated
void printHand(Card hand[], int size) {
    for (int i = 0; i < size; i++) {
        int curCard = hand[i].ID;

        // set color
        switch (hand[i].color) {
            case RED:    printf("\033[31m"); break;
            case GREEN:  printf("\033[32m"); break;
            case BLUE:   printf("\033[34m"); break;
            case YELLOW: printf("\033[33m"); break;
            case WILD:   printf("\033[35m"); break;
        }
        
        // print card value
        if (curCard >= 0 && curCard <= 9) {
            printf("%d", curCard);
        } else {
            switch (curCard) {
                case 10: printf("SKIP"); break;
                case 11: printf("REVERSE"); break;
                case 12: printf("DRAW2"); break;
                case 13: printf("WILD"); break;
                case 14: printf("WILD4"); break;
                default: printf("?"); break;
            }
        }

        // reset color + spacing
        printf("\033[0m  ");
    }
    printf("\n");
}

//deal starter cards
void dealDeckStart(Player player[], int numPlayer, Card deck[], int *deckTop){
    for(int i = 0; i < numPlayer; i++){
        player[i].handSize = 7;
        for(int j = 0; j < 7; j++){
            player[i].hand[j] = deck[(*deckTop)++];
        }
    }
}

//draw n cards
void draw(int n, int targetPlayerID, Player players[], int *deckTop, Card deck[]) {
    for (int i = 0; i < n; i++) {
        players[targetPlayerID].hand[players[targetPlayerID].handSize] = deck[(*deckTop)++];
        players[targetPlayerID].handSize++;
    }
}

int chooseColor(Card *topCard, int returnID) {
    printf("What color? (Enter index 1-4)\n");
    Card colorDeck[4] = {
        {1, RED},
        {2, GREEN},
        {3, BLUE},
        {4, YELLOW}
    };
    printHand(colorDeck, 4);

    printf("Enter number: ");
    int color;
    scanf("%d", &color);
    color--;

    topCard->color = color;
    topCard->ID = returnID;
}


//reshuffle deck
void resetDeck(Card deck[], int *deckTop) {
    *deckTop = 0;
    createDeck(deck);
    shuffleDeck(deck);
}
