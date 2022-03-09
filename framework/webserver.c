#include "main.h"

// TOOD: ENFORCE MUTUAL EXCLUSION

pthread_mutex_t webserver_objRunning = PTHREAD_MUTEX_INITIALIZER;

struct mg_mgr* webserver_objMongoose = NULL;
struct mg_connection* webserver_objConnection = NULL;

void webserver_handler(struct mg_connection* objConnection, int intEvent, void* voidData) {
    if (intEvent == MG_EV_HTTP_REQUEST) {
        struct http_message* objRequest = (struct http_message*) (voidData);
        
        printf("webserver: %.*s\n", (int) (objRequest->uri.len), objRequest->uri.p);
        
        if (objConnection->send_mbuf.len == 0) {
            if (mg_vcmp(&objRequest->uri, "/") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 302 Found\r\n");
                mg_printf(objConnection, "%s", "Location: /assets/index.html\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                mg_send_http_chunk(objConnection, "", 0);
                
            } else if (strncmp(objRequest->uri.p, "/assets/", strlen("/assets/"))  == 0) {
                struct mg_serve_http_opts objServe = { };
                
                objServe.document_root = ".";
                objServe.dav_document_root = ".";
                objServe.enable_directory_listing = "yes";
                
                mg_serve_http(objConnection, objRequest, objServe);
                
            }
        }
        
        if (objConnection->send_mbuf.len == 0) {
            if (zeromq_connected() == false) {
                mg_printf(objConnection, "%s", "HTTP/1.1 400 Bad Request\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                mg_send_http_chunk(objConnection, "", 0);
            }
        }
        
        if (objConnection->send_mbuf.len == 0) {
            if (mg_vcmp(&objRequest->uri, "/four_reset") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    four_reset();
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_boardGet") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    char charOut[1024] = { };
                    
                    four_boardGet(charOut);
                    
                    cJSON_AddStringToObject(objJson, "strOut", charOut);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_boardSet") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    char charIn[1024] = { };
                    
                    mg_get_http_var(&objRequest->query_string, "strIn", charIn, sizeof(charIn));
                    
                    four_boardSet(charIn);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_winner") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    char strReturn[16] = { };
                    
                    strReturn[0] = four_winner();
                    strReturn[1] = '\0';
                    
                    cJSON_AddStringToObject(objJson, "strReturn", strReturn);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_eval") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    cJSON_AddNumberToObject(objJson, "intReturn", four_eval());
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_moves") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    int intOut = 0;
                    char charOut[1024] = { };
                    
                    intOut = four_moves(charOut);
                    
                    cJSON_AddNumberToObject(objJson, "intOut", intOut);
                    cJSON_AddStringToObject(objJson, "strOut", charOut);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_move") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    char charIn[16] = { };
                    
                    mg_get_http_var(&objRequest->query_string, "strIn", charIn, sizeof(charIn));
                    
                    four_move(charIn);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_moveRandom") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    char charOut[16] = { };
                    
                    four_moveRandom(charOut);
                    
                    cJSON_AddStringToObject(objJson, "strOut", charOut);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_moveGreedy") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    char charOut[16] = { };
                    
                    four_moveGreedy(charOut);
                    
                    cJSON_AddStringToObject(objJson, "strOut", charOut);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_moveNegamax") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    char charOut[16] = { };
                    char charMaxdepth[16] = { };
                    char charDuration[16] = { };
                    
                    mg_get_http_var(&objRequest->query_string, "intMaxdepth", charMaxdepth, sizeof(charMaxdepth));
                    mg_get_http_var(&objRequest->query_string, "intDuration", charDuration, sizeof(charDuration));
                    
                    four_moveNegamax(charOut, atoi(charMaxdepth), atoi(charDuration));
                    
                    cJSON_AddStringToObject(objJson, "strOut", charOut);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_moveAlphabeta") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    char charOut[16] = { };
                    char charMaxdepth[16] = { };
                    char charDuration[16] = { };
                    
                    mg_get_http_var(&objRequest->query_string, "intMaxdepth", charMaxdepth, sizeof(charMaxdepth));
                    mg_get_http_var(&objRequest->query_string, "intDuration", charDuration, sizeof(charDuration));
                    
                    four_moveAlphabeta(charOut, atoi(charMaxdepth), atoi(charDuration));
                    
                    cJSON_AddStringToObject(objJson, "strOut", charOut);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/four_undo") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    four_undo();
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_board") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_board());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_winner") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_winner());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_isValid") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_isValid());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_isEnemy") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_isEnemy());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_isOwn") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_isOwn());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_isNothing") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_isNothing());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_eval") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_eval());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_moves") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_moves());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_move") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_move());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_undo") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_undo());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_movesShuffled") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_movesShuffled());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_movesEvaluated") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_movesEvaluated());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_moveRandom") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_moveRandom());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_moveGreedy") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_moveGreedy());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_moveNegamax") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_moveNegamax());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            } else if (mg_vcmp(&objRequest->uri, "/test_moveAlphabeta") == 0) {
                mg_printf(objConnection, "%s", "HTTP/1.1 200 OK\r\n");
                mg_printf(objConnection, "%s", "Transfer-Encoding: chunked\r\n");
                mg_printf(objConnection, "%s", "Content-Type: application/json\r\n");
                mg_printf(objConnection, "%s", "\r\n");
                
                cJSON* objJson = cJSON_CreateObject();
                
                {
                    unsigned long long longStart = milliseconds();
                    
                    cJSON_AddBoolToObject(objJson, "boolReturn", test_moveAlphabeta());
                    
                    unsigned long long longStop = milliseconds();
                    
                    cJSON_AddNumberToObject(objJson, "intBench", longStop - longStart);
                }
                
                {
                    char* charJson = cJSON_PrintUnformatted(objJson);
                    
                    mg_send_http_chunk(objConnection, charJson, strlen(charJson));
                    mg_send_http_chunk(objConnection, "", 0);
                    
                    free(charJson);
                }
                
                cJSON_Delete(objJson);
                
            }
        }
        
    } else if (intEvent == MG_EV_WEBSOCKET_HANDSHAKE_DONE) {
        webserver_broadcast("zeromq_status", NULL);
        
        webserver_broadcast("zeromq_name", NULL);
        
    } else if (intEvent == MG_EV_WEBSOCKET_FRAME) {
        
        
    }
}

