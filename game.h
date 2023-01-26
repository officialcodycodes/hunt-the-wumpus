/*********************************************************************
** Program Filename: game.h
** Author: Cody DePeel
** Date: 11/15/2022
** Description: Header file for the Game class (contains all of the function prototypes)
** of the Game class, as well as the actual Game class definition itself. Member vars,
** accessors, setters, constrctors, and destructors can be found here.
** Input: N?A
** Output: N?A
*********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "wumpus.h"
#include "gold.h"
#include "bats.h"
#include "pit.h"
#include "event.h"
#include "room.h"
#include "adventurer.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Game{
    private:
        vector <vector<Room> > cave;
        vector<Event*> eventPtrs;
        vector<Room*> roomPtrs;
        vector<Room*> trackedOriginalRoomPtrs;
        
        // int start_x, start_y, current_x, current_y; // coords of player
        // char direction;

        Adventurer user;
        Room* escapeRoom;
        
        bool isGameOver;
        bool debugMode;
        int caveSize;
    public:
        // constructor
        Game();


        // destructor 
        ~Game();

        // member functions
        int rand_index();
        void createEventPtrs();
        Room* get_room(int, int);
        void populateCave(int&, int&);
        void initializeCave();
        bool debugModeAsk();
        int caveSizeAsk();
        void gameStart();

        // debug mode printing
        void print_event_in_room(int, int&, int&, int&, int&, bool&);
        void debugFirstRowMiddlePlayer(int, int&, int&, int&, bool&);
        
        void debugFirstRowMiddle(int, int&);
        void debugFirstRow(int, int&);
        
        void debugMiddleRowsMiddle(int, int&);
        void debugMiddleRows(int, int&);

        void extraPrint(int, int&, bool&);

        void debugBottomRowMiddle(int, int&);
        void debugBottomRow(int, int&);
        
        // normal mode printing
        void firstRowMiddlePlayer(int, int&, int&);

        void firstRowMiddle(int, int&);
        void firstRow(int, int&);

        void middleRowMiddle(int, int&);
        void middleRows(int, int&);
        
        void bottomRowMiddle(int, int&);
        void bottomRow(int, int&);

        void print_cave(int);
        void print_coordinates();
        void printNearbyMessage();
        void generateBatTeleportNums(int&, int&);
        void updateGameStates(bool&);
        void roomInteraction();
        void displayInformation();
        
        void fireNorth();
        void fireSouth();
        void fireWest();
        void fireEast();
        void genNewWumpusRoom(int&, int&);
        void wumpusWakesUp();
        void extraArrowInstructions(bool&);
        void fireArrowInDirection(char&);
        void doFireArrows(char&);

        void doAvailableOptions(char&);
        void userInputsChoice(char&);

        bool checkIfWon();
        void deleteEventPtrs();
        void resetUserData();
        void pushBackNewEvents();
        void restartGame();
        void playWithNewSettings();
        void askSameSettings();
        void askReplay();
        void playGame();

};

#endif
