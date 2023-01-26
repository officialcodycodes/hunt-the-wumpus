/*********************************************************************
** Program Filename: game.cpp
** Author: Cody DePeel
** Date: 11-21-2022
** Description:
** Input: N?A
** Output: N?A
*********************************************************************/

#include "game.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*********************************************************************
** Function: Game::Game()
** Description: The default constructor for the Game class.
** Parameters: NONE
** Pre-Conditions: Game object has been declared, now its member vars need to be initialized.
** Post-Conditions: Sets variables isGameOver and cheatMode to false.
*********************************************************************/
Game::Game(){
    // I added a member variable to the Game class, and it is a boolean that will change IF the game is over (all books are laid down and the player with the most books wins)
    this->isGameOver = false;
    
    // // Cheat mode auto defaults to false.
    // this->debugMode = false;
    
    // ask if the player wants to access cheat mode
    this->debugMode = debugModeAsk();

    // ask the user for the size of the cave
    this->caveSize = caveSizeAsk();

    initializeCave();

    cout << this->cave.size() << endl;
	cout << this->cave[0].size() << endl;
    
    int spawn_x, spawn_y;
    // Now, populate the cave
    populateCave(spawn_x, spawn_y);

    this->user.setCurrentRoom(get_room(spawn_x, spawn_y)); // sets the adventurer's current room (their starting room)
    this->escapeRoom = this->user.getCurrentRoom(); // sets the escapeRoom for this specific game

    cout << "SPAWN X (Row): " << this->user.getCurrentRoom()->getRow() << endl;
    cout << "SPAWN Y (Col): " << this->user.getCurrentRoom()->getCol() << endl;

    // char eventChar;
    // for(int i = 0; i < this->roomPtrs.size(); i++){
    //     eventChar = this->roomPtrs[i]->getEvent()->obtainEventChar();
    //     cout << "Room @ " << i << ": " << eventChar << "(" << this->roomPtrs[i]->getRow() << "," << this->roomPtrs[i]->getCol() << ")" << endl;
    // }
   
}

/*********************************************************************
** Function: ~Game()
** Description: Destructor for the game class.
** Parameters: NONE
** Pre-Conditions: Game object is out of scope
** Post-Conditions: The game object is successfully destructed.
*********************************************************************/
Game::~Game(){
    //delete this->user;
}


/*********************************************************************
** Function: rand_index()
** Description: Generates a random int within the scope of the program (with respect to the cave Size)
** Parameters: NONE
** Pre-Conditions: rand_index() is called
** Post-Conditions: A random number from 0 to the cave size is generated and returned as an int.
*********************************************************************/
int Game::rand_index(){
    /* initalize random seed */
    //srand(time(NULL));

    int randomNum = rand() % this->caveSize; // 0-however big the user inputted the size
    return randomNum;
}

/*********************************************************************
** Function: createEventPtrs()
** Description: Function creates the event ptrs and adds them to the eventPtrs vector within the game object.
** Parameters: NONE
** Pre-Conditions: Current game object is being constructed
** Post-Conditions: All of the events have been added to the eventPtr vector.
*********************************************************************/
void Game::createEventPtrs(){
    // 2 pits
    this->eventPtrs.push_back(new Pit());
    this->eventPtrs.push_back(new Pit());
    // 2 bats
    this->eventPtrs.push_back(new Bats());
    this->eventPtrs.push_back(new Bats());
    // 1 wumpus
    this->eventPtrs.push_back(new Wumpus());
    // 1 gold
    this->eventPtrs.push_back(new Gold());
}

/*********************************************************************
** Function: get_room()
** Description: Returns the room given two different indices (the row and col)
** Parameters: int randi, int randj
** Pre-Conditions: A function wants the room of two indices
** Post-Conditions: The room is returned as a room pointer.
*********************************************************************/
Room* Game::get_room(int randi, int randj){
    Room* r = &cave[randi][randj];
    return r;
}

/*********************************************************************
** Function: populateCave()
** Description: Populates the cave member variable within the current Game object.
** Parameters: int &spawn_x, int &spawn_y
** Pre-Conditions: The cave has been initialized but not populated.
** Post-Conditions: The cave vector has been populated with respect to the user-inputted cave size.
*********************************************************************/
void Game::populateCave(int &spawn_x, int &spawn_y){
    // We need 2 pits, 2 bats, 1 wumpus, 1 gold, and 1 adventurer.
    createEventPtrs();

    int randi, randj; // declare ints
    // cout << "EventPtrs.size():  " << this->eventPtrs.size() << endl;
    
    // do this for all of the events
    for(int i = 0; i < 6; i++){
        // find an empty room
        do{
            randi = rand_index();
            randj = rand_index();
        }while (!this->cave[randi][randj].is_empty());

        // after finding an empty room, place the LAST event of the eventPtrs vector in that room
        this->cave[randi][randj].setEvent(this->eventPtrs.back());

        // add the event to the roomPtrs vector if the user wants to play the same game again (same locations of events)
        // We can track the rooms this way
        this->roomPtrs.push_back(get_room(randi, randj));
        this->trackedOriginalRoomPtrs.push_back(get_room(randi, randj));
        // cout << "roomPtrs.size():  " << this->roomPtrs.size() << endl;
        // cout << "roomPtrs.back():  " << this->roomPtrs.back()->getEvent()->obtainEventChar()<< endl;
        // cout << "EventPtrs.at(" << i << "): " << this->eventPtrs[i]->obtainEventChar() << endl;
        // cout << "roomPtrs.at(" << i << "): " << this->roomPtrs[i]->getEvent()->obtainEventChar() << endl;

        // after adding that event, remove it from the eventPtrs vector so we won't add it again accidentally
        this->eventPtrs.pop_back();
        // cout << "AFTER POP_BACK:   EventPtrs.size():  " << this->eventPtrs.size() << endl;


    }

    // Now, find an empty room for the spawning point of the adventurer
    do{
        randi = rand_index();
        randj = rand_index();
    }while (!this->cave[randi][randj].is_empty());

    spawn_x = randi;
    spawn_y = randj;

}

/*********************************************************************
** Function: initializeCave()
** Description: Initializes the cave using the user-inputted cave size.
** Parameters: NONE
** Pre-Conditions: Cave vector has been declared but not initialized.
** Post-Conditions: Rooms are added to the cave vector's rows and columns
*********************************************************************/
void Game::initializeCave(){
    /* Yoinked from Week 8 slides */
    // Cave is a square, so we use the CaveSize var for both the rows and cols
    for(int i = 0; i < this->caveSize; i++){
        vector<Room> row_vec; // declare a vector for one of the rows
        
        for(int j = 0; j < this->caveSize; j++){
            row_vec.push_back(Room(i, j));
        }

        // Now add that row to the 2d vector (the cave)
        cave.push_back(row_vec);
    }
    
}

