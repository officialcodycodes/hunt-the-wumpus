/*********************************************************************
** Program Filename: driver.cpp
** Author: Cody DePeel
** Date: 11-21-2022
** Description: the driver file for the program, contains a game object and calls the playGame(), which runs through the entire game
** Input: N?A
** Output: N?A
*********************************************************************/
#include "game.h"
#include "adventurer.h"
#include "room.h"
#include "event.h"
#include "bats.h"
#include "gold.h"
#include "wumpus.h"
#include "pit.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*********************************************************************
** Function: main
** Description: The main() function for the program. Contains a declaration of a game object, as well as calling playGame() function within the Game class.
** Parameters: NONE
** Pre-Conditions: Program is running
** Post-Conditions: Game has run at least once and all memory has been freed.
*********************************************************************/
int main(){
    /* initalize random seed */
    srand(time(NULL));

    
    Game g;
    g.playGame();

    return 0;
}