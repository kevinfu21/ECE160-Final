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
    printf("\nPlayer %d, %s, your turn!\n", currentTurn + 1, players[currentTurn].name);

    //print top card
    printf("Top card: ");
    printHand(topCard, 1);
}

//print user turn UI, players[] and numPLayers is unused, moved to publicUI. Changed to int to return ID.
int userTurn(Player players[], int numPlayers, Player *player, Card *topCard){
    int choice;

    if (player->handSize == 0) { //skipturn if won already
        return -2;
    }
    //ISSUE - WINNER CAN STILL BE INTERACTED WITH, THIS IS JUST A TEMP WORKAROUND


    //make sure no peeky peeky
    printf("Type 0 when you're ready: ");
    int a;
    do {
        scanf("%d", &a);
    } while(a != 0);

    //print player's hand
    printf("Your Cards: \n");
    printHand(player->hand, player->handSize);

    printf("Which card would you like to play? (enter index 1-%d or type 0 to draw. Type -1 to reset deck.): ", player->handSize);
    do{
        scanf("%d", &choice);

        if (choice == 0) { //draw cards
            return 0;
        }

        if (choice == -1) { //reset deck
            return -1;
        }
    } while((choice < 1 || choice > player->handSize) || !validTurn(player->hand[choice-1], topCard));

    int ID = player->hand[choice-1].ID;
    *topCard = player->hand[choice - 1];
    organizeHand(player, choice-1);
    //Check if card follows rule, play card, remove from playersDeck

    return ID;
}

int checkUno(Player *player) {
    if (player->handSize == 1) {
        return 1;
    }
    else return 0;
}

void screamUNO(Player *player, Card deck[], int deckTop, int currentTurn, Player players[]) {
    //make some space
    for (int i = 0; i < 50; i++){
    printf("\n");
    }
    //print the big boi UNO
    UNO();

    printf("Player %d, %s, has one card! Scream UNO!!\n\n", currentTurn + 1, player->name);

    printf("Type 0 if %s is safe, and 1 if they failed to say UNO in time.", player->name);

    for (int i = 0; i < 10; i++){
    printf("\n");
    }

    printf("Response: ");
    int safe;
    scanf("%d", &safe);

    if(safe) {
        draw(2, currentTurn, players, &deckTop, deck);
    }
}

void UNO() {
    printf("                                            ,---,  \n");
printf("                       ,--.    ,----..   ,`--.' |  \n");
printf("                     ,--.'|   /   /   \\  |   :  :  \n");
printf("         ,--,    ,--,:  : |  /   .     : '   '  ;  \n");
printf("       ,'_ /| ,`--.'`|  ' : .   /   ;.  \\|   |  |  \n");
printf("  .--. |  | : |   :  :  | |.   ;   /  ` ;'   :  ;  \n");
printf(",'_ /| :  . | :   |   \\ | :;   |  ; \\ ; ||   |  '  \n");
printf("|  ' | |  . . |   : '  '; ||   :  | ; | ''   :  |  \n");
printf("|  | ' |  | | '   ' ;.    ;.   |  ' ' ' :;   |  ;  \n");
printf(":  | | :  ' ; |   | | \\   |'   ;  \\; /  |`---'. |  \n");
printf("|  ; ' |  | ' '   : |  ; .' \\   \\  ',  /  `--..`;  \n");
printf(":  | : ;  ; | |   | '`--'    ;   :    /  .--,_     \n");
printf("'  :  `--'   \\'   : |         \\   \\ .'   |    |`.  \n");
printf(":  ,      .-./;   |.'          `---`     `-- -`, ; \n");
printf(" `--`----'    '---'                        '---`\"  \n");
}

                                            
void checkWin(Player *player, int *numWinners, Podium podium[], int *winners) {
    if (player->handSize == 0) {
        strcpy(podium[*numWinners].name, player->name);

        switch (*numWinners) {
            case 0:
            strcpy(podium[*numWinners].placeText, "First Place");
            *winners = 1; //place where done
            break;
            case 1: 
            strcpy(podium[*numWinners].placeText, "Second Place");
            //support for more winners if u want to implement that
            break;
        }
            (*numWinners)++;
    }
}



void printWinners(int numWinners, Podium podium[]) {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
    for (int i = 0; i < numWinners; i++) {
        printf("%s: %s\n", podium[i].placeText, podium[i].name);
    }
}