/*********************************************************************
** Function: debugModeAsk()
** Description: Asks the user if they want to enable or disable Debug mode for the session
** Parameters: NONE
** Pre-Conditions: Program needs to know whether or not to enable debug mode
** Post-Conditions: the member var DebugMode is either enabled or disabled for the current Game object.
*********************************************************************/
bool Game::debugModeAsk(){
    int input;
    cout << "Would you like to enter debug mode? (1) Yes, (2) No" << endl;
    cin >> input;
    
    if(input == 1){
        cout << "Debug Mode Enabled." << endl;
        cin.clear();  //So there isn't a bug for the next user input
        return true;
    }
    else{
        cout << "Debug Mode Disabled." << endl;
        cin.clear();  //So there isn't a bug for the next user input
        return false;
    }

}

/*********************************************************************
** Function: caveSizeAsk()
** Description: Asks the user for the size of the cave and saves that value to the current Game object
** Parameters: NONE
** Pre-Conditions: Program needs the caveSize to populate the cave vector
** Post-Conditions: Cave size is obtained and is returned back to the constructor
*********************************************************************/
int Game::caveSizeAsk(){
    int size;
    cout << "Please enter a size (greater than 3) for the Wumpus cave: ";
    
    // Check to see if the input was an int and it was greater than 3
    while(!(cin >> size) || !(size > 3)){
        cout << "Error: enter a valid number: ";

        // Clear the previous input
        cin.clear();

        // Discard prev input
        cin.ignore(123, '\n');
    }
    
    return size;
}

/*********************************************************************
** Function: gameStart()
** Description: Safeguard function to make sure that the game is NOT over
** Parameters: NONE
** Pre-Conditions: playGame() begins after being called in main
** Post-Conditions: isGameOver is set to false.
*********************************************************************/
void Game::gameStart(){
    // Make sure the isGameOver state is set to false, because the user wants to restart
    this->isGameOver = false;
    

    // // ask if the player wants to access cheat mode
    // this->debugMode = debugModeAsk();


}

/*********************************************************************
** Function: print_event_in_room
** Description: Prints the event indicator WITHIN the room it is in on the cave map
** Parameters: size, x, j, z, i, check
** Pre-Conditions: A part of the cave map has already been printed
** Post-Conditions: The event that the room is in is printed to the map
*********************************************************************/
void Game::print_event_in_room(int size, int &x, int &j, int &z, int &i, bool &check){
    if((j != 0) && (j != (size - 1)) && (x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol())){
        cout << "     " << this->roomPtrs[z]->getEvent()->obtainEventChar() << "    ";
        j++;
    }
    // conditional if player is in this part of the cave
    else if(j == 0 && (x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol())){
        cout << "║    " << this->roomPtrs[z]->getEvent()->obtainEventChar() << "    ";
        j++;
    }
    // conditional if player is in this part of the cave
    else if(j == (size - 1) && (x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol())){
        cout << "     " << this->roomPtrs[z]->getEvent()->obtainEventChar() << "    ║" << endl;
        check = true;
        j+=5;
        i++;
    }
}


/*********************************************************************
** Function: debugFirstRowMiddlePlayer
** Description: Part of the printing cave function, where the player and event are in the SAME room
** Parameters: size, x, j, z, check
** Pre-Conditions: Top of the first debug row has been printed
** Post-Conditions: The middle part of the first row squares is printed.
*********************************************************************/
void Game::debugFirstRowMiddlePlayer(int size, int &x, int &j, int &z, bool &check){
    if((j != 0) && (j != (size - 1)) ){
        cout << "     " << this->roomPtrs[z]->getEvent()->obtainEventChar() << "*   ";
        j++;
    }
    // conditional if player is in this part of the cave
    else if(j == 0){
        cout << "║    " << this->roomPtrs[z]->getEvent()->obtainEventChar() << "*   ";
        j++;

    }
    // conditional if player is in this part of the cave
    else if(j == (size - 1)){
        cout << "     " << this->roomPtrs[z]->getEvent()->obtainEventChar() << "*   ║" << endl;
        check = true;
        j++;
    }
}

/*********************************************************************
** Function: debugFirstRowMiddle()
** Description: Part of the printing cave function, where the player and event are in the SAME room
** Parameters: size, x
** Pre-Conditions: The top of the first row is printed.
** Post-Conditions: The middle of the first row is printed.
*********************************************************************/
void Game::debugFirstRowMiddle(int size, int &x){
    bool check = false;
    // Middle of square
    /* Add an if statement if there is cheat mode so the user can see what event is in that square */
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < size; j++){
            
            // If statement has an opening in the box to indicate the passage for the user
            if(i == 1){
                
                // if statement when there is an event in the room in question
                for(int z = 0; z < this->roomPtrs.size(); z++){
                    // If the player is in a room with an event
                    if((x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol()) && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
                        //cout << "in here";
                        debugFirstRowMiddlePlayer(size, x, j, z, check);
                    }
                    // If there is an event in a room
                    else if((x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol())){
                        //cout << "not here";
                        print_event_in_room(size, x, j, z, i, check);
                    }

                }
                
                // call a different function that will print different lines if the user happens to be in THAT room
                if(x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol()){
                    //cout << "here";
                    firstRowMiddlePlayer(size, x, j);
                }
                else{
                    
                    extraPrint(size, j, check);
                    
                }
            }
            else{
                cout << "║         ";
                if(j == size - 1)
                    cout << "║" << endl;
            }
        }
    }
}

/*********************************************************************
** Function: debugFirstRow()
** Description: Main function for printing the first row of the cave map. Contains print statements for the top of the row.
** Parameters: size, x
** Pre-Conditions: Program needs to print out the cave.
** Post-Conditions: The first row of the cave map has been printed out.
*********************************************************************/
void Game::debugFirstRow(int size, int &x){
    // Top of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "╔═════════";
        else if(i!= 0 && i != (size - 1))
            cout << "╦═════════";
        else
            cout << "╦═════════╗" << endl;
    }

    // Middle of square
    debugFirstRowMiddle(size, x);

    // Bottom of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "╠═══   ═══";
        else if(i!= 0 && i != (size - 1))
            cout << "╬═══   ═══";
        else
            cout << "╬═══   ═══╣" << endl;

    }
}


/*********************************************************************
** Function: debugMiddleRowsMiddle()
** Description: Prints the middle part of the middle rows of the debugged cave
** Parameters: size, x
** Pre-Conditions: Printed out the top and some of the middle of the middle rows.
** Post-Conditions: Printed out the middle of the middle rows of the debugged cave.
*********************************************************************/
void Game::debugMiddleRowsMiddle(int size, int &x){
    bool check = false;
    // Middle of square
    /* Add an if statement if there is cheat mode so the user can see what event is in that square */
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < size; j++){
            
            // If statement has an opening in the box to indicate the passage for the user
            if(i == 1){
                
                // if statement when there is an event in the room in question
                for(int z = 0; z < this->roomPtrs.size(); z++){
                    // If the player is in a room with an event
                    if((x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol()) && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
                        debugFirstRowMiddlePlayer(size, x, j, z, check);
                    }
                    // If there is an event in a room
                    else if((x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol())){
                        print_event_in_room(size, x, j, z, i, check);
                    }
                }

                // call a different function that will print different lines if the user happens to be in THAT room
                if(x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol()){
                    firstRowMiddlePlayer(size, x, j);
                }
                else{
                    extraPrint(size, j, check);
                }
            }
            else{
                cout << "║         ";
                if(j == size - 1)
                    cout << "║" << endl;
            }
        }
    }
}

