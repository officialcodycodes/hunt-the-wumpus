/*********************************************************************
** Program Filename: pit.cpp
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Implementation file for the Pit class. Contains constructor and member functions.
** Input: N?A
** Output: N?A
*********************************************************************/

#include "pit.h"

#include <iostream>

using namespace std;

/*********************************************************************
** Function: Pit()
** Description: Default constructor for the Pit class.
** Parameters: NONE
** Pre-Conditions: This class object is now in scope.
** Post-Conditions: Properly sets the name var to its corresponding character.
*********************************************************************/
Pit::Pit(){
    this->name = 'P';
}

/*********************************************************************
** Function: print_nearby_statement()
** Description: Function prints out the message if the user is adjacent to a room with this event.
** Parameters: NONE
** Pre-Conditions: game.cpp wants to print the nearby statement
** Post-Conditions: The nearby statement is printed.
*********************************************************************/
void Pit::print_nearby_statement() const{
    cout << "\x1B[90mYou feel a breeze.\033[0m" << endl;
    
}

/*********************************************************************
** Function: print_interaction_statement()
** Description: Function prints out the message if the user is INSIDE of a room with this event.
** Parameters: NONE
** Pre-Conditions: game.cpp wants to print the interaction statement
** Post-Conditions: The interaction statement is printed.
*********************************************************************/
void Pit::print_interaction_statement() const{
    cout << "\x1B[1;90mYou fell into a bottomless pit.\033[0m" << endl;
}

/*********************************************************************
** Function: obtainEventChar()
** Description: Function that returns the name character of the corresponding event type.
** Parameters: NONE
** Pre-Conditions: game.cpp wants the event name character.
** Post-Conditions: Returns the char to game.cpp
*********************************************************************/
char Pit::obtainEventChar() const{
    return this->name;
}