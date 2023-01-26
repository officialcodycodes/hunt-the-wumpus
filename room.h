/*********************************************************************
** Program Filename: room.h
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Header file for the Room class. Contains class definitions, function prototypes, etc.
** Input: N?A
** Output: N?A
*********************************************************************/
#ifndef ROOM_H
#define ROOM_H

#include "event.h"

#include <iostream>
#include <vector>

using namespace std;

class Room{
    private:
        Event* e;
        int row;
        int col;
        bool hasEvent; 
    public:
        Room(); // default constructor

        Room(int, int); // non-default constructor if given both the row and col #
        ~Room(); // destructor

        // getters
        int getRow();
        int getCol();
        bool getHasEvent();
        Event* getEvent();

        // setters
        void setRow(int);
        void setCol(int);
        void setHasEvent(bool);
        void setEvent(Event* event);

        // member functions
        bool is_empty();


};
#endif