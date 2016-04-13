#include "main.h"

// TOOD: ENFORCE MUTUAL EXCLUSION

pthread_mutex_t webserver_pthreadmutexRunning = PTHREAD_MUTEX_INITIALIZER;

struct mg_mgr* webserver_mgmgrHandle = NULL;
struct mg_connection* webserver_mgconnectionHandle = NULL;

void webserver_handler(struct mg_connection* mgconnectionHandle, int intEvent, void* voidData) {
	if (intEvent == MG_EV_HTTP_REQUEST) {
		struct http_message* httpmessageHandle = (struct http_message*) (voidData);
		
		{
			printf("webserver: %.*s\n", (int) (httpmessageHandle->uri.len), httpmessageHandle->uri.p);
		}
		
		{
			if (mgconnectionHandle->send_mbuf.len == 0) {
				if (mg_vcmp(&httpmessageHandle->uri, "/") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 302 Found\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Location: /assets/index.html\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						mg_send_http_chunk(mgconnectionHandle, "", 0);
					}
					
				} else if (strncmp(httpmessageHandle->uri.p, "/assets/", strlen("/assets/"))  == 0) {
					{
						struct mg_serve_http_opts mgservehttpoptsHandle = { };
						
						mgservehttpoptsHandle.document_root = ".";
						mgservehttpoptsHandle.dav_document_root = ".";
						mgservehttpoptsHandle.enable_directory_listing = "yes";
						
						mg_serve_http(mgconnectionHandle, httpmessageHandle, mgservehttpoptsHandle);
					}
					
				}
			}
		}
		
		{
			if (mgconnectionHandle->send_mbuf.len == 0) {
				if (zeromq_connected() == false) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 400 Bad Request\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						mg_send_http_chunk(mgconnectionHandle, "", 0);
					}
				}
			}
		}
		
		{
			if (mgconnectionHandle->send_mbuf.len == 0) {
				if (mg_vcmp(&httpmessageHandle->uri, "/four_reset") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							four_reset();
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_boardGet") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							char charOut[1024] = { };
							
							four_boardGet(charOut);
							
							cJSON_AddStringToObject(cjsonHandle, "strOut", charOut);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_boardSet") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							char charIn[1024] = { };
							
							mg_get_http_var(&httpmessageHandle->query_string, "strIn", charIn, sizeof(charIn));
							
							four_boardSet(charIn);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_winner") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							char strReturn[16] = { };
							
							strReturn[0] = four_winner();
							strReturn[1] = '\0';
							
							cJSON_AddStringToObject(cjsonHandle, "strReturn", strReturn);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_eval") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							cJSON_AddNumberToObject(cjsonHandle, "intReturn", four_eval());
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_moves") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							int intOut = 0;
							char charOut[1024] = { };
							
							intOut = four_moves(charOut);
							
							cJSON_AddNumberToObject(cjsonHandle, "intOut", intOut);
							cJSON_AddStringToObject(cjsonHandle, "strOut", charOut);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_move") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							char charIn[16] = { };
							
							mg_get_http_var(&httpmessageHandle->query_string, "strIn", charIn, sizeof(charIn));
							
							four_move(charIn);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_moveRandom") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							char charOut[16] = { };
							
							four_moveRandom(charOut);
							
							cJSON_AddStringToObject(cjsonHandle, "strOut", charOut);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_moveGreedy") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							char charOut[16] = { };
							
							four_moveGreedy(charOut);
							
							cJSON_AddStringToObject(cjsonHandle, "strOut", charOut);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_moveNegamax") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							char charOut[16] = { };
							char charDepth[16] = { };
							char charDuration[16] = { };
							
							mg_get_http_var(&httpmessageHandle->query_string, "intDepth", charDepth, sizeof(charDepth));
							mg_get_http_var(&httpmessageHandle->query_string, "intDuration", charDuration, sizeof(charDuration));
							
							four_moveNegamax(charOut, atoi(charDepth), atoi(charDuration));
							
							cJSON_AddStringToObject(cjsonHandle, "strOut", charOut);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_moveAlphabeta") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							char charOut[16] = { };
							char charDepth[16] = { };
							char charDuration[16] = { };
							
							mg_get_http_var(&httpmessageHandle->query_string, "intDepth", charDepth, sizeof(charDepth));
							mg_get_http_var(&httpmessageHandle->query_string, "intDuration", charDuration, sizeof(charDuration));
							
							four_moveAlphabeta(charOut, atoi(charDepth), atoi(charDuration));
							
							cJSON_AddStringToObject(cjsonHandle, "strOut", charOut);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/four_undo") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							four_undo();
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_board") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_board());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_winner") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_winner());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_isValid") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_isValid());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_isEnemy") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_isEnemy());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_isOwn") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_isOwn());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_isNothing") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_isNothing());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_eval") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_eval());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_moves") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_moves());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_move") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_move());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_undo") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_undo());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_movesShuffled") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_movesShuffled());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_movesEvaluated") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_movesEvaluated());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_moveRandom") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_moveRandom());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_moveGreedy") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_moveGreedy());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_moveNegamax") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_moveNegamax());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				} else if (mg_vcmp(&httpmessageHandle->uri, "/test_moveAlphabeta") == 0) {
					{
						mg_printf(mgconnectionHandle, "%s", "HTTP/1.1 200 OK\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Transfer-Encoding: chunked\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "Content-Type: application/json\r\n");
						
						mg_printf(mgconnectionHandle, "%s", "\r\n");
					}
					
					{
						cJSON* cjsonHandle = cJSON_CreateObject();
						
						{
							unsigned long long longStart = milliseconds();
							
							cJSON_AddBoolToObject(cjsonHandle, "boolReturn", test_moveAlphabeta());
							
							unsigned long long longStop = milliseconds();
							
							cJSON_AddNumberToObject(cjsonHandle, "intBench", longStop - longStart);
						}
						
						{
							char* charJson = cJSON_PrintUnformatted(cjsonHandle);
							
							mg_send_http_chunk(mgconnectionHandle, charJson, strlen(charJson));
							mg_send_http_chunk(mgconnectionHandle, "", 0);
							
							free(charJson);
						}
						
						cJSON_Delete(cjsonHandle);
					}
					
				}
			}
		}
		
	} else if (intEvent == MG_EV_WEBSOCKET_HANDSHAKE_DONE) {
		{
			webserver_broadcast("zeromq_status", NULL);
			
			webserver_broadcast("zeromq_name", NULL);
		}
		
	} else if (intEvent == MG_EV_WEBSOCKET_FRAME) {
		
		
	}
}

