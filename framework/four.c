#include "main.h"

void four_reset() {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_reset");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}

void four_boardGet(char* charOut) {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_boardGet");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(cjsonIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}

void four_boardSet(char* charIn) {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_boardSet");

			cJSON_AddStringToObject(cjsonOut, "strIn", charIn);
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}

char four_winner() {
	char charReturn = '?';
	
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_winner");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			charReturn = cJSON_GetObjectItem(cjsonIn, "strReturn")->valuestring[0];
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
	
	return charReturn;
}

bool four_isValid(int intX, int intY) {
	bool boolReturn = false;
	
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_isValid");
			
			cJSON_AddNumberToObject(cjsonOut, "intX", intX);

			cJSON_AddNumberToObject(cjsonOut, "intY", intY);
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(cjsonIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
	
	return boolReturn;
}

bool four_isEnemy(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_isEnemy");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(cjsonOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(cjsonIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
	
	return boolReturn;
}

bool four_isOwn(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_isOwn");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(cjsonOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(cjsonIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
	
	return boolReturn;
}

bool four_isNothing(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_isNothing");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(cjsonOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(cjsonIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
	
	return boolReturn;
}

int four_eval() {
	int intReturn = 0;
	
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_eval");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(cjsonIn, "intReturn")->valueint;
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
	
	return intReturn;
}

int four_moves(char* charOut) {
	int intReturn = 0;

	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_moves");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(cjsonIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(cjsonIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}

	return intReturn;
}

int four_movesShuffled(char* charOut) {
	int intReturn = 0;

	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_movesShuffled");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(cjsonIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(cjsonIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}

	return intReturn;
}

int four_movesEvaluated(char* charOut) {
	int intReturn = 0;

	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_movesEvaluated");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(cjsonIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(cjsonIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}

	return intReturn;
}

void four_move(char* charIn) {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_move");

			cJSON_AddStringToObject(cjsonOut, "strIn", charIn);
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}

void four_moveRandom(char* charOut) {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_moveRandom");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(cjsonIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}

void four_moveGreedy(char* charOut) {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_moveGreedy");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(cjsonIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}

void four_moveNegamax(char* charOut, int intDepth, int intDuration) {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_moveNegamax");
			
			cJSON_AddNumberToObject(cjsonOut, "intDepth", intDepth);

			cJSON_AddNumberToObject(cjsonOut, "intDuration", intDuration);
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(cjsonIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}

void four_moveAlphabeta(char* charOut, int intDepth, int intDuration) {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_moveAlphabeta");
			
			cJSON_AddNumberToObject(cjsonOut, "intDepth", intDepth);

			cJSON_AddNumberToObject(cjsonOut, "intDuration", intDuration);
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(cjsonIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}

void four_undo() {
	{
		cJSON* cjsonOut = cJSON_CreateObject();
		cJSON* cjsonIn = NULL;
		
		{
			cJSON_AddStringToObject(cjsonOut, "strFunction", "four_undo");
		}
		
		{
			zeromq_send(cjsonOut);
			
			cjsonIn = zeromq_recv();
		}
		
		cJSON_Delete(cjsonOut);
		cJSON_Delete(cjsonIn);
	}
}
