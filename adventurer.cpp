/*********************************************************************
** Program Filename: adventurer.cpp
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Implementation file for the Adventurer class. Contains constructors, getters, setters, and mem funcs
** Input: N?A
** Output: N?A
*********************************************************************/

#include "adventurer.h"

#include <iostream>

using namespace std;

/*********************************************************************
** Function: Adventurer()
** Description: default constructor for the Adventurer class
** Parameters: NONE
** Pre-Conditions: Adventurer object is in scope.
** Post-Conditions: Sets the member vars to a good value for the game.
*********************************************************************/
Adventurer::Adventurer(){
    this->numArrows = 3;
    this->hasGold = false;
    this->killedWumpus = false;

    this->currentRoom = NULL;

}

/*********************************************************************
** Function: Adventurer() 
** Description: Non default constructor for the Adventurer class
** Parameters: Room *r
** Pre-Conditions: Adventurer obj is in scope
** Post-Conditions: Sets the member vars accordingly
*********************************************************************/
Adventurer::Adventurer(Room *r){
    this->numArrows = 3;
    this->hasGold = false;
    this->killedWumpus = false;
    
    this->currentRoom = r;
}

// destructor
// Adventurer::~Adventurer(){

// }

// Accessors
/*********************************************************************
** Function: getNumArrows()
** Description: Getter for the num of arrows
** Parameters: NONE
** Pre-Conditions: game.cpp needs the num of arrows
** Post-Conditions: Num of arrows is returned
*********************************************************************/
int Adventurer::getNumArrows(){
    return this->numArrows;
}

/*********************************************************************
** Function: getHasGold()
** Description: Getter for if the user has gold
** Parameters: NONE
** Pre-Conditions: game.cpp needs the HasGold
** Post-Conditions: hasGold bool is returned
*********************************************************************/
bool Adventurer::getHasGold(){
    return this->hasGold;
}

/*********************************************************************
** Function: getKilledWumpus()
** Description: Getter for if the user killedWumpus
** Parameters: NONE
** Pre-Conditions: game.cpp needs if the user killed the Wumpus
** Post-Conditions: killedWumpus bool is returned
*********************************************************************/
bool Adventurer::getKilledWumpus(){
    return this->killedWumpus;
}

/*********************************************************************
** Function: getCurrentRoom()
** Description: Getter for the currentRoom()
** Parameters: NONE
** Pre-Conditions: game.cpp needs the current room of the user
** Post-Conditions: return a room* to game.cpp
*********************************************************************/
Room* Adventurer::getCurrentRoom(){
    return this->currentRoom;
}

// Mutators
/*********************************************************************
** Function: setNumArrows()
** Description: Mutator for the number of arrows
** Parameters: num
** Pre-Conditions: game.cpp wants to set the num of arrows
** Post-Conditions: num of arrows is changed
*********************************************************************/
void Adventurer::setNumArrows(int num){
    this->numArrows = num;
}

/*********************************************************************
** Function: setHasGold()
** Description: Mutator for HasGold
** Parameters: g
** Pre-Conditions: game.cpp wants to update hasGold
** Post-Conditions: hasGold is updated
*********************************************************************/
void Adventurer::setHasGold(bool g){
    this->hasGold = g;
}

/*********************************************************************
** Function: setKilledWumpus()
** Description: Mutator for killedWumpus
** Parameters: NONE
** Pre-Conditions: game.cpp wants to update killedWumpus
** Post-Conditions: killedWumpus is updated
*********************************************************************/
void Adventurer::setKilledWumpus(bool w){
    this->killedWumpus = w;
}

/*********************************************************************
** Function: setCurrentRoom()
** Description: Mutator for currentRoom
** Parameters: NONE
** Pre-Conditions: game.cpp wants to update the user's current room
** Post-Conditions: currentRoom is updated.
*********************************************************************/
void Adventurer::setCurrentRoom(Room* r){
    this->currentRoom = r;
}