/*********************************************************************
** Function: debugMiddleRows()
** Description: Prints out the middle rows of the debugged cave map.
** Parameters: size, x
** Pre-Conditions: Top of the cave has been printed, now we need to print the middle.
** Post-Conditions: Middle of the debugged cave map has been printed.
*********************************************************************/
void Game::debugMiddleRows(int size, int &x){
    // Top of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "║         ";
        else if(i!= 0 && (i != (size - 1)))
            cout << "║         ";
        else
            cout << "║         ║" << endl;
    }

    // Middle of Square
    debugMiddleRowsMiddle(size, x);

    // Bottom of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "╠═══   ═══";
        else if(i!= 0 && i != (size - 1))
            cout << "╬═══   ═══";
        else
            cout << "╬═══   ═══╣" << endl;

    }
}

/*********************************************************************
** Function: extraPrint()
** Description: Function that has some extra lines for printing the squares so as to not run over the 15 line function limit.
** Parameters: size, j, check
** Pre-Conditions: Part of the square/row has already been printed
** Post-Conditions: The rest of the square/row has finished being printed.
*********************************************************************/
void Game::extraPrint(int size, int &j, bool &check){
    if(j == 0){
        cout << "║         ";    
    }
    else if(j == (size - 1)){
        cout << "          ║" << endl; 
    }
    else{
        if(check == true){

        }
        else{
            cout << "          ";
        }
    }
}

/*********************************************************************
** Function: debugBottomRowMiddle()
** Description: The middle of the debugged bottom row is printed.
** Parameters: size, x
** Pre-Conditions: The top-half of the bottom rows have been printed.
** Post-Conditions: The middle of the debugged bottom row is printed.
*********************************************************************/
void Game::debugBottomRowMiddle(int size, int &x){
    bool check = false;
    // Middle of square
    /* Add an if statement if there is cheat mode so the user can see what event is in that square */
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < size; j++){

            // If statement has an opening in the box to indicate the passage for the user
            if(i == 1){
                // if statement when there is an event in the room in question
                for(int z = 0; z < this->roomPtrs.size(); z++){
                    // If the player is in a room with an event
                    if((x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol()) && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
                        debugFirstRowMiddlePlayer(size, x, j, z, check);
                    }
                    // If there is an event in a room
                    else if((x == this->roomPtrs[z]->getRow() && j == this->roomPtrs[z]->getCol())){
                        print_event_in_room(size, x, j, z, i, check);
                    }
                }

                // call a different function that will print different lines if the user happens to be in THAT room
                if(x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol()){
                    firstRowMiddlePlayer(size, x, j);
                }
                else{
                    extraPrint(size, j, check);
                }
            }
            else{
                cout << "║         ";
                if(j == size - 1)
                    cout << "║" << endl;
            }
        }
    }
}

/*********************************************************************
** Function: debugBottomRow()
** Description: Prints out the bottom row of the debugged cave map.
** Parameters: size, x
** Pre-Conditions: The top and middle rows of the debugged cave map are printed.
** Post-Conditions: Prints out the bottom row of the debugged cave map.
*********************************************************************/
void Game::debugBottomRow(int size, int &x){
    // Top of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "║         ";
        else if(i!= 0 && i != (size - 1))
            cout << "║         ";
        else
            cout << "║         ║" << endl;
    }

    // Middle of square
    debugBottomRowMiddle(size, x);

    // Bottom of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "╚═════════";
        else if(i!= 0 && i != (size - 1))
            cout << "╩═════════";
        else
            cout << "╩═════════╝" << endl;

    }
}

/*********************************************************************
** Function: firstRowMiddlePlayer()
** Description: The middle rows of the first row are printed, IF the player is in them.
** Parameters: size, x, j
** Pre-Conditions: The top part of the first row is printed.
** Post-Conditions: The middle portion of the top row is printed WITH the player in them.
*********************************************************************/
void Game::firstRowMiddlePlayer(int size, int &x, int &j){
    if((j != 0) && (j != (size - 1)) && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
        cout << "      *   ";
    }
    // conditional if player is in this part of the cave
    else if(j == 0 && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
        cout << "║     *   ";
    }
    // conditional if player is in this part of the cave
    else if(j == (size - 1) && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
        cout << "      *   ║" << endl;
    }
}

/*********************************************************************
** Function: firstRowMiddle()
** Description: The middle rows of the first row are printed.
** Parameters: size, x, 
** Pre-Conditions: The top part of the first row is printed.
** Post-Conditions: The middle portion of the top row is printed.
*********************************************************************/
void Game::firstRowMiddle(int size, int &x){
    // Middle of square
    /* Add an if statement if there is cheat mode so the user can see what event is in that square */
    bool check = false;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < size; j++){
            
            // If statement has an opening in the box to indicate the passage for the user
            if(i == 1){
                
                // call a different function that will print different lines if the user happens to be in THAT room
                if(x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol()){
                    firstRowMiddlePlayer(size, x, j);
                }
                else{
                    extraPrint(size, j, check);
                    
                }
            }
            else{
                cout << "║         ";
                if(j == size - 1)
                    cout << "║" << endl;
            }
        }
    }
}

/*********************************************************************
** Function: firstRow()
** Description: The first row of the cave map is printed.
** Parameters: size, x
** Pre-Conditions: The cave map needs to be printed, as requested by the displayInfo function
** Post-Conditions: The top/first row of the map is printed.
*********************************************************************/
void Game::firstRow(int size, int &x){
// Top of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "╔═════════";
        else if(i!= 0 && i != (size - 1))
            cout << "╦═════════";
        else
            cout << "╦═════════╗" << endl;
    }

    // Middle of square
    firstRowMiddle(size, x);

    // Bottom of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "╠═══   ═══";
        else if(i!= 0 && i != (size - 1))
            cout << "╬═══   ═══";
        else
            cout << "╬═══   ═══╣" << endl;

    }
}

/*********************************************************************
** Function: middleRowMiddle()
** Description: Prints out the middle of the middle rows of the cave map.
** Parameters: size, x
** Pre-Conditions: The first half of the middle rows have been printed.
** Post-Conditions: The middle of the middle row (THE OPENINGS) have been printed.
*********************************************************************/
void Game::middleRowMiddle(int size, int &x){
    // Middle of square
    /* Add an if statement if there is cheat mode so the user can see what event is in that square */
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < size; j++){
            
            // If statement has an opening in the box to indicate the passage for the user
            if(i == 1){
                
                // conditional for if the program is printing WHERE the user's position is, AND its not the starting box
                if((j != 0) && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
                    cout << "      *   ";
                }
                // conditional if player is in this part of the cave
                else if(j == 0 && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
                    cout << "║     *   ";
                }
                // conditional if player is in this part of the cave
                else if(j == (size - 1) && (x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol())){
                    cout << "      *   ║" << endl;
                }
                // player is not here
                else if(j == 0){
                    cout << "║         ";    
                }
                // player is not here
                else if(j == (size - 1)){
                    cout << "          ║" << endl; 
                }
                // player is not here
                else{
                    cout << "          ";
                }
            }
            else{
                cout << "║         ";
                if(j == size - 1)
                    cout << "║" << endl;
            }
        }
    }
}

