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

typedef struct MinhaJanela {

	GtkWidget *window;
	GtkWidget *botao1;
	GtkWidget *botao2;
	GtkWidget *botao3;
	GtkWidget *botao4;
	GtkWidget *texto1;
	GtkWidget *texto2;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *grid;
  	GtkWidget *view1;
  	GtkTextBuffer *buffer1;
  	GtkWidget *view2;
  	GtkTextBuffer *buffer2;
  	GtkWidget *view3;
  	GtkTextBuffer *buffer3;
  	GtkWidget *view4;
  	GtkTextBuffer *buffer4;


	char *string1;
	char *string2;
	char *string3;
	char *string4;

} JanelaPrincipal;

	
static void botao_clicado1(GtkWidget *, gpointer);
static void botao_clicado2(GtkWidget *, gpointer);
static void botao_clicado3(GtkWidget *, gpointer);
static void botao_clicado4(GtkWidget *, gpointer);

int requisito_socket;
int conexao_cliente;
char host[TAM_BUFFER];
char requisicao[TAM_BUFFER];
char http[TAM_BUFFER];
char buffer_requisicao[TAM_BUFFER];



int inicioSocketProxy (int porta);
int esperandoRequisicao (int proxy_socket);
int sendTextHeader (int socket, char *requisicao, char *host, char *http);
void serveText (int conexao_cliente, char *host, char *requisicao, char *http);
void camposRequisicao(char *buffer_requisicao, char *host, char *requisicao, char *http);
void dns(char *host, char *host_retorno);

int requestOption();

void replyOption();
int print_options(void);

