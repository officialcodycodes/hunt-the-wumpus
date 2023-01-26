/*********************************************************************
** Program Filename: wumpus.cpp
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Implementation file for the Wumpus class. Contains constructor, destructor, setter, and member functions.
** Input: N?A
** Output: N?A
*********************************************************************/

#include "wumpus.h"

#include <iostream>

using namespace std;


/*********************************************************************
** Function: Wumpus()
** Description: Default constructor for the Wumpus class.
** Parameters: NONE
** Pre-Conditions: This class object is now in scope.
** Post-Conditions: Properly sets the name var to its corresponding character.
*********************************************************************/
Wumpus::Wumpus(){
    this->name = 'W';
    this->killed = false;
}


/*********************************************************************
** Function: ~Wumpus()
** Description: ddestructor called after the adventurer KILLS the Wumpus
** Parameters: NONE
** Pre-Conditions: Wumpus object is no longer in scope
** Post-Conditions: killed is set to true, Wumpus has been killed.
*********************************************************************/
Wumpus::~Wumpus(){
    this->killed = true;
}

/*********************************************************************
** Function: setKilled()
** Description: Mutator for the killed variable.
** Parameters: b
** Pre-Conditions: game.cpp wants to set the killed state of the Wumpus.
** Post-Conditions: killed variable is updated.
*********************************************************************/
void Wumpus::setKilled(bool b){
    this->killed = b;
}

/*********************************************************************
** Function: print_nearby_statement()
** Description: Function prints out the message if the user is adjacent to a room with this event.
** Parameters: NONE
** Pre-Conditions: game.cpp wants to print the nearby statement
** Post-Conditions: The nearby statement is printed.
*********************************************************************/
void Wumpus::print_nearby_statement() const{
    cout << "\x1B[35mYou smell a terrible stench.\033[0m" << endl;

}

/*********************************************************************
** Function: print_interaction_statement()
** Description: Function prints out the message if the user is INSIDE of a room with this event.
** Parameters: NONE
** Pre-Conditions: game.cpp wants to print the interaction statement
** Post-Conditions: The interaction statement is printed.
*********************************************************************/
void Wumpus::print_interaction_statement() const{
    cout << "\x1B[1;35mThe hungry Wumpus eats you after walking into its room.\033[0m" << endl;

}

/*********************************************************************
** Function: obtainEventChar()
** Description: Function that returns the name character of the corresponding event type.
** Parameters: NONE
** Pre-Conditions: game.cpp wants the event name character.
** Post-Conditions: Returns the char to game.cpp
*********************************************************************/
char Wumpus::obtainEventChar() const{
    return this->name;
}