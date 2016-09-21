#include "main.h"

void four_reset() {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_reset");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}

void four_boardGet(char* charOut) {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_boardGet");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objectIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}

void four_boardSet(char* charIn) {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_boardSet");

			cJSON_AddStringToObject(objectOut, "strIn", charIn);
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}

char four_winner() {
	char charReturn = '?';
	
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_winner");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			charReturn = cJSON_GetObjectItem(objectIn, "strReturn")->valuestring[0];
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
	
	return charReturn;
}

bool four_isValid(int intX, int intY) {
	bool boolReturn = false;
	
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_isValid");
			
			cJSON_AddNumberToObject(objectOut, "intX", intX);

			cJSON_AddNumberToObject(objectOut, "intY", intY);
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(objectIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
	
	return boolReturn;
}

bool four_isEnemy(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_isEnemy");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(objectOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(objectIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
	
	return boolReturn;
}

bool four_isOwn(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_isOwn");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(objectOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(objectIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
	
	return boolReturn;
}

bool four_isNothing(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_isNothing");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(objectOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(objectIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
	
	return boolReturn;
}

int four_eval() {
	int intReturn = 0;
	
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_eval");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(objectIn, "intReturn")->valueint;
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
	
	return intReturn;
}

int four_moves(char* charOut) {
	int intReturn = 0;

	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_moves");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(objectIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(objectIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}

	return intReturn;
}

int four_movesShuffled(char* charOut) {
	int intReturn = 0;

	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_movesShuffled");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(objectIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(objectIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}

	return intReturn;
}

int four_movesEvaluated(char* charOut) {
	int intReturn = 0;

	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_movesEvaluated");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(objectIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(objectIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}

	return intReturn;
}

void four_move(char* charIn) {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_move");

			cJSON_AddStringToObject(objectOut, "strIn", charIn);
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}

void four_moveRandom(char* charOut) {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_moveRandom");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objectIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}

void four_moveGreedy(char* charOut) {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_moveGreedy");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objectIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}

void four_moveNegamax(char* charOut, int intDepth, int intDuration) {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_moveNegamax");
			
			cJSON_AddNumberToObject(objectOut, "intDepth", intDepth);

			cJSON_AddNumberToObject(objectOut, "intDuration", intDuration);
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objectIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}

void four_moveAlphabeta(char* charOut, int intDepth, int intDuration) {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_moveAlphabeta");
			
			cJSON_AddNumberToObject(objectOut, "intDepth", intDepth);

			cJSON_AddNumberToObject(objectOut, "intDuration", intDuration);
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objectIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}

void four_undo() {
	{
		cJSON* objectOut = cJSON_CreateObject();
		cJSON* objectIn = NULL;
		
		{
			cJSON_AddStringToObject(objectOut, "strFunction", "four_undo");
		}
		
		{
			zeromq_send(objectOut);
			
			objectIn = zeromq_recv();
		}
		
		cJSON_Delete(objectOut);
		cJSON_Delete(objectIn);
	}
}
