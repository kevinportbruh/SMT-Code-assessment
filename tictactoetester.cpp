#include <iostream>
#include <cassert>
#include "Tictactoe.h"
/**
 * This file uses the basic cassert to unit test the tictactoe class I wrote that could be used to track a game played by two people.
 * This class will test the functionality of the various methods of the class I wrote along with a couple of edge cases
 * the magic is below 🧙
 */


/**
 * I added this print board method as I wanted to see the board state when debugging
 * !!!!!!IT IS NOT APART OF THE TICTACTOE CLASS!!!!!!
 * I just wanted to see the board state
 * this helper method is in some of the tests but will only be used if debug mode is on
 */
void printboard(bool debugMode, const char (&board)[3][3]){
    if(debugMode){
        cout << "HELPER UNIT TEST ONLY PRINT METHOD CALLED" << endl;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
}
/**
 * This test will test the swap player function along with the getter for the player turn
 */
void testSwapPlayer(){
    TicTacToe game;
    assert(game.getPlayerTurn() == X);  // X goes first
    game.swapPlayer();
    assert(game.getPlayerTurn() == O);  // O goes second
    game.swapPlayer();
    assert(game.getPlayerTurn() == X);  // X goes third
    game.swapPlayer();
    assert(game.getPlayerTurn() == O);  // O goes fourth
}
/**
 * This test will reset the game and check if the board is empty
 * it also checks if the getboard and checkisgameover functions work
 */
void testReset(bool debugMode){
    if(debugMode){
        cout << "Testing reset with debug enabled" << endl;
    }
    
    TicTacToe game;
    game.setDebugMode(debugMode);
    game.makeMove(0, 0);  // X
    game.swapPlayer();
    game.makeMove(1, 1);  // O
    assert(game.getBoard()[0][0] == X);  // Check if the move was recorded
    assert(game.getBoard()[1][1] == O);  // Check if the move was recorded

    printboard(game.getDebugMode(), game.getBoard());
    
    assert(game.checkIsGameOver() == false);  // Game should not be over yet
    game.reset();  // Reset the game
    if(debugMode){
        cout << "Game state reset" << endl;
    }
    game.setDebugMode(debugMode);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            assert(game.getBoard()[i][j] == EMPTY);  // Check if the board is empty
        }
    }
    assert(game.checkIsGameOver() == false);  // Game should not be over after reset
    printboard(game.getDebugMode(), game.getBoard());
}
/**
 * This tests valid and invalid moves
 */
void testValidity(bool debugMode){
    if(debugMode){
        cout << "Testing validity with debug enabled" << endl;
    }
    TicTacToe game;
    game.setDebugMode(debugMode);
    // Test valid moves
    assert(game.isValid(0, 0) == true); // Spot is empty
    game.makeMove(0, 0);                // X
    game.swapPlayer();// Os turn
    assert(game.isValid(0, 0) == false); // Spot is now taken

    // Test out-of-bounds moves
    assert(game.isValid(-1, 0) == false);
    assert(game.isValid(3, 3) == false);

}
/**
 * This tests all win conditions
 */
void testWinner(bool debugMode){
     if(debugMode){
        cout << "Testing winner with debug enabled" << endl;
    }
    
    TicTacToe game;
    game.setDebugMode(debugMode);

    // Test winning move horizontally (bottom row x wins)
    game.makeMove(2, 0);  // X
    game.swapPlayer();
    game.makeMove(1, 0);  // O
    game.swapPlayer();
    game.makeMove(2, 1);  // X
    game.swapPlayer();
    game.makeMove(1, 1);  // O
    game.swapPlayer();
    game.makeMove(2, 2);  // X wins
    assert(game.getPlayerTurn()==X);// X should be the winnner
    assert(game.isWinner(game.getPlayerTurn())==true);//did they win?

    printboard(game.getDebugMode(), game.getBoard());//helper method 
    //does the game call a tie after a valid win?
    assert(game.isTie()==false);// no tie

    // Test winning move vertically (middle col o wins)
    //o wins
    game.reset();
    game.setDebugMode(debugMode);
    game.makeMove(0, 0);  // X
    game.swapPlayer();
    game.makeMove(0, 1);  // O
    game.swapPlayer();
    game.makeMove(1, 0);  // X
    game.swapPlayer();
    game.makeMove(1, 1);  // O
    game.swapPlayer();
    game.makeMove(0, 2); //x
    game.swapPlayer();
    game.makeMove(2,1);//O 
    assert(game.getPlayerTurn()==O);// O should be the winnner
    assert(game.isWinner(game.getPlayerTurn())==true);//did they win?
    printboard(game.getDebugMode(), game.getBoard());//helper method 

    // Test diagonal win (Left to right x wins)
    game.reset();
    game.setDebugMode(debugMode);
    game.makeMove(0, 0);  // X
    game.swapPlayer();
    game.makeMove(1, 0);  // O
    game.swapPlayer();
    game.makeMove(1, 1);  // X
    game.swapPlayer();
    game.makeMove(2, 0);  // O
    game.swapPlayer();
    game.makeMove(2, 2);  // X wins diagonally
    assert(game.getPlayerTurn()==X);// X should be the winnner
    assert(game.isWinner(game.getPlayerTurn())==true);//did they win?
    printboard(game.getDebugMode(), game.getBoard());//helper method 
    //other diagonal (right to left)
    game.reset();
    game.setDebugMode(debugMode);
    game.makeMove(0, 2);  // X
    game.swapPlayer();
    game.makeMove(1, 0);  // O
    game.swapPlayer();
    game.makeMove(1, 1);  // X
    game.swapPlayer();
    game.makeMove(2, 1);  // O
    game.swapPlayer();
    game.makeMove(2, 0);  // X wins diagonally
    assert(game.getPlayerTurn()==X);// X should be the winnner
    assert(game.isWinner(game.getPlayerTurn())==true);//did they win?
    printboard(game.getDebugMode(), game.getBoard());//helper method 

}




