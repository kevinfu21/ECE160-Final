#include <stdio.h>
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

void initializePlayers(Player *player, int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        player[i].ID = i;
        player[i].handSize = 0;
        printf("Player %d, what's your name?\n Name: ", i + 1);
        char temp[50];
        scanf("%s", temp);
        strcpy(player[i].name, temp);
    }
}
