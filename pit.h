/*********************************************************************
** Program Filename: pit.h
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Header file for the Pit class. Contains class definition and prototypes.
** Input: N?A
** Output: N?A
*********************************************************************/

#ifndef PIT_H
#define PIT_H

#include "event.h"

using namespace std;

// Pit is inherited from Event
class Pit : public Event{
    // No new data members for Pit
    public:
        Pit();

        // no destructor

        void print_nearby_statement() const;
        void print_interaction_statement() const;
        char obtainEventChar() const;



        
};
#endif