/**
 * this test will run a simple game
 * This method mainly tests the make move function testing valid and invalid moves
 * but also tests
 * This will also test ties, and win conditions
 * This also tests various getters and setters 
 */
void testBasicGame(bool debugMode){
    if(debugMode){
        cout << "Testing basic game with debug enabled" << endl;
    }
    TicTacToe game;
    game.setDebugMode(debugMode);
    
    assert(game.makeMove(0, 0) == true);  // Valid move -x
    game.swapPlayer(); 
    assert(game.getPlayerTurn()== O);//test the swap player
    assert(game.makeMove(0, 0) == false); // Invalid, spot already taken -o

    // Test out-of-bounds moves- should still be Os turn
    assert(game.makeMove(-1, 0) == false); // Invalid
    assert(game.makeMove(0, 3) == false);  // Invalid
    assert(game.makeMove(3, 3) == false);  // Invalid
    assert(game.makeMove(0,1) == true); // valid -o

    // Test valid second move
    game.swapPlayer();// x's turn now
    game.makeMove(1, 0); //valid -x move
    game.swapPlayer();
    assert(game.makeMove(0, 2) == true);  // Valid move-o

    assert(game.isWinner(game.getPlayerTurn())==false); //check for a win condition - o's turn, no winners
    assert(game.getWinner()==NOWINNER); // no winner yet
    assert(game.isTie()==false);// no tie yet
    game.swapPlayer();
    game.makeMove(2, 0); // X wins
    //lets make sure its
    assert(game.isTie()==false);//no tie
    assert(game.isWinner(game.getPlayerTurn())==true); //check for a win condition
    //check for a tie again as the game loop would
    assert(game.isTie()==false);// still no tie X won so flags should be set.
    assert(game.getWinner()==X);
    assert(game.checkIsGameOver()==true);
    
    assert(game.makeMove(2, 2) == false); // Game is over, move invalid
    printboard(game.getDebugMode(), game.getBoard());//helper method 

}
/**
 * This test will test a tie condition
 * 
 */
void testTie(bool debugMode){
    if(debugMode){
        cout << "Testing tie with debug enabled" << endl;
    }
    TicTacToe game;
    game.setDebugMode(debugMode);
    // Test tie
    game.makeMove(0, 0);  // X
    game.swapPlayer();
    game.makeMove(0, 1);  // O
    game.swapPlayer();
    game.makeMove(0, 2);  // X
    game.swapPlayer();
    game.makeMove(1, 0);  // O
    game.swapPlayer();
    game.makeMove(1, 1);  // X
    game.swapPlayer();
    game.makeMove(2, 0);  // O
    game.swapPlayer();
    game.makeMove(1, 2);  // X
    game.swapPlayer();
    game.makeMove(2, 2);  // O
    game.swapPlayer();
    game.makeMove(2, 1);  // X
    assert(game.isWinner(game.getPlayerTurn())==false);//x didnt win
    assert(game.isTie()==true);//tie
    assert(game.checkIsGameOver()==true);
    assert(game.getWinner()==NOWINNER); // no winner
    assert(game.getPlayerTurn()==X);
    assert(game.isWinner(game.getPlayerTurn())==false);//x didnt win
    assert(game.isWinner(O)==false); //o didnt win
    printboard(game.getDebugMode(), game.getBoard());//helper method
}

void testDebugMode(){
    TicTacToe game;
    game.setDebugMode(true);
    assert(game.getDebugMode()==true);
    game.setDebugMode(false); //mainly testing the print statements
    assert(game.getDebugMode()==false);
}


int main(){
    /**
     * functions with bool parameteers are there because they have various turning on debug mode and resetting the game
     * so to quickly test them I added a bool parameter to the function 
     */
    cout<< "Running tests"<<endl;
    testSwapPlayer();//tests swap player
    testValidity(false);//tests validity
    testReset(false);//tests reset
    testBasicGame(false);//an example of a simple game. tests make move and is valid (since makeMove() calls isValid())
    testWinner(false);//tests win conditions
    testTie(false);//tests tie conditions
    testDebugMode();//tests debug mode -- will always print statements
    cout<<"Tests passed"<<endl;
    return 0;
}