/*********************************************************************
** Function: middleRows()
** Description: Prints out the middle rows of the non-debugged cave map.
** Parameters: size, x
** Pre-Conditions: The first row has been printed out.
** Post-Conditions: The middle rows of the map are printed out.
*********************************************************************/
void Game::middleRows(int size, int &x){
    // Top of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "║         ";
        else if(i!= 0 && (i != (size - 1)))
            cout << "║         ";
        else
            cout << "║         ║" << endl;
    }

    // Middle of Square
    middleRowMiddle(size, x);

    // Bottom of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "╠═══   ═══";
        else if(i!= 0 && i != (size - 1))
            cout << "╬═══   ═══";
        else
            cout << "╬═══   ═══╣" << endl;

    }
}

/*********************************************************************
** Function: bottomRowMiddle()
** Description: The middle of the bottom row is printed (WITH OPENINGS)
** Parameters: size, x
** Pre-Conditions: The first half of the bottom row has been printed.
** Post-Conditions: The middle of the bottom row is printed (WITH OPENINGS)
*********************************************************************/
void Game::bottomRowMiddle(int size, int &x){
    // Middle of square
    /* Add an if statement if there is cheat mode so the user can see what event is in that square */
    bool check = false;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < size; j++){
            
            // If statement has an opening in the box to indicate the passage for the user
            if(i == 1){
                // call a different function that will print different lines if the user happens to be in THAT room
                if(x == this->user.getCurrentRoom()->getRow() && j == this->user.getCurrentRoom()->getCol()){
                    firstRowMiddlePlayer(size, x, j);
                }
                else{
                    extraPrint(size, j, check);
                }
            }
            else{
                cout << "║         ";
                if(j == size - 1)
                    cout << "║" << endl;
            }
        }
    }
}

/*********************************************************************
** Function: bottomRow()
** Description: Prints out the bottom row of the cave map.
** Parameters: size, x
** Pre-Conditions: The first and middle rows have been printed out.
** Post-Conditions: The bottom row is printed out to the user.
*********************************************************************/
void Game::bottomRow(int size, int &x){
    // Top of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "║         ";
        else if(i!= 0 && i != (size - 1))
            cout << "║         ";
        else
            cout << "║         ║" << endl;
    }

    // Middle of square
    bottomRowMiddle(size, x);

    // Bottom of square
    for(int i = 0; i < size; i++){
        if(i == 0)
            cout << "╚═════════";
        else if(i!= 0 && i != (size - 1))
            cout << "╩═════════";
        else
            cout << "╩═════════╝" << endl;

    }
}

/*********************************************************************
** Function: print_cave()
** Description: The main function for printing out the cave (calls all of the other debug/non-debug print functions)
** Parameters: size
** Pre-Conditions: The displayInfo() function wants to print the cave out to the user
** Post-Conditions: The cave map is printed out.
*********************************************************************/
void Game::print_cave(int size){
    for(int x = 0; x < size; x++){
        // If debug mode is true
        if(this->debugMode == true){
            if(x == 0){
                debugFirstRow(size, x);
            }
            else if(x > 0 && x != size - 1){
                debugMiddleRows(size, x); // Note --> the user and events can only be in the middle 
            }
            else{
                debugBottomRow(size, x);
            }
        }
        else if(this->debugMode == false){
            if(x == 0){
                firstRow(size, x);
            }
            else if(x > 0 && x != size - 1){
                middleRows(size, x); // Note --> the user can only be in the middle 
            }
            else{
                bottomRow(size, x);
            }
        }
    }
}

/*********************************************************************
** Function: print_coordinates()
** Description: This function prints the coordinates of the unique events/other info happening in the cave.
**              Added as a safeguard in case the events are not properly printed within the cave map.
** Parameters: NONE
** Pre-Conditions: The cave map has been printed.
** Post-Conditions: Coordinate key is printed out after the map.
*********************************************************************/
void Game::print_coordinates(){
    if(this->debugMode == true){
        char eventChar;

        for(int i = 0; i < this->roomPtrs.size(); i++){
            eventChar = this->roomPtrs[i]->getEvent()->obtainEventChar();
            if(eventChar == 'G')
                cout << "Gold: " << "(" << this->roomPtrs[i]->getRow() << "," << this->roomPtrs[i]->getCol() << ")\t";
            else if(eventChar == 'W')
                cout << "Wumpus: " << "(" << this->roomPtrs[i]->getRow() << "," << this->roomPtrs[i]->getCol() << ")\t";
            else if(eventChar == 'B')
                cout << "Super-Bats: " << "(" << this->roomPtrs[i]->getRow() << "," << this->roomPtrs[i]->getCol() << ")\t";
            else if(eventChar == 'P')
                cout << "Bottomless Pit: " << "(" << this->roomPtrs[i]->getRow() << "," << this->roomPtrs[i]->getCol() << ")\t";
        }

        // Additionally, print out the escape room's coordinates
        cout << "Escape Room: " << "(" << this->escapeRoom->getRow() << "," << this->escapeRoom->getCol() << ")\t";
        cout << "Current Position: " << "(" << this->user.getCurrentRoom()->getRow() << "," << this->user.getCurrentRoom()->getCol() << ")\t";
        cout << endl;

    }
}

/*********************************************************************
** Function: printNearbyMessage()
** Description: This function prints a message if the user is near an event
** Parameters: NONE
** Pre-Conditions: User is next to a room with an event
** Post-Conditions: A message is printed out to the user indicating an event is nearby.
*********************************************************************/
void Game::printNearbyMessage(){
    int user_x = this->user.getCurrentRoom()->getRow();
    int user_y = this->user.getCurrentRoom()->getCol();
    // If there is an event ABOVE the player, so minus 1 row
    if(user_x - 1 >= 0){
        if(this->cave[user_x - 1][user_y].getHasEvent()){
            this->cave[user_x - 1][user_y].getEvent()->print_nearby_statement();
        }
    }
    
    // If there is an event BELOW the player, so add 1 row (cave size so it doesn't check out of bounds)
    if(user_x + 1 < this->caveSize){
        if(this->cave[user_x + 1][user_y].getHasEvent()){
            this->cave[user_x + 1][user_y].getEvent()->print_nearby_statement();
        }
    }

    // If there is an event to the LEFT of the player, so minus 1 col (0 so it doesnt check out of bounds)
    if(user_y - 1 >= 0){
        if(this->cave[user_x][user_y - 1].getHasEvent()){
            this->cave[user_x][user_y - 1].getEvent()->print_nearby_statement();
        }
    }

    // If there is an event to the RIGHT of the player, so add one col
    if(user_y + 1 < this->caveSize){
        if(this->cave[user_x][user_y + 1].getHasEvent()){
            this->cave[user_x][user_y + 1].getEvent()->print_nearby_statement();
        }
    }

    cout << endl;
}


