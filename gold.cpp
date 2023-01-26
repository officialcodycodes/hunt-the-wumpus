/*********************************************************************
** Program Filename: gold.cpp
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Implementation file for the Gold class. Contains constructor, destructor and member functions.
** Input: N?A
** Output: N?A
*********************************************************************/

#include "gold.h"

#include <iostream>

using namespace std;

/*********************************************************************
** Function: Gold()
** Description: Default constructor for the Gold class.
** Parameters: NONE
** Pre-Conditions: This class object is now in scope.
** Post-Conditions: Properly sets the name var to its corresponding character.
*********************************************************************/
Gold::Gold(){
    this->name = 'G';
    this->goldFound = false;
}


/*********************************************************************
** Function: ~Gold()
** Description: destructor called after the adventurer picks up the gold (THERE IS NO MORE GOLD IN THE CAVE)
** Parameters: NONE
** Pre-Conditions: Gold object is no longer in scope
** Post-Conditions: goldFound is set to true; the gold has been found!
*********************************************************************/
Gold::~Gold(){
    this->goldFound = true;
}

/*********************************************************************
** Function: print_nearby_statement()
** Description: Function prints out the message if the user is adjacent to a room with this event.
** Parameters: NONE
** Pre-Conditions: game.cpp wants to print the nearby statement
** Post-Conditions: The nearby statement is printed.
*********************************************************************/
void Gold::print_nearby_statement() const{
    cout << "\x1B[33mYou see a glimmer nearby.\033[0m\t\t" << endl;

}

/*********************************************************************
** Function: print_interaction_statement()
** Description: Function prints out the message if the user is INSIDE of a room with this event.
** Parameters: NONE
** Pre-Conditions: game.cpp wants to print the interaction statement
** Post-Conditions: The interaction statement is printed.
*********************************************************************/
void Gold::print_interaction_statement() const{
    cout << "\x1B[1;33mYou found the treasure!\033[0m\t\t" << endl;
}

/*********************************************************************
** Function: obtainEventChar()
** Description: Function that returns the name character of the corresponding event type.
** Parameters: NONE
** Pre-Conditions: game.cpp wants the event name character.
** Post-Conditions: Returns the char to game.cpp
*********************************************************************/
char Gold::obtainEventChar() const{
    return this->name;
}