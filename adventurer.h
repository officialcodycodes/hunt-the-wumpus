/*********************************************************************
** Program Filename: adventurer.h
** Author: Cody DePeel
** Date: 11/15/2022
** Description: Header file for the Adventurer class (contains all of the function prototypes)
** of the Adventurer class, as well as the actual Adventurer class definition itself. Member vars,
** accessors, setters, constrctors, and destructors can be found here.
** Input: N?A
** Output: N?A
*********************************************************************/

#ifndef ADVENTURER_H
#define ADVENTURER_H

#include "room.h"

#include <iostream>
#include <vector>

using namespace std;

class Adventurer{
    protected:
        int numArrows;
        bool hasGold;
        bool killedWumpus;
        Room* currentRoom;

    public:
        Adventurer(); // default constructor
        Adventurer(Room *r);

        // ~Adventurer(); // destructor

        // Accessors
        int getNumArrows();
        bool getHasGold();
        bool getKilledWumpus();
        Room* getCurrentRoom();


        // Mutators
        void setNumArrows(int);
        void setHasGold(bool);
        void setKilledWumpus(bool);
        void setCurrentRoom(Room*);

                
};
#endif