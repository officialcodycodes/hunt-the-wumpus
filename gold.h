/*********************************************************************
** Program Filename: gold.h
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Header file for the Gold class. Contains class definition and prototypes.
** Input: N?A
** Output: N?A
*********************************************************************/
#ifndef GOLD_H
#define GOLD_H

#include "event.h"

using namespace std;

// Gold is inherited from Event
class Gold : public Event{
    protected:
        bool goldFound;
    public:
        Gold();

        ~Gold();

        void print_nearby_statement() const;
        void print_interaction_statement() const;
        char obtainEventChar() const;


        
};
#endif