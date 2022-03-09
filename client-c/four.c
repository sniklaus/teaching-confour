#include "main.h"

void four_reset() {
    // reset the state of the game / your internal variables - note that this function is highly dependent on your implementation
}

void four_boardGet(char* charOut) {
    // write the state of the game into the provided argument - one example is given below - note that the state has exactly 52 or 53 characters
    
    charOut += sprintf(charOut, "1 X\n");
    charOut += sprintf(charOut, "       \n");
    charOut += sprintf(charOut, "       \n");
    charOut += sprintf(charOut, "       \n");
    charOut += sprintf(charOut, "       \n");
    charOut += sprintf(charOut, "       \n");
    charOut += sprintf(charOut, "       \n");
}

void four_boardSet(char* charIn) {
    // read the state of the game from the provided argument and set your internal variables accordingly - note that the state has exactly 40 or 41 characters
}

char four_winner() {
    // determine the winner of the current state of the game and return '?' or '=' or 'X' or 'O' - note that we are returning a character and not a string
    
    return '?';
}

bool four_isValid(int intX, int intY) {
    if (intX < 0) {
        return false;
        
    } else if (intX > 6) {
        return false;
        
    }
    
    if (intY < 0) {
        return false;
        
    } else if (intY > 5) {
        return false;
        
    }
    
    return true;
}

bool four_isEnemy(char charPiece) {
    // with reference to the state of the game, return whether the provided argument is a piece from the side not on move - note that we could but should not use the other is() functions in here but probably
    
    return false;
}

bool four_isOwn(char charPiece) {
    // with reference to the state of the game, return whether the provided argument is a piece from the side on move - note that we could but should not use the other is() functions in here but probably
    
    return false;
}

bool four_isNothing(char charPiece) {
    // return whether the provided argument is not a piece / is an empty field - note that we could but should not use the other is() functions in here but probably
    
    return false;
}

int four_eval() {
    // with reference to the state of the game, return the the evaluation score of the side on move - note that positive means an advantage while negative means a disadvantage
    
    return 0;
}

int four_moves(char* charOut) {
    // with reference to the state of the game, write the possible moves into the provided argument and return the number of moves - one example is given below - note that a move has exactly 3 characters
    
    int intReturn = 0;
    
    intReturn += 1;
    charOut += sprintf(charOut, "a1\n");
    
    intReturn += 1;
    charOut += sprintf(charOut, "b1\n");
    
    intReturn += 1;
    charOut += sprintf(charOut, "c1\n");
    
    intReturn += 1;
    charOut += sprintf(charOut, "d1\n");
    
    intReturn += 1;
    charOut += sprintf(charOut, "e1\n");
    
    intReturn += 1;
    charOut += sprintf(charOut, "f1\n");
    
    intReturn += 1;
    charOut += sprintf(charOut, "g1\n");

    return intReturn;
}

int four_movesShuffled(char* charOut) {
    // with reference to the state of the game, determine the possible moves and shuffle them before writing the output into the provided argument and returning the number of moves- note that you can call the four_moves() function in here

    return 0;
}

int four_movesEvaluated(char* charOut) {
    // with reference to the state of the game, determine the possible moves and sort them in order of an increasing evaluation score before writing the output into the provided argument and returning the number of moves - note that you can call the four_movesEvaluated() function in here

    return 0;
}

void four_move(char* charIn) {
    // perform the supplied move (for example "a5-a4\n") and update the state of the game / your internal variables accordingly - note that it advised to do a sanity check of the supplied move
}

void four_moveRandom(char* charOut) {
    // perform a random move and write the chosen move into the provided argument - one example output is given below - note that you can call the four_movesShuffled() function as well as the four_move() function in here
    
    charOut[0] = 'd';
    charOut[1] = '1';
    charOut[2] = '\n';
    charOut[3] = '\0';
}

void four_moveGreedy(char* charOut) {
    // perform a greedy move and write the chosen move into the provided argument - one example output is given below - note that you can call the four_movesEvaluated() function as well as the four_move() function in here
    
    charOut[0] = 'd';
    charOut[1] = '1';
    charOut[2] = '\n';
    charOut[3] = '\0';
}

void four_moveNegamax(char* charOut, int intMaxdepth, int intDuration) {
    // perform a negamax move and write the chosen move into the provided argument - one example output is given below - note that you can call the the other functions in here
    
    charOut[0] = 'd';
    charOut[1] = '1';
    charOut[2] = '\n';
    charOut[3] = '\0';
}

void four_moveAlphabeta(char* charOut, int intMaxdepth, int intDuration) {
    // perform a alphabeta move and write the chosen move into the provided argument - one example output is given below - note that you can call the the other functions in here
    
    charOut[0] = 'd';
    charOut[1] = '1';
    charOut[2] = '\n';
    charOut[3] = '\0';
}

void four_undo() {
    // undo the last move and update the state of the game / your internal variables accordingly - note that you need to maintain an internal variable that keeps track of the previous history for this
}
