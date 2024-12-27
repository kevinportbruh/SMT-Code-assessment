#ifndef TICTACTOE_H
#define TICTACTOE_H

#define X 'X'
#define O 'O'
#define EMPTY ' '
#define NOWINNER '\0'
#include <iostream>
using namespace std;

/**
 * @Author: Kevin Portillo Self-Proclaimed Coding Wizard 🧙
 * 
 * ASSUMPTIONS MADE FOR THIS IMPLEMENTATION:
 *  according to the document, this should not have a UI and should be written so that any tictactoe interface can use it
 *  So from my understanding, this class is a backend class that will be used by a theorectical tictactoe front end to play the game.
 * - This class will NOT implement a game loop as that will be left up to the interface that uses this.
 * - The front end interface will adheare to the rules laid out in the method comments.
 * - the tictactoe interface will always be a 3x3 grid, if it is not then some small scale refactoring will need to be done.
 *      - the refactoring would be adding a field to hold the size of the board, replace any hard coded 3 to that boardSize and any hard coded 2 to boardSize-1 along with a few other changes.
 * - This class will NOT handle I/O, the front end will deal with that and pass it to us.
 * 
 * So this class will simply have logic to do the following:
 * - record a move on the board
 * - check if a player has won (3 in a row -- vert horiz or diag)
 * - check if the game is a tie (all spaces are filled)
 * - check if a move is valid (space is empty)
 * - reset the board
 * - some getters/setters for various fields.
 * 
 */


/**
 * IF THIS CLASS WERE TO BE USED IN A FRONT END AND THEY WERE TO HANDLE THE GAMELOOP THIS IS HOW I ENVISION IT
 * int main(){
 * TicTacToe game;
 * while(!game.IsGameOver()){
 *      printboard() // this is implement however they want to they can use get board method to get teh board state and format it however
 *      char currentP = game.getPlayerTurn();
 *      int row, col;
 *      //get the input
 *      if(game.makemove(r,c)){
 *          //check if this move won the game or resulted in a tie
*             if(game.isWinner(currentP))// do something
*             if(game.isTie())// do something     
*             swapPlayer()// swap the player AFTER checking for a winner
 *         }else{
 *             //the move was not valid so have tehm try again         
 *          }
 *      }
 * //end of while loop if here we broke or the game is over
 * //do something like reset or close.
 * } 
 */



class TicTacToe{
    private:
        char board[3][3]; // the board itself
        bool isXTurn=true; //true if it is X's turn, false if it is O's turn
        bool isGameOver = false; // flag for front end to use in a game loop
        char winner = NOWINNER; 
        bool debugMode = false;
        
    public:
        TicTacToe(); // Constructor to initialize the board
        void reset(); // Resets the board to the initial state
        bool makeMove(int row, int col); // Makes a move on the board
        void swapPlayer(); // Swaps the turn between players
        bool isValid(int row, int col); // Checks if a move is valid
        bool isWinner(char currentPlayer); // Checks if the current player has won
        bool isTie(); // Checks if the game is a tie
        char getWinner(); // Returns the winner character
        bool checkIsGameOver(); // Checks if the game is over
        void setIsGameOver(bool b); // Sets the game over flag
        char getPlayerTurn(); // Returns the current player's turn
        void setDebugMode(bool b); // Enables or disables debug mode
        bool getDebugMode(); // Returns whether debug mode is enabled
        const char (&getBoard() const)[3][3]; // Returns the current board state
};

#endif // TICTACTOE_H