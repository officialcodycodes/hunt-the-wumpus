/*********************************************************************
** Program Filename: room.cpp
** Author: Cody DePeel
** Date: 11-21-2022
** Description:
** Input: N?A
** Output: N?A
*********************************************************************/

#include "room.h"
#include "event.h"

#include <iostream>

using namespace std;


/*********************************************************************
** Function: Room()
** Description: Default constructor for the Room class.
** Parameters: NONE
** Pre-Conditions: Room object is in scope
** Post-Conditions: Proper values have been set up for the room obj
*********************************************************************/
Room::Room(){
    this->row = -1;
    this->col = -1;
    this->hasEvent = false;
    this->e = NULL;
}


/*********************************************************************
** Function: Room()
** Description: Non default constructor for the Room Class.
** Parameters: r, c
** Pre-Conditions: Room object with arguments is in scope
** Post-Conditions: The new room object is initialized.
*********************************************************************/
Room::Room(int r, int c){
    this->row = r;
    this->col = c;
    
    // This constructor constructs an EMPTY room. It has no event (it is not pointing to gold, wumpus, bats, or pit), which means the bool is FALSE. 
    this->hasEvent = false;
    this->e = NULL;
}


/*********************************************************************
** Function: ~Room()
** Description: Destructor for the Room Class
** Parameters: NONE
** Pre-Conditions: Room object is out of scope.
** Post-Conditions: Room object is properly deleted and memory is freed.
*********************************************************************/
Room::~Room(){
    if(this->e != NULL){
        delete this->e;
        this->e = NULL;
    }
}

// Accessors
/*********************************************************************
** Function: getRow()
** Description: Accessor for the row variable in the room
** Parameters: NONE
** Pre-Conditions: game.cpp needs a row for the room in question.
** Post-Conditions: The row is returned
*********************************************************************/
int Room::getRow(){
    return this->row;
}

/*********************************************************************
** Function: getCol()
** Description: Accessor for the col variable in the room
** Parameters: NONE
** Pre-Conditions: game.cpp needs a col for the room in question.
** Post-Conditions: The col is returned
*********************************************************************/
int Room::getCol(){
    return this->col;
}

/*********************************************************************
** Function: getHasEvent()
** Description: Accessor for the hasEvent variable
** Parameters: NONE
** Pre-Conditions: game.cpp needs to see if a room has an event
** Post-Conditions: A boolean is returned to game.cpp
*********************************************************************/
bool Room::getHasEvent(){
    return this->hasEvent;
}

/*********************************************************************
** Function: getEvent()
** Description: Accessor for the event pointer variable
** Parameters: NONE
** Pre-Conditions: game.cpp needs the event ptr
** Post-Conditions: An event ptr is returned to game.cpp
*********************************************************************/
Event* Room::getEvent(){
    return this->e;
}

// Mutators
/*********************************************************************
** Function: setRow()
** Description: Mutator for the row variable in the room
** Parameters: NONE
** Pre-Conditions: game.cpp needs to set a row for the room in question.
** Post-Conditions: The row is set
*********************************************************************/
void Room::setRow(int r){
    this->row = r;
}

/*********************************************************************
** Function: setCol()
** Description: Mutator for the col variable in the room
** Parameters: NONE
** Pre-Conditions: game.cpp needs to set a col for the room in question.
** Post-Conditions: The new col is set
*********************************************************************/
void Room::setCol(int c){
    this->col = c;
}

/*********************************************************************
** Function: setHasEvent()
** Description: Mutator for the hasEvent variable
** Parameters: NONE
** Pre-Conditions: game.cpp needs to set if the room has an event
** Post-Conditions: A boolean is set
*********************************************************************/
void Room::setHasEvent(bool truth){
    this->hasEvent = truth;
}

/*********************************************************************
** Function: setEvent()
** Description: Mutator for the event pointer variable
** Parameters: NONE
** Pre-Conditions: game.cpp needs to set the event ptr
** Post-Conditions: An event ptr is set to game.cpp
*********************************************************************/
void Room::setEvent(Event* event){
    this->e = event;

    // Now, the current room has an event. We need to set the boolean in this class to true!
    this->hasEvent = true;
}

// Member functions
/*********************************************************************
** Function: is_empty()
** Description: Member function for finding if the event ptr is empty
** Parameters: NONE
** Pre-Conditions: game.cpp needs to see if a room is empty
** Post-Conditions: A boolean is returned
*********************************************************************/
bool Room::is_empty(){
    return this->e == NULL;
}