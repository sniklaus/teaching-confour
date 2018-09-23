#ifndef FOUR_H_LOCK
#define FOUR_H_LOCK

void four_reset();
void four_boardGet(char* charOut);
void four_boardSet(char* charIn);
char four_winner();
bool four_isValid(int intX, int intY);
bool four_isEnemy(char charPiece);
bool four_isOwn(char charPiece);
bool four_isNothing(char charPiece);
int four_eval();
int four_moves(char* charOut);
int four_movesShuffled(char* charOut);
int four_movesEvaluated(char* charOut);
void four_move(char* charIn);
void four_moveRandom(char* charOut);
void four_moveGreedy(char* charOut);
void four_moveNegamax(char* charOut, int intMaxdepth, int intDuration);
void four_moveAlphabeta(char* charOut, int intMaxdepth, int intDuration);
void four_undo();

#endif
