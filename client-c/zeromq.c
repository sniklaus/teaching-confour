#include "main.h"

bool zeromq_boolRunning = false;

void zeromq_start() {
	{
		zeromq_boolRunning = true;
	}
	
	{
		void* contextHandle = zmq_ctx_new();
		void* socketHandle = zmq_socket(contextHandle, ZMQ_PAIR);
		
		{
			char charZeromq[1024] = { };
			
			sprintf(charZeromq, "tcp://*:%d", main_intZeromq);
			
			if (zmq_bind(socketHandle, charZeromq) == -1) {
				printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
			}
		}
		
		{
			do {
				cJSON* cjsonIn = NULL;
				cJSON* cjsonOut = cJSON_CreateObject();
				
				{
					char charJson[1024] = { };
					
					if (zmq_recv(socketHandle, charJson, sizeof(charJson), 0) == -1) {
						printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
					}
					
					cjsonIn = cJSON_Parse(charJson);
				}
				
				{
					if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "ping") == 0) {
						cJSON_AddStringToObject(cjsonOut, "strOut", main_charName);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_reset") == 0) {
						four_reset();
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_boardGet") == 0) {
						char charOut[1024] = { };
						
						four_boardGet(charOut);
						
						cJSON_AddStringToObject(cjsonOut, "strOut", charOut);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_boardSet") == 0) {
						char charIn[1024] = { };
						
						strcpy(charIn, cJSON_GetObjectItem(cjsonIn, "strIn")->valuestring);
						
						four_boardSet(charIn);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_winner") == 0) {
						char charReturn[16] = { };
						
						charReturn[0] = four_winner();
						charReturn[1] = '\0';
						
						cJSON_AddStringToObject(cjsonOut, "strReturn", charReturn);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_isValid") == 0) {
						cJSON_AddBoolToObject(cjsonOut, "boolReturn", four_isValid(cJSON_GetObjectItem(cjsonIn, "intX")->valueint, cJSON_GetObjectItem(cjsonIn, "intY")->valueint));
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_isEnemy") == 0) {
						char charIn[16] = { };
						
						strcpy(charIn, cJSON_GetObjectItem(cjsonIn, "strPiece")->valuestring);
						
						cJSON_AddBoolToObject(cjsonOut, "boolReturn", four_isEnemy(charIn[0]));
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_isOwn") == 0) {
						char charIn[16] = { };
						
						strcpy(charIn, cJSON_GetObjectItem(cjsonIn, "strPiece")->valuestring);
						
						cJSON_AddBoolToObject(cjsonOut, "boolReturn", four_isOwn(charIn[0]));
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_isNothing") == 0) {
						char charIn[16] = { };
						
						strcpy(charIn, cJSON_GetObjectItem(cjsonIn, "strPiece")->valuestring);
						
						cJSON_AddBoolToObject(cjsonOut, "boolReturn", four_isNothing(charIn[0]));
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_eval") == 0) {
						cJSON_AddNumberToObject(cjsonOut, "intReturn", four_eval());
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_moves") == 0) {
						int intOut = 0;
						char charOut[1024] = { };
						
						intOut = four_moves(charOut);
						
						cJSON_AddNumberToObject(cjsonOut, "intOut", intOut);
						cJSON_AddStringToObject(cjsonOut, "strOut", charOut);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_movesShuffled") == 0) {
						int intOut = 0;
						char charOut[1024] = { };
						
						intOut = four_movesShuffled(charOut);
						
						cJSON_AddNumberToObject(cjsonOut, "intOut", intOut);
						cJSON_AddStringToObject(cjsonOut, "strOut", charOut);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_movesEvaluated") == 0) {
						int intOut = 0;
						char charOut[1024] = { };
						
						intOut = four_movesEvaluated(charOut);
						
						cJSON_AddNumberToObject(cjsonOut, "intOut", intOut);
						cJSON_AddStringToObject(cjsonOut, "strOut", charOut);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_move") == 0) {
						char charIn[16] = { };
						
						strcpy(charIn, cJSON_GetObjectItem(cjsonIn, "strIn")->valuestring);
						
						four_move(charIn);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_moveRandom") == 0) {
						char charOut[16] = { };
						
						four_moveRandom(charOut);
						
						cJSON_AddStringToObject(cjsonOut, "strOut", charOut);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_moveGreedy") == 0) {
						char charOut[16] = { };
						
						four_moveGreedy(charOut);
						
						cJSON_AddStringToObject(cjsonOut, "strOut", charOut);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_moveNegamax") == 0) {
						char charOut[16] = { };
						
						four_moveNegamax(charOut, cJSON_GetObjectItem(cjsonIn, "intDepth")->valueint, cJSON_GetObjectItem(cjsonIn, "intDuration")->valueint);
						
						cJSON_AddStringToObject(cjsonOut, "strOut", charOut);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_moveAlphabeta") == 0) {
						char charOut[16] = { };
						
						four_moveAlphabeta(charOut, cJSON_GetObjectItem(cjsonIn, "intDepth")->valueint, cJSON_GetObjectItem(cjsonIn, "intDuration")->valueint);
						
						cJSON_AddStringToObject(cjsonOut, "strOut", charOut);
						
					} else if (strcmp(cJSON_GetObjectItem(cjsonIn, "strFunction")->valuestring, "four_undo") == 0) {
						four_undo();
						
					}
				}
				
				{
					char* charJson = cJSON_PrintUnformatted(cjsonOut);
					
					if (zmq_send(socketHandle, charJson, strlen(charJson), 0) == -1) {
						printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
					}
					
					free(charJson);
				}
				
				cJSON_Delete(cjsonIn);
				cJSON_Delete(cjsonOut);
			} while (zeromq_boolRunning == true);
		}
		
		zmq_close(socketHandle);
		zmq_ctx_destroy(contextHandle);
	}
}

void zeromq_stop() {
	{
		zeromq_boolRunning = false;
	}
}
