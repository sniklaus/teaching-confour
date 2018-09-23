#include "main.h"

bool zeromq_boolRunning = false;

void zeromq_start() {
	zeromq_boolRunning = true;

	void* objectContext = zmq_ctx_new();
	void* objectSocket = zmq_socket(objectContext, ZMQ_PAIR);
	
	{
		char charZeromq[1024] = { };
		
		sprintf(charZeromq, "tcp://*:%d", main_intZeromq);
		
		if (zmq_bind(objectSocket, charZeromq) == -1) {
			printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
		}
	}

	do {
		cJSON* objectIn = NULL;
		cJSON* objectOut = cJSON_CreateObject();
		
		{
			char charJson[1024] = { };
			
			if (zmq_recv(objectSocket, charJson, sizeof(charJson), 0) == -1) {
				printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
			}
			
			objectIn = cJSON_Parse(charJson);
		}
	
		if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "ping") == 0) {
			cJSON_AddStringToObject(objectOut, "strOut", main_charName);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_reset") == 0) {
			four_reset();
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_boardGet") == 0) {
			char charOut[1024] = { };
			
			four_boardGet(charOut);
			
			cJSON_AddStringToObject(objectOut, "strOut", charOut);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_boardSet") == 0) {
			char charIn[1024] = { };
			
			strcpy(charIn, cJSON_GetObjectItem(objectIn, "strIn")->valuestring);
			
			four_boardSet(charIn);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_winner") == 0) {
			char charReturn[16] = { };
			
			charReturn[0] = four_winner();
			charReturn[1] = '\0';
			
			cJSON_AddStringToObject(objectOut, "strReturn", charReturn);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_isValid") == 0) {
			cJSON_AddBoolToObject(objectOut, "boolReturn", four_isValid(cJSON_GetObjectItem(objectIn, "intX")->valueint, cJSON_GetObjectItem(objectIn, "intY")->valueint));
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_isEnemy") == 0) {
			char charIn[16] = { };
			
			strcpy(charIn, cJSON_GetObjectItem(objectIn, "strPiece")->valuestring);
			
			cJSON_AddBoolToObject(objectOut, "boolReturn", four_isEnemy(charIn[0]));
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_isOwn") == 0) {
			char charIn[16] = { };
			
			strcpy(charIn, cJSON_GetObjectItem(objectIn, "strPiece")->valuestring);
			
			cJSON_AddBoolToObject(objectOut, "boolReturn", four_isOwn(charIn[0]));
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_isNothing") == 0) {
			char charIn[16] = { };
			
			strcpy(charIn, cJSON_GetObjectItem(objectIn, "strPiece")->valuestring);
			
			cJSON_AddBoolToObject(objectOut, "boolReturn", four_isNothing(charIn[0]));
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_eval") == 0) {
			cJSON_AddNumberToObject(objectOut, "intReturn", four_eval());
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_moves") == 0) {
			int intOut = 0;
			char charOut[1024] = { };
			
			intOut = four_moves(charOut);
			
			cJSON_AddNumberToObject(objectOut, "intOut", intOut);
			cJSON_AddStringToObject(objectOut, "strOut", charOut);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_movesShuffled") == 0) {
			int intOut = 0;
			char charOut[1024] = { };
			
			intOut = four_movesShuffled(charOut);
			
			cJSON_AddNumberToObject(objectOut, "intOut", intOut);
			cJSON_AddStringToObject(objectOut, "strOut", charOut);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_movesEvaluated") == 0) {
			int intOut = 0;
			char charOut[1024] = { };
			
			intOut = four_movesEvaluated(charOut);
			
			cJSON_AddNumberToObject(objectOut, "intOut", intOut);
			cJSON_AddStringToObject(objectOut, "strOut", charOut);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_move") == 0) {
			char charIn[16] = { };
			
			strcpy(charIn, cJSON_GetObjectItem(objectIn, "strIn")->valuestring);
			
			four_move(charIn);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_moveRandom") == 0) {
			char charOut[16] = { };
			
			four_moveRandom(charOut);
			
			cJSON_AddStringToObject(objectOut, "strOut", charOut);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_moveGreedy") == 0) {
			char charOut[16] = { };
			
			four_moveGreedy(charOut);
			
			cJSON_AddStringToObject(objectOut, "strOut", charOut);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_moveNegamax") == 0) {
			char charOut[16] = { };
			
			four_moveNegamax(charOut, cJSON_GetObjectItem(objectIn, "intMaxdepth")->valueint, cJSON_GetObjectItem(objectIn, "intDuration")->valueint);
			
			cJSON_AddStringToObject(objectOut, "strOut", charOut);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_moveAlphabeta") == 0) {
			char charOut[16] = { };
			
			four_moveAlphabeta(charOut, cJSON_GetObjectItem(objectIn, "intMaxdepth")->valueint, cJSON_GetObjectItem(objectIn, "intDuration")->valueint);
			
			cJSON_AddStringToObject(objectOut, "strOut", charOut);
			
		} else if (strcmp(cJSON_GetObjectItem(objectIn, "strFunction")->valuestring, "four_undo") == 0) {
			four_undo();
			
		}
		
		{
			char* charJson = cJSON_PrintUnformatted(objectOut);
			
			if (zmq_send(objectSocket, charJson, strlen(charJson), 0) == -1) {
				printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
			}
			
			free(charJson);
		}
		
		cJSON_Delete(objectIn);
		cJSON_Delete(objectOut);
	} while (zeromq_boolRunning == true);
	
	zmq_close(objectSocket);
	zmq_ctx_destroy(objectContext);
}

void zeromq_stop() {
	zeromq_boolRunning = false;
}
