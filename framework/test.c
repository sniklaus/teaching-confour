#include "main.h"

bool test_board() {
	return false;
}

bool test_winner() {
	return false;
}

bool test_isValid() {
	return false;
}

bool test_isEnemy() {
	return false;
}

bool test_isOwn() {
	return false;
}

bool test_isNothing() {
	return false;
}

bool test_eval() {
	return false;
}

bool test_movesCompare(int intMoves, char* charA, char* charB) {
	if (strlen(charA) != intMoves * 6) {
		return false;
		
	} else if (strlen(charB) != intMoves * 6) {
		return false;
		
	}
	
	int intA[128] = { };
	int intB[128] = { };
	
	for (int intMove = 0; intMove < intMoves; intMove += 1) {
		intA[intMove] = (charA[(intMove * 6) + 0] * 1) + (charA[(intMove * 6) + 1] * 100) + (charA[(intMove * 6) + 3] * 10000) + (charA[(intMove * 6) + 4] * 1000000);
		intB[intMove] = (charB[(intMove * 6) + 0] * 1) + (charB[(intMove * 6) + 1] * 100) + (charB[(intMove * 6) + 3] * 10000) + (charB[(intMove * 6) + 4] * 1000000);
	}
	
	for (int intMove = 0; intMove < intMoves - 1; intMove += 1) {
		int intMin = intMove;
		
		for (int intIndex = intMove + 1; intIndex < intMoves; intIndex += 1) {
			if (intA[intIndex] < intA[intMin]) {
				intMin = intIndex;
			}
		}
		
		if (intMove == intMin) {
			continue;
		}
		
		int intSwap = intA[intMove];
		intA[intMove] = intA[intMin];
		intA[intMin] = intSwap;
	}
	
	for (int intMove = 0; intMove < intMoves - 1; intMove += 1) {
		int intMin = intMove;
		
		for (int intIndex = intMove + 1; intIndex < intMoves; intIndex += 1) {
			if (intB[intIndex] < intB[intMin]) {
				intMin = intIndex;
			}
		}
		
		if (intMove == intMin) {
			continue;
		}
		
		int intSwap = intB[intMove];
		intB[intMove] = intB[intMin];
		intB[intMin] = intSwap;
	}
	
	for (int intMove = 0; intMove < intMoves; intMove += 1) {
		if (intA[intMove] != intB[intMove]) {
			return false;
		}
	}
	
	return true;
}

bool test_moves() {
	return false;
}

bool test_move() {
	return false;
}

bool test_undo() {
	return false;
}

int test_movesSame(int* intBuffer, char* charBuffer, int intCount) {
	int intSame = 0;
	
	for (int intTrial = 0; intTrial < intCount; intTrial += 1) {
		for (int intSubsequent = intTrial + 1; intSubsequent < intCount; intSubsequent += 1) {
			if (intBuffer[intTrial] != intBuffer[intSubsequent]) {
				intSame = intCount;
			}
		}
	}
	
	for (int intTrial = 0; intTrial < intCount; intTrial += 1) {
		for (int intSubsequent = intTrial + 1; intSubsequent < intCount; intSubsequent += 1) {
			if (strcmp(&charBuffer[intTrial * 1024], &charBuffer[intSubsequent * 1024]) == 0) {
				intSame += 1;
			}
		}
	}
	
	return intSame;
}

bool test_movesShuffled() {
	return false;
}

bool test_movesOrder(int intMoves, char* charMoves) {
	int intEval[128] = { };
	
	for (int intMove = 0; intMove < intMoves; intMove += 1) {
		four_move(&charMoves[intMove * 6]);
		intEval[intMove] = four_eval();
		four_undo();
	}
	
	for (int intMove = 0; intMove < intMoves - 1; intMove += 1) {
		if (intEval[intMove] > intEval[intMove + 1]) {
			return false;
		}
	}
	
	return true;
}

bool test_movesEvaluated() {
	return false;
}

int test_moveSame(char* charBuffer, int intCount) {
	int intSame = 0;
	char charEqual[100 * 1024] = { };
	
	intSame = 0;
	charEqual[0] = '\0';
	
	for (int intTrial = 0; intTrial < intCount; intTrial += 1) {
		if (strstr(charEqual, &charBuffer[intTrial * 1024]) == NULL) {
			intSame += 1;
			strcat(charEqual, &charBuffer[intTrial * 1024]);
		}
	}
	
	return intSame;
}

bool test_moveRandom() {
	return false;
}

bool test_moveGreedy() {
	char charBuffer[1024] = { };
	
	int intWon = 0;
	int intLost = 0;
	
	for (int intGame = 0; intGame < 50; intGame += 1) {
		four_reset();
		
		do {
			four_moveGreedy(charBuffer);
			
			if (four_winner() != '?') {
				break;
			}
			
			four_moveRandom(charBuffer);
			
			if (four_winner() != '?') {
				break;
			}
		} while (true);
		
		if (four_winner() == 'X') {
			intWon += 1;
			
		} else if (four_winner() == 'O') {
			intLost += 1;
			
		}
	}
	
	for (int intGame = 0; intGame < 50; intGame += 1) {
		four_reset();
		
		do {
			four_moveRandom(charBuffer);
			
			if (four_winner() != '?') {
				break;
			}
			
			four_moveGreedy(charBuffer);
			
			if (four_winner() != '?') {
				break;
			}
		} while (true);
		
		if (four_winner() == 'O') {
			intWon += 1;
			
		} else if (four_winner() == 'X') {
			intLost += 1;
			
		}
	}
	
	if (intWon < 90) {
		return false;
		
	} else if (intLost > 10) {
		return false;
		
	}
	
	return true;
}

bool test_moveNegamax() {
	char charBuffer[1024] = { };
	
	int intWon = 0;
	int intLost = 0;
	
	for (int intGame = 0; intGame < 50; intGame += 1) {
		four_reset();
		
		do {
			four_moveNegamax(charBuffer, 2, INT_MAX);
			
			if (four_winner() != '?') {
				break;
			}
			
			four_moveGreedy(charBuffer);
			
			if (four_winner() != '?') {
				break;
			}
		} while (true);
		
		if (four_winner() == 'X') {
			intWon += 1;
			
		} else if (four_winner() == 'O') {
			intLost += 1;
			
		}
	}
	
	for (int intGame = 0; intGame < 50; intGame += 1) {
		four_reset();
		
		do {
			four_moveGreedy(charBuffer);
			
			if (four_winner() != '?') {
				break;
			}
			
			four_moveNegamax(charBuffer, 2, INT_MAX);
			
			if (four_winner() != '?') {
				break;
			}
		} while (true);
		
		if (four_winner() == 'O') {
			intWon += 1;
			
		} else if (four_winner() == 'X') {
			intLost += 1;
			
		}
	}
	
	if (intWon < 90) {
		return false;
		
	} else if (intLost > 10) {
		return false;
		
	}
	
	return true;
}

int test_moveCarbide(char* charLeft, char* charRight, int intNumber) {
	return 0;
}

int test_moveMercury(int intDepth) {
	return 0;
}

bool test_moveTungsten(int intDepth) {
	return false;
}

bool test_moveAlphabeta() {
	return false;
}
