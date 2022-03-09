#include "main.h"

bool zeromq_boolRunning = false;

void zeromq_start() {
    zeromq_boolRunning = true;

    void* objContext = zmq_ctx_new();
    void* objSocket = zmq_socket(objContext, ZMQ_PAIR);
    
    {
        char charZeromq[1024] = { };
        
        sprintf(charZeromq, "tcp://*:%d", main_intZeromq);
        
        if (zmq_bind(objSocket, charZeromq) == -1) {
            printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
        }
    }

    do {
        cJSON* objIn = NULL;
        cJSON* objOut = cJSON_CreateObject();
        
        {
            char charJson[1024] = { };
            
            if (zmq_recv(objSocket, charJson, sizeof(charJson), 0) == -1) {
                printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
            }
            
            objIn = cJSON_Parse(charJson);
        }
    
        if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "ping") == 0) {
            cJSON_AddStringToObject(objOut, "strOut", main_charName);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_reset") == 0) {
            four_reset();
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_boardGet") == 0) {
            char charOut[1024] = { };
            
            four_boardGet(charOut);
            
            cJSON_AddStringToObject(objOut, "strOut", charOut);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_boardSet") == 0) {
            char charIn[1024] = { };
            
            strcpy(charIn, cJSON_GetObjectItem(objIn, "strIn")->valuestring);
            
            four_boardSet(charIn);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_winner") == 0) {
            char charReturn[16] = { };
            
            charReturn[0] = four_winner();
            charReturn[1] = '\0';
            
            cJSON_AddStringToObject(objOut, "strReturn", charReturn);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_isValid") == 0) {
            cJSON_AddBoolToObject(objOut, "boolReturn", four_isValid(cJSON_GetObjectItem(objIn, "intX")->valueint, cJSON_GetObjectItem(objIn, "intY")->valueint));
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_isEnemy") == 0) {
            char charIn[16] = { };
            
            strcpy(charIn, cJSON_GetObjectItem(objIn, "strPiece")->valuestring);
            
            cJSON_AddBoolToObject(objOut, "boolReturn", four_isEnemy(charIn[0]));
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_isOwn") == 0) {
            char charIn[16] = { };
            
            strcpy(charIn, cJSON_GetObjectItem(objIn, "strPiece")->valuestring);
            
            cJSON_AddBoolToObject(objOut, "boolReturn", four_isOwn(charIn[0]));
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_isNothing") == 0) {
            char charIn[16] = { };
            
            strcpy(charIn, cJSON_GetObjectItem(objIn, "strPiece")->valuestring);
            
            cJSON_AddBoolToObject(objOut, "boolReturn", four_isNothing(charIn[0]));
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_eval") == 0) {
            cJSON_AddNumberToObject(objOut, "intReturn", four_eval());
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_moves") == 0) {
            int intOut = 0;
            char charOut[1024] = { };
            
            intOut = four_moves(charOut);
            
            cJSON_AddNumberToObject(objOut, "intOut", intOut);
            cJSON_AddStringToObject(objOut, "strOut", charOut);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_movesShuffled") == 0) {
            int intOut = 0;
            char charOut[1024] = { };
            
            intOut = four_movesShuffled(charOut);
            
            cJSON_AddNumberToObject(objOut, "intOut", intOut);
            cJSON_AddStringToObject(objOut, "strOut", charOut);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_movesEvaluated") == 0) {
            int intOut = 0;
            char charOut[1024] = { };
            
            intOut = four_movesEvaluated(charOut);
            
            cJSON_AddNumberToObject(objOut, "intOut", intOut);
            cJSON_AddStringToObject(objOut, "strOut", charOut);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_move") == 0) {
            char charIn[16] = { };
            
            strcpy(charIn, cJSON_GetObjectItem(objIn, "strIn")->valuestring);
            
            four_move(charIn);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_moveRandom") == 0) {
            char charOut[16] = { };
            
            four_moveRandom(charOut);
            
            cJSON_AddStringToObject(objOut, "strOut", charOut);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_moveGreedy") == 0) {
            char charOut[16] = { };
            
            four_moveGreedy(charOut);
            
            cJSON_AddStringToObject(objOut, "strOut", charOut);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_moveNegamax") == 0) {
            char charOut[16] = { };
            
            four_moveNegamax(charOut, cJSON_GetObjectItem(objIn, "intMaxdepth")->valueint, cJSON_GetObjectItem(objIn, "intDuration")->valueint);
            
            cJSON_AddStringToObject(objOut, "strOut", charOut);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_moveAlphabeta") == 0) {
            char charOut[16] = { };
            
            four_moveAlphabeta(charOut, cJSON_GetObjectItem(objIn, "intMaxdepth")->valueint, cJSON_GetObjectItem(objIn, "intDuration")->valueint);
            
            cJSON_AddStringToObject(objOut, "strOut", charOut);
            
        } else if (strcmp(cJSON_GetObjectItem(objIn, "strFunction")->valuestring, "four_undo") == 0) {
            four_undo();
            
        }
        
        {
            char* charJson = cJSON_PrintUnformatted(objOut);
            
            if (zmq_send(objSocket, charJson, strlen(charJson), 0) == -1) {
                printf("zeromq: %s\n", zmq_strerror(zmq_errno()));
            }
            
            free(charJson);
        }
        
        cJSON_Delete(objIn);
        cJSON_Delete(objOut);
    } while (zeromq_boolRunning == true);
    
    zmq_close(objSocket);
    zmq_ctx_destroy(objContext);
}

void zeromq_stop() {
    zeromq_boolRunning = false;
}
