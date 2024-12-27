#include "tictactoe.h"
//moved from the .h file to its own file to follow good practice
TicTacToe::TicTacToe(){
    //initialize the board to empty
    //call the reset function to save on code duplication
    reset();
}
void TicTacToe::reset(){
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
bool TicTacToe::makeMove(int row, int col){
    //first check that the move is valid
    if(!isValid(row,col) || isGameOver){
        return false;
    }
    //if it is valid then record the move and change player turn
    board[row][col]= (isXTurn? X:O);//ternary op!
    if(debugMode){ // added print statements
        cout << "player " << getPlayerTurn() << " made a move at R " << row << " C "<< col << endl;
    }
    //MOVED TO ITS OWN METHOD isXTurn = !isXTurn;//flip turn bool
    return true; //move was valid
}
//swaps the current players turn
void TicTacToe::swapPlayer(){
    isXTurn = !isXTurn;//flip turn bool
}
/**
 * Validation checker
 * mainly check if row and col are not out of bounds or if the spot we are trying to place is not taken
 * Return true if valid false if not.
 */
bool TicTacToe::isValid(int row, int col){
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
bool TicTacToe::isWinner(char currentPlayer){
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
bool TicTacToe::isTie(){
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
    //if the game is already over and a tie is checked then return false.
    if(isGameOver){
        return winner == NOWINNER;
    } 

    //if here then there is a winner and the game is over
    //the board is full and there was not a winner 
    isGameOver = true;//game is over
    if(debugMode){
        cout<< "The game is a draw!"<< endl;
    }
    return true;
}

//getters and setters for the fields
char TicTacToe::getWinner(){
    return winner;
}
//is the game over?
bool TicTacToe::checkIsGameOver(){
    return isGameOver;
}
void TicTacToe::setIsGameOver(bool b){
    isGameOver =b;
}
//get whoevers players turn it is.
char TicTacToe::getPlayerTurn(){
    return isXTurn ? X : O;
}

void TicTacToe::setDebugMode(bool b){
    if(b){
        cout << "Debug mode is on" << endl;
    }else if (debugMode){
        //if it was on then tell them its off
        cout << "Debug mode is now off" << endl;
    }
    debugMode = b;
}
bool TicTacToe::getDebugMode(){
    return debugMode;
}

//no setter for player turn as to prevent misue (setting it to another char), use the swapTurn() method instead
//getter for the board state
//had to look up how to return a 2d array as a reference this is what I found.
const char (&TicTacToe::getBoard() const)[3][3] {
    return board;
}