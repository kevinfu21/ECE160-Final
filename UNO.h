#include <stdio.h>

#define DECK_SIZE 108
#define MAX_PLAYERS 6 //arbitrary
#define STARTING_HAND 7

#define SKIP 10
#define REVERSE 11
#define DRAW2 12
#define WILD_CARD 13
#define WILD4 14

typedef enum {RED, GREEN, BLUE, YELLOW, WILD} Color;

//Structs
//card struct
typedef struct {
    int ID; //1-9, regular cards, 10-14, special cards
    Color color;
} Card;

//player struct
typedef struct {
    int ID;
    char name[25];
    Card hand[100];
    int handSize;
} Player;

typedef struct {
    char name[25];
    char placeText[25];
} Podium;


//test functions
void test1(void);
void test2(void);

//FUNCTIONS 1 - 


/* game setup / menu */
void prompt(int *drawUntilMatch, int *sz);
void gamemodes(int *drawUntilMatch, int *sz);
int computerTurn(Player *player, Card *topCard, Card deck[], int *deckTop);
int validTurn(Card userCard, Card *topCard, int computerMove);
void printOpponentCardCount(Player players[], int numPlayers);
void organizeHand(Player *player, int positionRemoved);


//FUNCTIONS 2 --
int getInt();
void initializePlayers(Player player[], int numPlayers);
void printPublicUI(int numPlayers, int order, Card *topCard, Player players[], int currentTurn);
int userTurn(Player players[], int numPlayers, Player *player, Card *topCard);
int checkUno(Player *player);
void UNO();
void screamUNO(Player *player, Card deck[], int deckTop, int currentTurn, Player players[]);

//CARDS.C 
void createDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void printDeck(Card deck[]);
void printHand(Card hand[], int size);
void dealDeckStart(Player player[], int numPlayer, Card deck[], int *deckTop);
void printAllDecks(Player player[], int numPlayer);
void draw(int n, int targetPlayerID, Player players[], int *deckTop, Card deck[]);
void chooseColor(Card *topCard, int returnID);
void resetDeck(Card deck[], int *deckTop);


/* setup / deck */
void createDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void printDeck(Card deck[]);   