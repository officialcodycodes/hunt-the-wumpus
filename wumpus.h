/*********************************************************************
** Program Filename: wumpus.h
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Header file for the Wumpus class. Contains class definition and prototypes.
** Input: N?A
** Output: N?A
*********************************************************************/

#ifndef WUMPUS_H
#define WUMPUS_H

#include "event.h"

using namespace std;

// Wumpus is inherited from Event
class Wumpus : public Event{
    protected:
        bool killed;
    public:
        Wumpus();

        ~Wumpus();

        // mutator
        void setKilled(bool);

        // member functions
        void print_nearby_statement() const;
        void print_interaction_statement() const;
        char obtainEventChar() const;

};
#endif