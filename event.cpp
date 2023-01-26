/*********************************************************************
** Program Filename: event.cpp
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Implementation file for the event class. Very sparse since this is an abstract class.
** Input: N?A
** Output: N?A
*********************************************************************/

#include "event.h"

#include <iostream>

using namespace std;


/*********************************************************************
** Function: Event()
** Description: default constructor for the event class
** Parameters: NONE
** Pre-Conditions: Event class is abstract, so this should not run
** Post-Conditions: Event class is abstract, so this should not run
*********************************************************************/
Event::Event(){
    this->name = 'E'; // set to E for event, this constructor should not affect the derived classes of event
}


/*********************************************************************
** Function: ~Event()
** Description: destructor for the event class
** Parameters: NONE
** Pre-Conditions: Event class is abstract, so this should not run
** Post-Conditions: Event class is abstract, so this should not run
*********************************************************************/
Event::~Event(){
    
}



