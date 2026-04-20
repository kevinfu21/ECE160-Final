#include <stdio.h>
#include "UNO.h"
#include <stdlib.h>
#include <time.h>

// Create full UNO deck (108 cards) 
void createDeck(Card deck[]) {
    Color colors[] = {RED, GREEN, BLUE, YELLOW};
    int index = 0;

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
void printDeck(Card deck[]) {
    for (int i = 0; i < DECK_SIZE; i++) {
        printf("%d %d\n", deck[i].ID, deck[i].color);
    }
}

void printHand(Card hand[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d %d ", hand[i].ID);
    }
    printf("\n");
}


void dealDeckStart(Player player[], int numPlayer, Card deck[], int *deckTop){
    for(int i = 0; i < numPlayer; i++){
        player[i].handSize = 7;
        for(int j = 0; j < 7; j++){
            player[i].hand[j] = deck[(*deckTop)++];
        }
    }
}