void webserver_thread() {
    mg_mgr_init(webserver_objMongoose, NULL);
    
    {
        char charWebserver[1024] = { };
        
        sprintf(charWebserver, "%d", main_intWebserver);
        
        webserver_objConnection = mg_bind(webserver_objMongoose, charWebserver, webserver_handler);
    }

    mg_set_protocol_http_websocket(webserver_objConnection);

    do {
        mg_mgr_poll(webserver_objMongoose, 1000);
    } while (pthread_mutex_trylock(&webserver_objRunning) != 0);
    
    pthread_mutex_unlock(&webserver_objRunning);
    
    mg_mgr_free(webserver_objMongoose);
}

void webserver_start() {
    pthread_mutex_init(&webserver_objRunning, NULL);
    pthread_mutex_lock(&webserver_objRunning);
    
    webserver_objMongoose = (struct mg_mgr*) (malloc(sizeof(struct mg_mgr)));
    webserver_objConnection = NULL;
    
    pthread_t objThread = 0; pthread_create(&objThread, NULL, (void*) (webserver_thread), NULL);
}

void webserver_stop() {
    pthread_mutex_unlock(&webserver_objRunning);
    pthread_mutex_destroy(&webserver_objRunning);
}

void webserver_broadcast(char* charEvent, char* charData) {
    cJSON* objJson = cJSON_CreateObject();

    {
        cJSON_AddStringToObject(objJson, "strEvent", charEvent);

        if (strcmp(charEvent, "zeromq_status") == 0) {
            if (zeromq_connected() == false) {
                cJSON_AddStringToObject(objJson, "strData", "disconnected");
                
            } else if (zeromq_connected() == true) {
                cJSON_AddStringToObject(objJson, "strData", "connected");
                
            }
            
        } else if (strcmp(charEvent, "zeromq_name") == 0) {
            cJSON_AddStringToObject(objJson, "strData", zeromq_name());
            
        }
    }
    
    {
        char* charJson = cJSON_PrintUnformatted(objJson);
        
        {
            struct mg_connection* objConnection = mg_next(webserver_objMongoose, NULL);
            
            do {
                if (objConnection == NULL) {
                    break;
                }
                
                if ((objConnection->flags & MG_F_IS_WEBSOCKET) == MG_F_IS_WEBSOCKET) {
                    mg_send_websocket_frame(objConnection, WEBSOCKET_OP_TEXT, charJson, strlen(charJson));
                }
                
                objConnection = mg_next(webserver_objMongoose, objConnection);
            } while (true);
        }
        
        free(charJson);
    }
    
    cJSON_Delete(objJson);
}
