/*
*
*	SNOOPY
*
*	Laís Mendes & Helena
*
*	TR2 1/2018
*
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
//#include <curses.h>


#define TAM_BUFFER 1000
#define PORTA_PADRAO 8000


int inicioSocketProxy (int porta);
int esperandoRequisicao (int proxy_socket);
int sendTextHeader (int socket, char *requisicao, char *host, char *http);
void serveText (int conexao_cliente, char *host, char *requisicao, char *http);
void camposRequisicao(char *buffer_requisicao, char *host, char *requisicao, char *http);
void dns(char *host, char *host_retorno);
