#include "main.h"

void four_reset() {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_reset");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}

void four_boardGet(char* charOut) {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_boardGet");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}

void four_boardSet(char* charIn) {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_boardSet");

			cJSON_AddStringToObject(objOut, "strIn", charIn);
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}

char four_winner() {
	char charReturn = '?';
	
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_winner");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			charReturn = cJSON_GetObjectItem(objIn, "strReturn")->valuestring[0];
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
	
	return charReturn;
}

bool four_isValid(int intX, int intY) {
	bool boolReturn = false;
	
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_isValid");
			
			cJSON_AddNumberToObject(objOut, "intX", intX);

			cJSON_AddNumberToObject(objOut, "intY", intY);
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(objIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
	
	return boolReturn;
}

bool four_isEnemy(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_isEnemy");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(objOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(objIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
	
	return boolReturn;
}

bool four_isOwn(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_isOwn");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(objOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(objIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
	
	return boolReturn;
}

bool four_isNothing(char charPiece) {
	bool boolReturn = false;
	
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_isNothing");
			
			char charPieceWrapped[16] = { };
			
			charPieceWrapped[0] = charPiece;
			charPieceWrapped[1] = '\0';
			
			cJSON_AddStringToObject(objOut, "strPiece", charPieceWrapped);
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			boolReturn = cJSON_GetObjectItem(objIn, "boolReturn")->valueint;
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
	
	return boolReturn;
}

int four_eval() {
	int intReturn = 0;
	
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_eval");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(objIn, "intReturn")->valueint;
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
	
	return intReturn;
}

int four_moves(char* charOut) {
	int intReturn = 0;

	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_moves");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(objIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(objIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}

	return intReturn;
}

int four_movesShuffled(char* charOut) {
	int intReturn = 0;

	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_movesShuffled");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(objIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(objIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}

	return intReturn;
}

int four_movesEvaluated(char* charOut) {
	int intReturn = 0;

	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_movesEvaluated");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			intReturn = cJSON_GetObjectItem(objIn, "intOut")->valueint;
			
			strcpy(charOut, cJSON_GetObjectItem(objIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}

	return intReturn;
}

void four_move(char* charIn) {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_move");

			cJSON_AddStringToObject(objOut, "strIn", charIn);
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}

void four_moveRandom(char* charOut) {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_moveRandom");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}

void four_moveGreedy(char* charOut) {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_moveGreedy");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}

void four_moveNegamax(char* charOut, int intMaxdepth, int intDuration) {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_moveNegamax");
			
			cJSON_AddNumberToObject(objOut, "intMaxdepth", intMaxdepth);

			cJSON_AddNumberToObject(objOut, "intDuration", intDuration);
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}

void four_moveAlphabeta(char* charOut, int intMaxdepth, int intDuration) {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_moveAlphabeta");
			
			cJSON_AddNumberToObject(objOut, "intMaxdepth", intMaxdepth);

			cJSON_AddNumberToObject(objOut, "intDuration", intDuration);
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		{
			strcpy(charOut, cJSON_GetObjectItem(objIn, "strOut")->valuestring);
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}

void four_undo() {
	{
		cJSON* objOut = cJSON_CreateObject();
		cJSON* objIn = NULL;
		
		{
			cJSON_AddStringToObject(objOut, "strFunction", "four_undo");
		}
		
		{
			zeromq_send(objOut);
			
			objIn = zeromq_recv();
		}
		
		cJSON_Delete(objOut);
		cJSON_Delete(objIn);
	}
}
