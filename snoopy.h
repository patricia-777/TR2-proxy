/*
*
*	SNOOPY
*
*	Laís Mendes & Helena
*
*	TR2 1/2018
*
*/



#include "types_global.h"
#include "snoopy_dump.h"



int inicioSocketProxy (int porta);
int esperandoRequisicao (int proxy_socket);
int sendTextHeader (int socket, char *requisicao, char *host, char *http);
void serveText (int conexao_cliente, char *host, char *requisicao, char *http);
void camposRequisicao(char *buffer_requisicao, char *host, char *requisicao, char *http);
void dns(char *host, char *host_retorno);

int requestOption(int requisito_socket, int conexao_cliente, char *host, char *requisicao, char *http, char *buffer_requisicao);

void replyOption(int requisito_socket, int conexao_cliente, char *host, char *requisicao, char *http);
int print_options(void);

