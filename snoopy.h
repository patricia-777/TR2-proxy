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

struct Spider{
	char modulo[TAM_BUFFER];	//nome da pasta ou do arquivo entre as barras "/"
	struct Spider *filho[TAM_BUFFER];	//lista para armazenar os arquivos ou pastas contidos na pasta pai
};
void procuraPath (char *);
int pegaPath(char *);
void pushArvore (char * , int );
void imprimeSpider();

struct Spider *spider;

int requisito_socket;
int conexao_cliente;
char host[TAM_BUFFER];
char requisicao[TAM_BUFFER];
char http[TAM_BUFFER];
char buffer_requisicao[TAM_BUFFER];
char buffer_requisicao_editada[TAM_BUFFER];
char buffer_reply_editada[TAM_BUFFER];
int proxy_socket;
int PORTA;



int inicioSocketProxy (int porta);
int esperandoRequisicao (int proxy_socket);
int sendTextHeader (int socket, char *requisicao, char *host, char *http);
void serveText (int conexao_cliente, char *host, char *requisicao, char *http);
void camposRequisicao(char *buffer_requisicao, char *host, char *requisicao, char *http);
void dns(char *host, char *host_retorno);
int requestOption(int requisito_socket, int conexao_cliente, char *host, char *requisicao, char *http, char *buffer_requisicao);
char* replyOption(int requisito_socket, int conexao_cliente, char *host, char *requisicao, char *http, int opcao, char *ponteiro_reply);


/*!\brief proxy funcao principal que aceita uma requisicao e retorna um vetor com a resposta
 *
 * Essa funcao e usada por todas as funcionalidades do projeto, fazendo as requisicoes e retornando
 * a resposta do servidor externo.
 */
char* proxy(int vezes_while, int opcao, int primeira_requisicao);

