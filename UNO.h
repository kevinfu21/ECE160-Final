#include <stdio.h>

#define DECK_SIZE 108
#define MAX_PLAYERS 4
#define STARTING_HAND 7

#define SKIP 10
#define REVERSE 11
#define DRAW2 12
#define WILD_CARD 13
#define WILD4 14

typedef enum {RED, GREEN, BLUE, YELLOW, WILD} Color;

//Structs
typedef struct {
    int ID;
    Color color;
} Card;

typedef struct {
    Card hand[100];
    int handSize;
} Player;

//test functions
void test1(void);
void test2(void);

//FUNCTIONS 1 - 
/*
this'll one will be a pretty big one (draw_board)
INCLUDE SPACE FOR:

For EVERYONE to see:
- Current card
- The cards before the current one, if time allows
- Turn number
- Number of cards each player has

- At the bottom, each person's "Menu," theoretically "PRIVATE" for each player, with:
    - Player's card
take in the proper inputs to be able to display this
*/

/* game setup / menu */
void prompt(int *drawUntilMatch, int *sz);
void gamemodes(int *drawUntilMatch, int *sz);
void initializePlayers(Player *player, int numPlayer);
void userTurn(Player players[], int numPlayers, Player *player, Card *topCard);
void computerTurn(Player *player, Card *topCard);
int validTurn(Card userCard, Card *topCard);
void printOpponentCardCount(Player players[], int numPlayers);
void organizeHand(Player *player, int positionRemoved);

void deal_cards(); //initial dealing
void draw_cards(); //draw card placed
int validate_turn(); //make sure u play right moves
void next_turn(); //what it sounds like
void skip(); //skip card
void reverse(); //reverse card

//FUNCTIONS 2 --



//CARDS.C 
void createDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void printDeck(Card deck[]);
void printHand(Card hand[], int size);
void dealDeckStart(Player player[], int numPlayer, Card deck[], int *deckTop);


/* setup / deck */
void createDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void printDeck(Card deck[]);   