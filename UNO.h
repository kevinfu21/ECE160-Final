#include <stdio.h>

//put all functions prototypes here
//FUNCTIONS 1 & 2 just to split the workload and make sure no merge crap happens
void test1(void);
void test2(void);



//FUNCTIONS 1 - 
void prompt(void); //initial setup prompts
void draw_board(); //draw the UI
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


void deal_cards(); //initial dealing
void draw_cards(); //draw card placed
int validate_turn(); //make sure u play right moves
void next_turn(); //what it sounds like
void skip(); //skip card
void reverse(); //reverse card

//FUNCTIONS 2 --




//Structs
//All cards, was thinking each player could just be an array of these?
struct Card {
    int ID; //for internal use, use RNG for distribution
    char *name; //offical name
    char color; //r,g,b,y
    char type; //Regular(r), special(s)
};


//4 colors: 0-9, draw 2, skip, reverse. 
struct Card cards[] = {
    {1, "Red 1", 'r', 'r'},
    //.....
};
