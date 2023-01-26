/*********************************************************************
** Program Filename: bats.h
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Header file for the Bats class. Contains class definition and function prototypes.
** Input: N?A
** Output: N?A
*********************************************************************/

#ifndef BATS_H
#define BATS_H

#include "event.h"

using namespace std;

// Bats is inherited from Event
class Bats : public Event{
    // No new data members for Bats
    public:
        Bats();

        // no destructor

        void print_nearby_statement() const;
        void print_interaction_statement() const;
        char obtainEventChar() const;
        
};
#endif