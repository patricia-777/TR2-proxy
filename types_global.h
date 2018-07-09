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

#include <curl/curl.h>

#include <sys/stat.h>




#define TAM_BUFFER 1000
#define PORTA_PADRAO 8000
// #define PORTA_PADRAO 8228
#define IP_PADRAO "localhost"
// #define IP_PADRAO  "127.0.0.1"