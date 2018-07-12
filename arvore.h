#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM_BUFFER 1000
#define PORTA_PADRAO 8000
char host[TAM_BUFFER];

struct Spider{
	char modulo[50];	//nome da pasta ou do arquivo entre as barras "/"
	struct Spider *filho[30];	//lista para armazenar os arquivos ou pastas contidos na pasta pai
};
void procuraPath (char *buffer, char *path);
int pegaPath(char *);
void pushArvore (char * , int );
void imprimeSpider();

struct Spider *spider;
