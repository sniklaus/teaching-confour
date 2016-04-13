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
	
	for (int intFor1 = 0; intFor1 < intMoves; intFor1 += 1) {
		intA[intFor1] = (charA[(intFor1 * 6) + 0] * 1) + (charA[(intFor1 * 6) + 1] * 100) + (charA[(intFor1 * 6) + 3] * 10000) + (charA[(intFor1 * 6) + 4] * 1000000);
		intB[intFor1] = (charB[(intFor1 * 6) + 0] * 1) + (charB[(intFor1 * 6) + 1] * 100) + (charB[(intFor1 * 6) + 3] * 10000) + (charB[(intFor1 * 6) + 4] * 1000000);
	}
	
	for (int intFor1 = 0; intFor1 < intMoves - 1; intFor1 += 1) {
		int intMin = intFor1;
		
		for (int intFor2 = intFor1 + 1; intFor2 < intMoves; intFor2 += 1) {
			if (intA[intFor2] < intA[intMin]) {
				intMin = intFor2;
			}
		}
		
		if (intFor1 == intMin) {
			continue;
		}
		
		int intSwap = intA[intFor1];
		intA[intFor1] = intA[intMin];
		intA[intMin] = intSwap;
	}
	
	for (int intFor1 = 0; intFor1 < intMoves - 1; intFor1 += 1) {
		int intMin = intFor1;
		
		for (int intFor2 = intFor1 + 1; intFor2 < intMoves; intFor2 += 1) {
			if (intB[intFor2] < intB[intMin]) {
				intMin = intFor2;
			}
		}
		
		if (intFor1 == intMin) {
			continue;
		}
		
		int intSwap = intB[intFor1];
		intB[intFor1] = intB[intMin];
		intB[intMin] = intSwap;
	}
	
	for (int intFor1 = 0; intFor1 < intMoves; intFor1 += 1) {
		if (intA[intFor1] != intB[intFor1]) {
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

int test_movesCount(int* intBuffer, char* charBuffer, int intCount) {
	int intEqual = 0;
	
	for (int intFor1 = 0; intFor1 < intCount; intFor1 += 1) {
		for (int intFor2 = intFor1 + 1; intFor2 < intCount; intFor2 += 1) {
			if (intBuffer[intFor1] != intBuffer[intFor2]) {
				intEqual = intCount;
			}
		}
	}
	
	for (int intFor1 = 0; intFor1 < intCount; intFor1 += 1) {
		for (int intFor2 = intFor1 + 1; intFor2 < intCount; intFor2 += 1) {
			if (strcmp(&charBuffer[intFor1 * 1024], &charBuffer[intFor2 * 1024]) == 0) {
				intEqual += 1;
			}
		}
	}
	
	return intEqual;
}

bool test_movesShuffled() {
	return false;
}

bool test_movesOrder(int intMoves, char* charMoves) {
	int intEval[128] = { };
	
	for (int intFor1 = 0; intFor1 < intMoves; intFor1 += 1) {
		four_move(&charMoves[intFor1 * 6]);
		intEval[intFor1] = four_eval();
		four_undo();
	}
	
	for (int intFor1 = 0; intFor1 < intMoves - 1; intFor1 += 1) {
		if (intEval[intFor1] > intEval[intFor1 + 1]) {
			return false;
		}
	}
	
	return true;
}

bool test_movesEvaluated() {
	return false;
}

int test_moveCount(char* charBuffer, int intCount) {
	int intEqual = 0;
	char charEqual[100 * 1024] = { };
	
	intEqual = 0;
	charEqual[0] = '\0';
	
	for (int intFor1 = 0; intFor1 < intCount; intFor1 += 1) {
		if (strstr(charEqual, &charBuffer[intFor1 * 1024]) == NULL) {
			intEqual += 1;
			strcat(charEqual, &charBuffer[intFor1 * 1024]);
		}
	}
	
	return intEqual;
}

bool test_moveRandom() {
	return false;
}

bool test_moveGreedy() {
	char charBuffer[1024] = { };
	
	int intWon = 0;
	int intLost = 0;
	
	for (int intFor1 = 0; intFor1 < 50; intFor1 += 1) {
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
		
		if (four_winner() == 'W') {
			intWon += 1;
			
		} else if (four_winner() == 'B') {
			intLost += 1;
			
		}
	}
	
	for (int intFor1 = 0; intFor1 < 50; intFor1 += 1) {
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
		
		if (four_winner() == 'B') {
			intWon += 1;
			
		} else if (four_winner() == 'W') {
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
	
	for (int intFor1 = 0; intFor1 < 50; intFor1 += 1) {
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
		
		if (four_winner() == 'W') {
			intWon += 1;
			
		} else if (four_winner() == 'B') {
			intLost += 1;
			
		}
	}
	
	for (int intFor1 = 0; intFor1 < 50; intFor1 += 1) {
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
		
		if (four_winner() == 'B') {
			intWon += 1;
			
		} else if (four_winner() == 'W') {
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