/*********************************************************************
** Function: generateBatTeleportNums()
** Description: Function that specifically generates the numbers that the user will be teleported to
**              Similar to rand_index(), but this requires some error checking
** Parameters: randi, randj
** Pre-Conditions: The user is in the same room as the bats
** Post-Conditions: Random numbers are generated for the user's new position in the cave
*********************************************************************/
void Game::generateBatTeleportNums(int &randi, int &randj){
    // find an empty room --> NOTE THAT THE PLAYER IS NOT AN EVENT, so the player is in an "empty room". The wumpus will be allowed to enter their room.
    bool check = false;
    do{
        randi = rand_index();
        randj = rand_index();

        if(this->cave[randi][randj].getHasEvent() == true){
            if(this->cave[randi][randj].getEvent()->obtainEventChar() != 'B'){
                check = true;
            }
        }
        else{
            check = true;
        }
    }while (check == false);
}


/*********************************************************************
** Function: updateGameStates()
** Description: Updates certain game variables based on what room the user is in (they could be in a room with an event)
** Parameters: teleported
** Pre-Conditions: User moved to a new room.
** Post-Conditions: Game member vars are properly updated based on the event.
*********************************************************************/
void Game::updateGameStates(bool &teleported){    
    if(this->user.getCurrentRoom()->getHasEvent() == false){
    
    }
    // Wumpus
    else if(this->user.getCurrentRoom()->getEvent()->obtainEventChar() == 'W'){
        // If the wumpus is not killed, AND the player is in the SAME ROOM as it, the Wumpus will kill the player. Game is now over.
        // ! operator because if the user HASN'T killed the Wumpus, we want to end the game (eats the player)
        if(teleported == true && !(this->user.getKilledWumpus())){ // player was teleported INTO the Wumpus room
            this->user.getCurrentRoom()->getEvent()->print_interaction_statement();
            this->isGameOver = true;
        }
        else if(!(this->user.getKilledWumpus())){  // not teleported
            this->isGameOver = true;
        }
    }
    // Gold
    else if(this->user.getCurrentRoom()->getEvent()->obtainEventChar() == 'G'){
        // User is in the same room as the gold, so they pick it up
        this->user.setHasGold(true);
    }
    // Super-Bats
    else if(this->user.getCurrentRoom()->getEvent()->obtainEventChar() == 'B'){
        // cout << "USER IS IN THE ROOM WITH BATS" << endl;
        // Generate random indices
        // int rand_x = rand_index();
        // int rand_y = rand_index();
        int rand_x, rand_y;
        generateBatTeleportNums(rand_x, rand_y);

        Room* random = get_room(rand_x, rand_y); // obtain the room with those random indices

        this->user.setCurrentRoom(random); // MOVE the user to the new random room

        teleported = true;
        // cout << "USER POS: (" << this->user.getCurrentRoom()->getRow() << "," << this->user.getCurrentRoom()->getCol() << ")" << endl;
        updateGameStates(teleported); // now that the user is in a new room, we may need to update the game states again, so call the function again
    }
    // Bottomless Pit
    else if(this->user.getCurrentRoom()->getEvent()->obtainEventChar() == 'P'){
        if(teleported == true){
            this->user.getCurrentRoom()->getEvent()->print_interaction_statement();
        }
        this->isGameOver = true;  // player entered a room with a pit, they fall through and die
    }

}

/*********************************************************************
** Function: roomInteraction()
** Description: Main function that is called when the user is in a room. Adjacent room msgs are printed, as well as game variables being updated.
** Parameters: NONE
** Pre-Conditions: Cave map is printed out.
** Post-Conditions: Game vars are properly updated, and notifications are printed to the user.
*********************************************************************/
void Game::roomInteraction(){
    // Check if the user's room has an event in it
    if(this->user.getCurrentRoom()->getHasEvent()){
        // Wumpus
        if(this->user.getCurrentRoom()->getEvent()->obtainEventChar() == 'W'){
            if(this->user.getKilledWumpus() == true){
                cout << "\x1B[1;35mYou walk into the room with the dead Wumpus.\033[0m" << endl;
            }
            else{
                this->user.getCurrentRoom()->getEvent()->print_interaction_statement();
            }
        }
        // If the user is in a room with bats, gold, or pits
        else{
            if(this->user.getCurrentRoom()->getEvent()->obtainEventChar() == 'G' && this->user.getHasGold()){ // special case if the user goes into the gold room again after obtaining the gold
                cout << "\x1B[1;33mYou walk back into the empty Treasure room (the gold was already picked up).\033[0m\t\t" << endl;
            }
            else{
                this->user.getCurrentRoom()->getEvent()->print_interaction_statement();
            }
        }
        bool teleported = false;
        // Set game states -- wumpus dead, gameOver, has gold, etc.
        updateGameStates(teleported);
    }
    // If the user is in an empty room
    else if(this->user.getCurrentRoom()->getHasEvent() == false){

    }

}

/*********************************************************************
** Function: displayInformation()
** Description: Main function that displays ALL of the info for the game. Calls other functions.
** Parameters: NONE
** Pre-Conditions: The game is created and/or another loop of the playGame() func is running
** Post-Conditions: All of the information is properly displayed to the user.
*********************************************************************/
void Game::displayInformation(){
    int size = this->caveSize;

    Room* theCurrentRoom = this->user.getCurrentRoom();
    print_cave(size);
    print_coordinates();
    // cout << "You have " << this->user.getNumArrows() << " arrows left." << endl;
    cout << "\x1B[3;36mYou have \033[0m" << "\x1B[3;4;32m"<< this->user.getNumArrows() << "\033[0m" << "\x1B[3;36m arrows left.\033[0m" << endl;

    printNearbyMessage();
    
}

/*********************************************************************
** Function: fireNorth()
** Description: Fires the arrow North.
** Parameters: NONE
** Pre-Conditions: User indicated they want to fire an arrow to the North.
** Post-Conditions: Arrow misses, hits Wumpus, or wakes Wumpus.
*********************************************************************/
void Game::fireNorth(){
    // An arrow can only travel through up to 3 rooms
    for(int i = 1; i < 4; i++){
        // Make sure the room is in bounds so we don't get a seg fault
        if(this->user.getCurrentRoom()->getRow() - i >= 0){
            if(get_room(this->user.getCurrentRoom()->getRow() - i, this->user.getCurrentRoom()->getCol())->getHasEvent() == true){ // subtract i to the user's row, since they fire UPWARDS
                // there is an event in the room that the arrow is traveling in
            
                if((this->user.getKilledWumpus() != true) && get_room(this->user.getCurrentRoom()->getRow() - i, this->user.getCurrentRoom()->getCol())->getEvent()->obtainEventChar() == 'W'){ // check to see if there is a wumpus in this room
                    // there is a wumpus in the room
                    cout << "\x1B[3;36mYour arrow strikes the Wumpus and kills it.\033[0m\t\t" << endl;
                    this->user.setKilledWumpus(true); // arrow kills the wumpus

                    cout << "\x1B[32mTHE WUMPUS IS DEAD.\033[0m\t\t" << endl;
                }
            }            
        }
    }
}

