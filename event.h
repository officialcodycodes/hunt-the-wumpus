/*********************************************************************
** Program Filename: event.h
** Author: Cody DePeel
** Date: 11-21-2022
** Description: Header file for the event class. Sets the member functions to pure virtual type.
** Input: N?A
** Output: N?A
*********************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <iostream>

using namespace std;

class Event{    
    protected:
        char name;
    public:
        Event();

        ~Event();
        
        // print statement when near room of event type
        virtual void print_nearby_statement() const = 0;
        // print statement when user is in this room
        virtual void print_interaction_statement() const = 0;
        
        virtual char obtainEventChar() const = 0;
        
};
#endif