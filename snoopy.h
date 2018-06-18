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
<<<<<<< HEAD
//#include <curses.h>
=======
#include <curses.h>
>>>>>>> b82a256ad8af4453318fa315fc474b1a78625eac


#define TAM_BUFFER 1000
#define PORTA_PADRAO 8000


int inicioSocketProxy (int porta);
int esperandoRequisicao (int proxy_socket);
<<<<<<< HEAD
void sendTextHeader (int socket, char *buffer_requisicao);
void serveText (int proxy_socket, char *buffer_requisicao);
=======
void pedindoRequisicao (int porta, char *buffer_requisicao);
int sendTextHeader (int socket, char *host, char *pastas, char *htt_parte);
>>>>>>> b82a256ad8af4453318fa315fc474b1a78625eac