/*********************************************************************
** Function: fireSouth()
** Description: Fires the arrow South.
** Parameters: NONE
** Pre-Conditions: User indicated they want to fire an arrow to the South.
** Post-Conditions: Arrow misses, hits Wumpus, or wakes Wumpus.
*********************************************************************/
void Game::fireSouth(){
    // An arrow can only travel through up to 3 rooms
    for(int i = 1; i < 4; i++){
        // Make sure the room is in bounds so we don't get a seg fault
        
        if(this->user.getCurrentRoom()->getRow() + i < this->caveSize){
            
            if(get_room(this->user.getCurrentRoom()->getRow() + i, this->user.getCurrentRoom()->getCol())->getHasEvent() == true){ // add i to the user's row, since they fire DOWNWARDS
                // there is an event in the room that the arrow is traveling in

                if((this->user.getKilledWumpus() != true) && get_room(this->user.getCurrentRoom()->getRow() + i, this->user.getCurrentRoom()->getCol())->getEvent()->obtainEventChar() == 'W'){ // check to see if there is a wumpus in this room
                    // there is a wumpus in the room
                    cout << "\x1B[3;36mYour arrow strikes the Wumpus and kills it.\033[0m\t\t" << endl;
                    this->user.setKilledWumpus(true); // arrow kills the wumpus

                    cout << "\x1B[32mTHE WUMPUS IS DEAD.\033[0m\t\t" << endl;

                }
            }
        }
    }
}

/*********************************************************************
** Function: fireWest()
** Description: Fires the arrow West.
** Parameters: NONE
** Pre-Conditions: User indicated they want to fire an arrow to the West.
** Post-Conditions: Arrow misses, hits Wumpus, or wakes Wumpus.
*********************************************************************/
void Game::fireWest(){
    // An arrow can only travel through up to 3 rooms
    for(int i = 1; i < 4; i++){
        // Make sure the room is in bounds so we don't get a seg fault
        // Make sure the room is in bounds so we don't get a seg fault
        if(this->user.getCurrentRoom()->getCol() - i >= 0){
        
            if(get_room(this->user.getCurrentRoom()->getRow(), this->user.getCurrentRoom()->getCol() - i)->getHasEvent() == true){  // subtract i to the user's col, since they fire LEFT
                // there is an event in the room that the arrow is traveling in
                
                if((this->user.getKilledWumpus() != true) && get_room(this->user.getCurrentRoom()->getRow(), this->user.getCurrentRoom()->getCol() - i)->getEvent()->obtainEventChar() == 'W'){ // check to see if there is a wumpus in this room
                    // there is a wumpus in the room
                    cout << "\x1B[3;36mYour arrow strikes the Wumpus and kills it.\033[0m\t\t" << endl;
                    this->user.setKilledWumpus(true); // arrow kills the wumpus

                    cout << "\x1B[32mTHE WUMPUS IS DEAD.\033[0m\t\t" << endl;

                }
            }
        }
    }
}

/*********************************************************************
** Function: fireEast()
** Description: Fires the arrow East.
** Parameters: NONE
** Pre-Conditions: User indicated they want to fire an arrow to the East.
** Post-Conditions: Arrow misses, hits Wumpus, or wakes Wumpus.
*********************************************************************/
void Game::fireEast(){
    // An arrow can only travel through up to 3 rooms
    for(int i = 1; i < 4; i++){
        // Make sure the room is in bounds so we don't get a seg fault
        // Make sure the room is in bounds so we don't get a seg fault
        if(this->user.getCurrentRoom()->getCol() + i < this->caveSize){
        
            if(get_room(this->user.getCurrentRoom()->getRow(), this->user.getCurrentRoom()->getCol() + i)->getHasEvent() == true){ // add i to the user's col, since they fire RIGHT
                // there is an event in the room that the arrow is traveling in
                
                if((this->user.getKilledWumpus() != true) && get_room(this->user.getCurrentRoom()->getRow(), this->user.getCurrentRoom()->getCol() + i)->getEvent()->obtainEventChar() == 'W'){ // check to see if there is a wumpus in this room
                    // there is a wumpus in the room
                    cout << "\x1B[3;36mYour arrow strikes the Wumpus and kills it.\033[0m\t\t" << endl;

                    this->user.setKilledWumpus(true); // arrow kills the wumpus

                    cout << "\x1B[32mTHE WUMPUS IS DEAD.\033[0m\t\t" << endl;

                }
            }
        }
    }
}

/*********************************************************************
** Function: genNewWumpusRoom()
** Description: Generates two random numbers within the scope of the cave's size. It is for the Wumpus when it moves rooms.
** Parameters: randi, randj
** Pre-Conditions: The Wumpus has woken up and needs to move.
** Post-Conditions: The two new random coordinate values have been set.
*********************************************************************/
void Game::genNewWumpusRoom(int &randi, int &randj){
    // find an empty room --> NOTE THAT THE PLAYER IS NOT AN EVENT, so the player is in an "empty room". The wumpus will be allowed to enter their room.
    bool check = false;
    do{
        randi = rand_index();
        randj = rand_index();

        if(this->cave[randi][randj].is_empty()){
            check = true;
        }
    }while (check == false);
    
}

/*********************************************************************
** Function: wumpusWakesUp()
** Description: Main function when the Wumpus wakes up from an arrow.
** Parameters: NONE
** Pre-Conditions: The user fired an arrow which missed.
** Post-Conditions: 75% chance of occurring -> the Wumpus moves rooms.
*********************************************************************/
void Game::wumpusWakesUp(){
    /* initalize random seed */
    srand(time(NULL));

    int randomNum = rand() % 4; // 0-3
    // 75% chance
    if(randomNum <= 2){
        cout << "\x1B[3;35mThe Wumpus woke up and moved to another room.\033[0m" << endl;

        int randi, randj;
        genNewWumpusRoom(randi, randj);

        Event* temp;  // temporary ptr to store the wumpus's OLD location
        // Find the location of the Wumpus
        for(int i = 0; i < this->caveSize; i++){  // Rows
            for(int j = 0; j < this->caveSize; j++){  // Cols
                
                if(this->cave[i][j].getHasEvent() == true){  // If event is in room (IF TRUE), then check if that event is a wumpus
                    
                    if(this->cave[i][j].getEvent()->obtainEventChar() == 'W'){
                        temp = this->cave[i][j].getEvent(); // save the wumpus to the temp variable

                        // Get rid of the old wumpus's location in the cave vector, so we don't have duplicates
                        this->cave[i][j].setEvent(NULL);
                        this->cave[i][j].setHasEvent(false);
                    }
                }
                
            }
        }
        // still inside of the 75% chance
        this->roomPtrs[1] = get_room(randi, randj);  // first update the vector that is printing out the assignments
        this->cave[randi][randj].setEvent(temp);
    }
    else{
        cout << "\x1B[3;35mThe Wumpus did not hear your arrow.\033[0m" << endl;
    } 
}

