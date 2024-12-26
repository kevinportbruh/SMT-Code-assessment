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
        TicTacToe(){
            //initialize the board to empty
            //call the reset function to save on code duplication
            reset();
        }
        void reset(){
            //clear board
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    board[i][j]==EMPTY;
                }
            }
            //x always goes first
            isXTurn = true;
            isGameOver=false;
            winner = NOWINNER;
        }
         /**
         *  Rows and Cols are 0 based
         *  the interface that uses this must make sure they pass this correctly
         *  Returns true if we were able to record the move
         *  Returns false if we were unable to (not valid move)
         */
        bool makeMove(int row, int col){
            //first check that the move is valid
            if(!isValid(row,col)){
                return false;
            }
            //if it is valid then record the move and change player turn
            board[row][col]= (isXTurn? X:O);//ternary op!
            isXTurn = !isXTurn;//flip turn bool
            return true; //move was valid
        }
        /**
         * Validation checker
         * mainly check if row and col are not out of bounds or if the spot we are trying to place is not taken
         * Return true if valid false if not.
         */
        bool isValid(int row, int col){
            //First check if the row and col are between [0-2] else its out of range
            if((row<0||row>2) ||(col<0||col>2)){
                return false;
            }else if (board[row][col]!=EMPTY){  //then check if board[row][col] == empty space
                return false;
            }
            //the above could be consolidated into one line but i like the readablity
            //checks passed return true
            return true;
        }

        /*todo list
        isWinner()
        isTie()
        */
};