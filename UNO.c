#include <stdio.h>

void prompt(int *players, int *computers){
    int choice = 0;
    printf("(1) Start Game\n");
    printf("(2) Game Setting\n");
    printf("(3) Player Setting\n");
    scanf();
/*
    printf("Number of players: \n");
    scanf("%d", players);
    printf("Number of Computers: \n");
    scanf("%d", computers);
    */
}

int main(){
    int players;
    int computers;
    printf("Hello! This is UNO : ).\n");
    prompt(&players, &computers);

    printf("Players: %d\n", players);
    printf("Computers: %d\n", computers);

    return 0;
}