/*********************************************************************
** Function: extraArrowInstructions()
** Description: Extra arrow instructions so the function doesn't go over 15 lines.
** Parameters: once
** Pre-Conditions: Arrow has already been fired.
** Post-Conditions: Calls the Wumpus Wake up function if the arrow missed.
*********************************************************************/
void Game::extraArrowInstructions(bool &once){
    if(this->user.getKilledWumpus() == true && once == false){
        // cout << "\x1B[3;36mYour arrow strikes the Wumpus and kills it.\033[0m\t\t" << endl;
        // cout << "\x1B[32mTHE WUMPUS IS DEAD.\033[0m\t\t" << endl;
        once = true;

    }
    else{  // WILL NOT RUN WHEN THE WUMPUS IS DEAD
        cout << "\x1B[3;36mYour arrow missed.\033[0m" << endl;
        
        wumpusWakesUp(); // your arrow missed.. the wumpus now has a 75% chance to move
    }

    
}

/*********************************************************************
** Function: fireArrowInDirection()
** Description: Fires the arrow in a user-specified direction. Calls other functions to accomplish this.
** Parameters: c
** Pre-Conditions: User inputted a direction in which to fire the arrow.
** Post-Conditions: Arrow is fired and game is properly updated.
*********************************************************************/
void Game::fireArrowInDirection(char &c){
    // Fire arrow UP
    if(c == 'W' || c == 'w'){
        cout << "\x1B[3;36mYour arrow travels North...\033[0m\t\t" << endl;
        fireNorth();
    }
    // Fire arrow DOWN
    else if(c == 'S' || c == 's'){
        cout << "\x1B[3;36mYour arrow travels South...\033[0m\t\t" << endl;
        fireSouth();
    }
    // Fire arrow LEFT
    else if(c == 'A' || c == 'a'){
        cout << "\x1B[3;36mYour arrow travels West...\033[0m\t\t" << endl;
        fireWest();
    }
    // Fire arrow RIGHT
    else if(c == 'D' || c == 'd'){
        cout << "\x1B[3;36mYour arrow travels East...\033[0m\t\t" << endl;
        fireEast();
    }

    // Last statement is to subtract the number of arrows from the user's quiver by 1; it happens for all cases
    this->user.setNumArrows(this->user.getNumArrows() - 1);
    bool once = false;
    extraArrowInstructions(once);
}

/*********************************************************************
** Function: doFireArrows()
** Description: Obtain the direction for which the user wants to fire the arrow into.
** Parameters: choice
** Pre-Conditions: The user specified they want to fire arrows.
** Post-Conditions: Arrow is fired in specified direction. Game is updated.
*********************************************************************/
void Game::doFireArrows(char &choice){
    if(this->user.getNumArrows() > 0){
        char c = ' ';
        cout << "Enter the direction for which to fire an arrow (WASD): ";
        cin >> c;

        if(c == 'W' || c == 'w' || c == 'A' || c == 'a' || c == 'S' || c == 's' || c == 'D' || c == 'd'){
            fireArrowInDirection(c);
        }
        else{
            while((c != 'W') || (c != 'A') || (c != 'S') || (c != 'D')){
                cout << "Error: enter a valid choice: ";
                cin >> c;
                
                if(c == 'W' || c == 'w' || c == 'A' || c == 'a' || c == 'S' || c == 's' || c == 'D' || c == 'd'){
                    fireArrowInDirection(c);
                    break;
                }
            }
        }
    }
    // User has no arrows left
    else{
        cout << "\x1B[3;36mERROR: You have no more arrows left.\033[0m\t\t" << endl;
    }
    
    
}

/*********************************************************************
** Function: doAvailableOptions()
** Description: Performs the options that were available to the user (movement options occur here)
** Parameters: choice
** Pre-Conditions: User inputted a variable which specifies what they want to do.
** Post-Conditions: User moves, fires an arrow, etc.
*********************************************************************/
void Game::doAvailableOptions(char &choice){
    // User wants to move UP a room
    if(choice == 'W' || choice == 'w'){
        // If the user is in bounds
        if(this->user.getCurrentRoom()->getRow() - 1 >= 0){
            this->user.setCurrentRoom(get_room(this->user.getCurrentRoom()->getRow() - 1, this->user.getCurrentRoom()->getCol()));
        }
        // Out of bounds
        else{
            cout << "\x1B[31mERROR: Out of bounds.\033[0m\t\t" << endl;
        }
    }

    // User wants to move DOWN a room
    else if(choice == 'S' || choice == 's'){
        // If the user is in bounds
        if(this->user.getCurrentRoom()->getRow() + 1 < this->caveSize){
            this->user.setCurrentRoom(get_room(this->user.getCurrentRoom()->getRow() + 1, this->user.getCurrentRoom()->getCol()));
        }
        // Out of bounds
        else{
            cout << "\x1B[31mERROR: Out of bounds.\033[0m\t\t" << endl;
        }
    }

    // User wants to move LEFT a room
    else if(choice == 'A' || choice == 'a'){
        // If the user is in bounds
        if(this->user.getCurrentRoom()->getCol() - 1 >= 0){
            this->user.setCurrentRoom(get_room(this->user.getCurrentRoom()->getRow(), this->user.getCurrentRoom()->getCol() - 1));
        }
        // Out of bounds
        else{
            cout << "\x1B[31mERROR: Out of bounds.\033[0m\t\t" << endl;
        }
    }

    // User wants to move RIGHT a room
    else if(choice == 'D' || choice == 'd'){
        // If the user is in bounds
        if(this->user.getCurrentRoom()->getCol() + 1 < this->caveSize){
            this->user.setCurrentRoom(get_room(this->user.getCurrentRoom()->getRow(), this->user.getCurrentRoom()->getCol() + 1));
        }
        // Out of bounds
        else{
            cout << "\x1B[31mERROR: Out of bounds.\033[0m\t\t" << endl;
        }
    }

    else if(choice == 'F' || choice == 'f'){
        doFireArrows(choice);
    }
}

/*********************************************************************
** Function: userInputsChoice()
** Description: User inputs a certain choice based on movement or firing an arrow
** Parameters: choice
** Pre-Conditions: Map is printed out to the user. They need to do something now to progress the game.
** Post-Conditions: A choice is inputted, and the game is updated.
*********************************************************************/
// Function where the user inputs a char to tell the program that they either want to MOVE, or to FIRE an arrow
void Game::userInputsChoice(char &choice){
    choice = ' ';
    cout << "Enter W, A, S, D to move, or F to fire an arrow." << endl;
    cin >> choice;
    
    if(choice == 'W' || choice == 'w' || choice == 'A' || choice == 'a' || choice == 'S' || choice == 's' || choice == 'D' || choice == 'd' || choice == 'F' || choice == 'f'){
        doAvailableOptions(choice);
    }
    else{
        while((choice != 'W') || (choice != 'A') || (choice != 'S') || (choice != 'D') || (choice != 'F')){
            cout << "Error: enter a valid choice: ";
            cin >> choice;
            
            if(choice == 'W' || choice == 'w' || choice == 'A' || choice == 'a' || choice == 'S' || choice == 's' || choice == 'D' || choice == 'd'|| choice == 'F' || choice == 'f'){
                doAvailableOptions(choice);
                break;
            }
        }
    }
}