void webserver_thread() {
	{
		mg_mgr_init(webserver_mgmgrHandle, NULL);
	}
	
	{
		char charWebserver[1024] = { };
		
		sprintf(charWebserver, "%d", main_intWebserver);
		
		webserver_mgconnectionHandle = mg_bind(webserver_mgmgrHandle, charWebserver, webserver_handler);
	}
	
	{
		mg_set_protocol_http_websocket(webserver_mgconnectionHandle);
	}
	
	{
		do {
			mg_mgr_poll(webserver_mgmgrHandle, 1000);
		} while (pthread_mutex_trylock(&webserver_pthreadmutexRunning) != 0);
		
		pthread_mutex_unlock(&webserver_pthreadmutexRunning);
	}
	
	{
		mg_mgr_free(webserver_mgmgrHandle);
	}
}

void webserver_start() {
	{
		pthread_mutex_init(&webserver_pthreadmutexRunning, NULL);
		
		pthread_mutex_lock(&webserver_pthreadmutexRunning);
	}
	
	{
		webserver_mgmgrHandle = (struct mg_mgr*) (malloc(sizeof(struct mg_mgr)));
		
		webserver_mgconnectionHandle = NULL;
	}
	
	{
		pthread_t pthreadHandle = 0;
		
		pthread_create(&pthreadHandle, NULL, (void*) (webserver_thread), NULL);
	}
}

void webserver_stop() {
	{
		pthread_mutex_unlock(&webserver_pthreadmutexRunning);
		
		pthread_mutex_destroy(&webserver_pthreadmutexRunning);
	}
}

void webserver_broadcast(char* charEvent, char* charData) {
	{
		cJSON* cjsonHandle = cJSON_CreateObject();
		
		{
			cJSON_AddStringToObject(cjsonHandle, "strEvent", charEvent);
		}
		
		{
			if (strcmp(charEvent, "zeromq_status") == 0) {
				if (zeromq_connected() == false) {
					cJSON_AddStringToObject(cjsonHandle, "strData", "disconnected");
					
				} else if (zeromq_connected() == true) {
					cJSON_AddStringToObject(cjsonHandle, "strData", "connected");
					
				}
				
			} else if (strcmp(charEvent, "zeromq_name") == 0) {
				cJSON_AddStringToObject(cjsonHandle, "strData", zeromq_name());
				
			} 
		}
		
		{
			char* charJson = cJSON_PrintUnformatted(cjsonHandle);
			
			{
				struct mg_connection* mgconnectionHandle = mg_next(webserver_mgmgrHandle, NULL);
				
				do {
					if (mgconnectionHandle == NULL) {
						break;
					}
					
					{
						if ((mgconnectionHandle->flags & MG_F_IS_WEBSOCKET) == MG_F_IS_WEBSOCKET) {
							mg_send_websocket_frame(mgconnectionHandle, WEBSOCKET_OP_TEXT, charJson, strlen(charJson));
						}
					}
					
					{
						mgconnectionHandle = mg_next(webserver_mgmgrHandle, mgconnectionHandle);
					}
				} while (true);
			}
			
			free(charJson);
		}
		
		cJSON_Delete(cjsonHandle);
	}
}
