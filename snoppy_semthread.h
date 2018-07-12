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

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
//#include <curses.h>


#define TAM_BUFFER 1000
#define PORTA_PADRAO 8000


int inicioSocketProxy (int porta);
int esperandoRequisicao (int proxy_socket);
void sendTextHeader (int socket, char *buffer_requisicao);
void serveText (int proxy_socket, char *buffer_requisicao);