/*********************************************************************
** Function: checkIfWon()
** Description: To win, the user has to have obtained the gold, killed the Wumpus, AND be in the escape room
** Parameters: NONE
** Pre-Conditions: Game has ended, the do-while loop was exited.
** Post-Conditions: Program determines if the user won or lost.
*********************************************************************/
bool Game::checkIfWon(){
    if(this->user.getHasGold() && this->user.getKilledWumpus() && (this->user.getCurrentRoom() == this->escapeRoom)){
        cout << "\x1B[32mYou killed the Wumpus, and escaped with the gold!\033[0m" << endl;
        this->isGameOver = true;
        return true;
    }
    return false;
}


/*********************************************************************
** Function: deleteEventPtrs()
** Description: Resets the game data to their default values so the user can play the game again
** Parameters: NONE
** Pre-Conditions: EventPtrs has not been deleted yet.
** Post-Conditions: EventPtrs has been properly freed of memory to prevent mem leaks.
*********************************************************************/
void Game::deleteEventPtrs(){
    /* NEED THIS FOR CLEARING THE EVENT POINTERS SO NO MEMORY LEAKS OCCUR */

    for(int i = 0; i < this->eventPtrs.size(); i++){
        delete this->eventPtrs[i];
    }
    this->eventPtrs.clear();
}


/*********************************************************************
** Function: resetUserData()
** Description: Function resets the user's data to its default preset numbers; # arrows, hasGold, killedWumpus, currentRoom.
** Parameters: NONE
** Pre-Conditions: The previous game has ended and the user wants to play again.
** Post-Conditions: The user data is set back to its original preset numbers.
*********************************************************************/ 
void Game::resetUserData(){
    this->user.setNumArrows(3);
    this->user.setHasGold(false);
    this->user.setKilledWumpus(false);

    this->user.setCurrentRoom(this->escapeRoom);
}


/*********************************************************************
** Function: pushBackNewEvents()
** Description: This function is equivalent to createEventPtrs, but with some minor additions
**              the additions include updating the roomPtrs vector
** Parameters: NONE
** Pre-Conditions: In the process of restarting the game
** Post-Conditions: The event ptrs have been added.
*********************************************************************/ 
void Game::pushBackNewEvents(){
    // 2 pits
    this->eventPtrs.push_back(new Pit());
    

    this->eventPtrs.push_back(new Pit());
    
    // 2 bats
    this->eventPtrs.push_back(new Bats());
    this->eventPtrs.push_back(new Bats());
    
    // 1 wumpus
    this->eventPtrs.push_back(new Wumpus());
    this->roomPtrs[1]->setEvent(this->eventPtrs[4]);
    
    // 1 gold
    this->eventPtrs.push_back(new Gold());
}


/*********************************************************************
** Function: restartGame()
** Description: Function that restarts the game
** Parameters: NONE
** Pre-Conditions: User wants to restart the game (play again)
** Post-Conditions: Memory is freed, the user data is ret, and the game is no longer over.
*********************************************************************/ 
void Game::restartGame(){
    deleteEventPtrs(); // clear the event ptrs
    
    resetUserData(); // reset the adventurer's data
    this->isGameOver = false;
    
    // pushBackNewEvents(); // add new event pointers to the eventPtr vector

}

/*********************************************************************
** Function: playWithNewSettings()
** Description: If the user wants to play again but with NEW settings. Redeclare vectors and other member vars
** Parameters: NONE
** Pre-Conditions: User indicated they want to play with new settings.
** Post-Conditions: New settings are set up by emulating a constructor in this function.
*********************************************************************/ 
void Game::playWithNewSettings(){
    deleteEventPtrs();
    // deleteRoomPtrs();
    resetUserData();

    this->cave.clear();
    this->eventPtrs.clear();
    this->roomPtrs.clear();
    this->trackedOriginalRoomPtrs.clear();

    // Repeat the instructions that exist in the default constructor for the Game class
    this->isGameOver = false;
    this->debugMode = debugModeAsk();
    this->caveSize = caveSizeAsk();
    initializeCave();

    int spawn_x, spawn_y;
    // Now, populate the cave
    populateCave(spawn_x, spawn_y);

    this->user.setCurrentRoom(get_room(spawn_x, spawn_y)); // sets the adventurer's current room (their starting room)
    this->escapeRoom = this->user.getCurrentRoom(); // sets the escapeRoom for this specific game
}


/*********************************************************************
** Function: askSameSettings()
** Description: Function that asks the user if they want to play the game again with the same settings (second prompt)
** Parameters: NONE
** Pre-Conditions: User indicated they want to play again.
** Post-Conditions: User either wants to play with or without the same settings.
*********************************************************************/ 
void Game::askSameSettings(){
    int choice;
    cout << "Do you want to replay with the same settings? (1) Yes, (2) No: ";
    cin >> choice;

    if(choice == 1){
        cout << "Same settings..." << endl;
        restartGame();
        
        playGame(); // once that is all said and done, call the playGame() function so the game can get started again
    }
    else{
        cout << "New settings!" << endl;
        playWithNewSettings();
        playGame();
    }
    
    
}


/*********************************************************************
** Function: askReplay()
** Description: Ask the user if they would like to replay the game (first prompt)
** Parameters: NONE
** Pre-Conditions: Game has ended.
** Post-Conditions: User either wants to replay or does not want to replay.
**                  If replay, then playGame() is restarted. If not, program is exited.
*********************************************************************/
void Game::askReplay(){
    int choice;
    cout << "Would you like to replay Hunt The Wumpus? (1) Yes, (2) No: ";
    cin >> choice;

    // User wants to replay the game
    if(choice == 1){
        askSameSettings();
    }
    // User does NOT want to play again
    else{
        cout << "Exiting the game..." << endl;
    }


}

/*********************************************************************
** Function: playGame()
** Description: The main function for playing the game. All main function calls are here.
** Parameters: NONE
** Pre-Conditions: Game object has been declared, and now the program needs to start the game.
** Post-Conditions: Game session has run at least once, and either loops back to the start if the user wanted to play again, or exits the program.
*********************************************************************/
void Game::playGame(){
    gameStart();

    // Loop runs while a player has not won just yet 
    while(!(this->isGameOver)){        
        displayInformation();  // includes cave map, adjoining room messages, 

        char userChoice;
        userInputsChoice(userChoice);  // move or fire --> function contains the DOING of those tasks
        roomInteraction();  // update the vars of the game, or print messages  

        // displayInformation();  // includes cave map, adjoining room messages, 


        // checkIfGameOver();  

        // Adventurer Victory
        if(checkIfWon()){
            cout << "Victory!" << endl;
        }
        // player loses
        // this->isGameOver = true; 
    }

    cout << "GAME OVER!" << endl;
    askReplay();

    
}