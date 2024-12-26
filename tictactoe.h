#define X 'X'
#define O 'O'
#define EMPTY ' '
#define NOWINNER '\0'
#include <iostream>

/**
 * ASSUMPTIONS MADE FOR THIS IMPLEMENTATION:
 *  according to the document, this should not have a UI and should be written so that any tictactoe interface can use it
 *  So from my understanding, this class is a backend class that will be used by a theorectical tictactoe front end to play the game.
 * - This class will not implement a game loop as that will be left up to the interface that uses this.
 * - The front end interface will adheare to the rules laid out in the method comments.
 * - the tictactoe interface will always be a 3x3 grid, if it is not then some small scale refactoring will need to be done.
 * - This class will not handle I/O, the front end will deal with that and pass it to us.
 * So this class will simply have logic to do the following:
 * - record a move on the board
 * - check if a player has won (3 in a row -- vert horiz or diag)
 * - check if the game is a tie (all spaces are filled)
 * - check if a move is valid (space is empty)
 * - reset the board
 * - some getters/setters for various fields.
 */
class TicTacToe{
    private:
        char board[3][3]; // the board itself
        bool isXTurn=true; //true if it is X's turn, false if it is O's turn
        bool isGameOver = false; // flag for front end to use
        char winner = NOWINNER; 
    public:
        //this constructor will simply call the reset function as both initalize the board to new game state.
        TicTacToe(){
            reset();
        }
        void reset(){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    board[i][j]==EMPTY;
                }
            }
            isXTurn = true;
            isGameOver=false;
            winner = NOWINNER;
        }
        /*todo list
        makemove(r,c)
        isvalid()
        isWinner()
        isTie()
        */
};