#define X 'X'
#define O 'O'
#define EMPTY ' '
#define NOWINNER '\0'
#include <iostream>
using namespace std;
/**
 * ASSUMPTIONS MADE FOR THIS IMPLEMENTATION:
 *  according to the document, this should not have a UI and should be written so that any tictactoe interface can use it
 *  So from my understanding, this class is a backend class that will be used by a theorectical tictactoe front end to play the game.
 * - This class will NOT implement a game loop as that will be left up to the interface that uses this.
 * - The front end interface will adheare to the rules laid out in the method comments.
 * - the tictactoe interface will always be a 3x3 grid, if it is not then some small scale refactoring will need to be done.
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
        TicTacToe(){
            //initialize the board to empty
            //call the reset function to save on code duplication
            reset();
        }
        void reset(){
            //clear board
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    board[i][j] = EMPTY;
                }
            }
            //x always goes first
            isXTurn = true;
            isGameOver=false;
            winner = NOWINNER;
            debugMode = false;
        }
         /**
         *  Rows and Cols are 0 based
         *  the interface that uses this must make sure they pass this correctly
         *  Returns true if we were able to record the move
         *  Returns false if we were unable to (not valid move)
         * 
         * THIS USED TO SWAP THE PLAYER TURN AUTOMATICALLY HOWEVER ISSUES MAY ARRISE FROM THE isWinner() 
         * SO WE MOVED IT TO A METHOD
         */
        bool makeMove(int row, int col){
            //first check that the move is valid
            if(!isValid(row,col)){
                return false;
            }
            //if it is valid then record the move and change player turn
            board[row][col]= (isXTurn? X:O);//ternary op!
            if(debugMode){ // added print statements
                cout << "player " << getPlayerTurn() << "made a move at R " << row << " C "<< col << endl;
            }
            //MOVED TO ITS OWN METHOD isXTurn = !isXTurn;//flip turn bool
            return true; //move was valid
        }
        //swaps the current players turn
        void swapPlayer(){
            isXTurn = !isXTurn;//flip turn bool
        }
        /**
         * Validation checker
         * mainly check if row and col are not out of bounds or if the spot we are trying to place is not taken
         * Return true if valid false if not.
         */
        bool isValid(int row, int col){
            //First check if the row and col are between [0-2] else its out of range
            if((row<0||row>2) ||(col<0||col>2)){
                if(debugMode){
                    cout<< "row or col was not between 0-2. Row : "<< row << " Col: " << col << endl;
                }
                return false;
            }else if (board[row][col]!=EMPTY){  //then check if board[row][col] == empty space
                if(debugMode){
                    printf("The spot %d %d is already taken\n", row, col);// wanted to use string formatting instead of cout
                }
                return false;
            }
            //the above could be consolidated into one line but i like the readablity
            //checks passed return true
            return true;
        }
        /**
         * is winner, return true if the current player just won the game else return false
         */
        bool isWinner(char currentPlayer){
            //this loop checks the horizontals and vertical win conditions
            for(int i=0;i<3;i++){
                if((board[i][0]==currentPlayer && board[i][1]==currentPlayer && board[i][2]==currentPlayer)
                || (board[0][i]==currentPlayer &&board[1][i]==currentPlayer &&board[2][i]==currentPlayer)){
                    
                    winner = currentPlayer; //winner found set the winner field.
                    isGameOver = true;
                    if(debugMode){
                        printf("The player %c has won the game!\n", winner);
                    }
                    return true;
                }
            }
            //this if statment checks the diagonals
            if((board[0][0]==currentPlayer && board[1][1]==currentPlayer && board[2][2]==currentPlayer)
            || (board[0][2]==currentPlayer &&board[1][1]==currentPlayer &&board[2][0]==currentPlayer)){
                winner = currentPlayer; //winner found set the winner field.
                isGameOver = true;
                if(debugMode){
                        printf("The player %c has won the game!\n", winner);
                    }
                return true;
            }
            //if here no winner
            return false;

        }
        /**
         * isTie - returns true if there is a tie if not return false
         * a tie would be if there are no empty spaces on the board and there is not a winner.
         */
        bool isTie(){
            //loop thru board
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    //if we found an empty spot and there is not a winner
                    if(board[i][j] == EMPTY && winner == NOWINNER){
                        if(debugMode){
                            cout<< "no tie"<< endl;
                        }
                        return false;
                    }
                }
            }
            //the board is full and there was not a winner 
            isGameOver = true;//game is over
            if(debugMode){
                cout<< "The game is a draw!"<< endl;
            }
            return true;
        }

        //getters and setters for the fields
        char getWinner(){
            return winner;
        }
        //is the game over?
        bool isGameOver(){
            return isGameOver;
        }
        void setIsGameOver(bool b){
            isGameOver =b;
        }
        //get whoevers players turn it is.
        char getPlayerTurn(){
            return isXTurn ? X : O;
        }
        void setDebugMode(bool b){
            debugMode = b;
        }

        //no setter for player turn as to prevent misue (setting it to another char), use the swapTurn() method instead
        //getter for the board state
        //had to look up how to return a 2d array as a reference this is what I found.
        const char (&getBoard() const)[3][3] {
            return board;
        }
};