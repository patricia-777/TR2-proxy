/*
*
*	SNOOPY
*
*	Laís Mendes & Helena
*
*	TR2 1/2018
*
*/

#include "snoopy.h"



char* proxy(int vezes_while, int opcao, int primeira_requisicao)
{
	int comparacao, servidor_conectado;
	int tam_requisicao, option;
	struct sockaddr_in cliente_addr;
	socklen_t cliente_tam;
	int conexao_cliente;
	char c;
	char *ponteiro_reply = NULL;


	proxy_socket = inicioSocketProxy(PORTA);

	//se for proxy --> vezes_while==1
	//se for dump ou spider --> vezes_while==0
	do
    {

    	if (opcao == PROXY || opcao == INSPECAO || primeira_requisicao)
    	{
		    //habilita o servidor a rceber conexoes dos clientes
		    listen (proxy_socket, 1);
		    
		    printf ("[PROXY/INSPECTOR] Esperando requisicao...\n");

		    // aceitando as conexoes do cliente e verificando se houve erro
		    cliente_tam = sizeof (cliente_addr);
		    conexao_cliente = accept (proxy_socket, (struct sockaddr *)&cliente_addr, &cliente_tam);
		    if (conexao_cliente < 0) 
		    {
		        errx (EXIT_FAILURE, "Erro ao aceitar conexao do cliente");
		    }


	        //essa funcao le o que esta no socket, e retorna o tamanho da mensagem ou -1 se tiver erro
	        bzero((char*)buffer_requisicao, TAM_BUFFER);
	        tam_requisicao = recv (conexao_cliente, buffer_requisicao, TAM_BUFFER, 0);
	        if (tam_requisicao < 0) 
	        {
	            errx (EXIT_FAILURE, "Erro ao ler a requisição");
	        }
		}

		if (opcao == INSPECAO)
		{
			printf ("[INSPECTOR] Requisição recebida: %s\n", buffer_requisicao);

			printf("[INSPECTOR] Escreva a requisição editada: ");

			scanf("%s", buffer_requisicao_editada);

	    	bzero((char*)buffer_requisicao, TAM_BUFFER);
	    	strcat(buffer_requisicao,"GET http://");
	    	strcat(buffer_requisicao,buffer_requisicao_editada);
	    	strcat(buffer_requisicao," HTTP/1.1\nHost: ");
	    	strcat(buffer_requisicao,buffer_requisicao_editada);

	    	printf ("[INSPECTOR] Requisição editada: %s\n", buffer_requisicao);
		}

    	servidor_conectado = requestOption(requisito_socket, conexao_cliente, host, requisicao, http, buffer_requisicao);

        if (servidor_conectado)
        {
	        printf ("[AGUARDE] Enviando resposta...\n");

	        ponteiro_reply = (char*)malloc((TAM_BUFFER+1)*sizeof(char));
			ponteiro_reply = replyOption(requisito_socket, conexao_cliente, host, requisicao, http, opcao, ponteiro_reply);


	        printf ("[AGUARDE] Resposta enviada\n");
	        printf ("[AGUARDE] Conexão fechada\n\n\n");
        }
        //se a conexao nao for http, uma mensagem é enviada para o usuario
		else
		{
			send(conexao_cliente,"ERROR : SORRY DUDE!\nAPENAS CONEXÕES HTTP SÃO PERMITIDAS",60,0);
		} 

    	close(conexao_cliente);

    	bzero((char*)buffer_requisicao, TAM_BUFFER);
 
    }while(vezes_while);

    return ponteiro_reply;
}




//Função da opção request, retorna 1 se for conexao http e retorna 0 se for https
int requestOption()
{
	int tam_requisicao;
	int comparacao, flag_http, n;
	char c;


    //MOSTRAR AQUI O BUFFER E DEPOIS DO BOTAO REQUEST FOR CLICADO VERIFICAR O BUFFER

    //tratando da requisição
	//separando as informacoes de host, pasta, e http
    camposRequisicao(buffer_requisicao, host, requisicao, http);

    //se a requisição for http entao entra no if e faz a conexao
	comparacao = strncmp(http, "HTTP/", 5);
    if (!comparacao)
    {
    	printf ("[REQUEST] Conectando ao servidor externo...\n");

    	flag_http = 1;
    }
    else
    {
    	flag_http = 0;
    }

    return flag_http;
}


char* replyOption(int requisito_socket, int conexao_cliente, char *host, char *requisicao, char *http, int opcao, char *ponteiro_reply)
{
    struct sockaddr_in ext_addr;
    int requisicao_conexao, n;
    char buffer[TAM_BUFFER];
    int option;

	char host_ip[INET_ADDRSTRLEN];


    // criando socket e verificando se houve erro
    requisito_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (requisito_socket < 0) 
    {
        errx (EXIT_FAILURE, "Erro ao criar o socket do proxy");
    }


    //pegando endereço ip do host solicitado pelo usuario
    dns(host, host_ip);

    //colocando os parametros para fazer a conexao do socket com o servidor do site externo
    ext_addr.sin_family = AF_INET;
    ext_addr.sin_addr.s_addr = inet_addr(host_ip);
    ext_addr.sin_port = htons(80);


    requisicao_conexao = connect(requisito_socket,(struct sockaddr*)&ext_addr,sizeof(struct sockaddr));
    if (requisicao_conexao < 0) 
    {
        errx (EXIT_FAILURE, "Erro de conexao ao servidor remoto");
    }

    // printf("CONECTADO AO SERVIDOR EXTERNO\n");

    //mandando header para o servidor externo
    n = sendTextHeader (requisito_socket, requisicao, host, http);

    // printf("ENVIANDO HEADER\n");

	if(n<0)
	{
		errx (EXIT_FAILURE, "Error writing to socket");
	}
	else
	{
		do
		{
			//zerando buffer para pegar mais respostas
			bzero((char*)buffer,TAM_BUFFER);

			//le do socket de 1000 em 1000
			n=recv(requisito_socket,buffer,TAM_BUFFER,0);

			//enquanto tiver dados no buffer ele le e envia ao usuario
			if(!(n<=0))
			{

				if (opcao == DUMP || opcao == SPIDER)
				{
					strcat(ponteiro_reply,buffer);
					// printf("REQUISICAO---->>>%s\n", buffer);
					ponteiro_reply = (char*)realloc(ponteiro_reply, (TAM_BUFFER+1)*sizeof(char));

					//mostrando uma mensagem de satisfação para o cliente
					char *message = "Processando pedido...\n";
					send (conexao_cliente, message, strlen (message), 0);
				}
				else
				{
					if (EDITAR_REPLY)
					{
						bzero((char*)buffer_reply_editada, TAM_BUFFER);
						printf ("[REPLY] Resposta recebida: %s\n", buffer);

						printf("[REPLY] Escreva a resposta editada: ");

						scanf("%s", buffer_reply_editada);

						send(conexao_cliente,buffer_reply_editada,n,0);
					}
					else
					{
						send(conexao_cliente,buffer,n,0);	
					}
				}
			}

		} while(n>0);
	}

    close(requisito_socket);
	close(conexao_cliente);


	return ponteiro_reply;

}


//Funcao que faz as vezes de um DNS, traduzindo para o ip o nome do host
void dns(char *host, char *host_retorno)
{
	struct hostent* host_ip_structure;
	char host_ip[INET_ADDRSTRLEN];

	//pesuisando pelo host qual as informaçoes dns dele
	host_ip_structure = gethostbyname(host);
	//verificando se deu erro a pesquisa
	if (host_ip_structure == NULL)
	{
		errx (EXIT_FAILURE, "Erro na pesquisa de DNS");
	}

	//pegando o parametro endereço ip da struct retornada
	inet_ntop(AF_INET,(void *)host_ip_structure->h_addr,host_ip,sizeof(host_ip));

	//copiando endereço ip para o buffer da função principal
	//fazer isso porque dava erro ao retornar como um cahr simples
	//ou quando usava direto o buffer que recebeu como parametro
	sprintf(host_retorno,"%s",host_ip);
}


//funcao para separar a requisicao em hos, diretorio, http
void camposRequisicao(char *buffer_requisicao, char *host, char *requisicao, char *http)
{
	char *aux = NULL, *aux_req = NULL;
	char aux_concat[TAM_BUFFER];
	char dados_lixo[TAM_BUFFER];

	//pegando a parte GET do cabeçalho da requisição
	//dividido em GET http://site HTTP
	aux = strtok(buffer_requisicao,"\n");
	sscanf(aux,"%s %s %s", dados_lixo, requisicao, http);

	//pegando atributo host do cabeçalho
	//no formato Host: site.com.br
	aux = strtok(NULL,"\n");
	sscanf(aux,"%s %s", dados_lixo, host);


	//pegando a parte de requisição e isolando somenete o diretorio que foi pedido
	//http://site.com.br/diretorio.html
	aux_req = strtok(requisicao, "/");
	aux_req = strtok(NULL, "/");
	aux_req = strtok(NULL, "/");

	//passa o resultado para requisicao
	sprintf(requisicao,"%s",aux_req);

	//verifica se tem mais de um diretorio na requisição
	//pega outros diretorios da requisição e concatena com o primeiro
	aux_req = strtok(NULL, "/");
	while (aux_req != NULL)
	{
		//concatena com a /
		strcat(requisicao, "/");
		
		//passa o valor do diretorio para outra variavel
		sprintf(aux_concat,"%s",aux_req);

		//concatena essa variavel com o valor anterior do diretorio
		strcat(requisicao, aux_concat);
		
		//verifica se tem mais algum diretorio
		aux_req = strtok(NULL, "/");
	}
}


//funcao que manda a requisição para o servidor externo
int sendTextHeader (int socket, char *requisicao, char *host, char *http) 
{
    char message[TAM_BUFFER];
    int comparacao;
    int n;

    comparacao = strcmp(requisicao, "(null)");
    if(!comparacao)
    {
    	sprintf(message,"GET / %s\r\nHost: %s\r\nConnection: close\r\n\r\n",http, host);
    }
    else
    {
		sprintf(message,"GET /%s %s\r\nHost: %s\r\nConnection: close\r\n\r\n",requisicao, http, host);
    }

    n = send (socket, message, strlen (message), 0);

    return n;
}







// void serveText (int conexao_cliente, char *host, char *requisicao, char *http) 
// {
//     struct sockaddr_in ext_addr;
//     int requisito_socket, requisicao_conexao, n;
//     char buffer[TAM_BUFFER];

// 	char host_ip[INET_ADDRSTRLEN];


//     // criando socket e verificando se houve erro
//     requisito_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (requisito_socket < 0) 
//     {
//         errx (EXIT_FAILURE, "Erro ao criar o socket do proxy");
//     }


//     //pegando endereço ip do host solicitado pelo usuario
//     dns(host, host_ip);

//     //colocando os parametros para fazer a conexao do socket com o servidor do site externo
//     ext_addr.sin_family = AF_INET;
//     ext_addr.sin_addr.s_addr = inet_addr(host_ip);
//     ext_addr.sin_port = htons(80);


//     requisicao_conexao = connect(requisito_socket,(struct sockaddr*)&ext_addr,sizeof(struct sockaddr));
//     if (requisicao_conexao < 0) 
//     {
//         errx (EXIT_FAILURE, "Erro de conexao ao servidor remoto");
//     }

//     //mandando header para o servidor externo
//     n = sendTextHeader (requisito_socket, requisicao, host, http);


//     //lendo a resposta do servidor externo e enviando de volta para o cliente
//     if(n<0)
// 	{
// 		errx (EXIT_FAILURE, "Error writing to socket");
// 	}
// 	else
// 	{
// 	    do
// 	    {
// 	        //zerando buffer para pegar mais respostas
// 	        bzero((char*)buffer,TAM_BUFFER);
	        
// 	        //le do socket de 1000 em 1000
// 	        n=recv(requisito_socket,buffer,TAM_BUFFER,0);

// 	        ////////////////////////////////////////////////

// 	        ////----->>>>AQUI VAI O REPLY, MOSTRAR O BUFFER ANTES DE ENVIAR PELO SEND
	        
// 	        ///////////////////////////////////////////////

// 	        //enquanto tiver dados no buffer ele le e envia ao usuario
// 	        if(!(n<=0))
// 	        {
// 	            send(conexao_cliente,buffer,n,0);
// 	        }
// 	        // else
// 	        // {
// 	        // 	printf("Erro recv -->%s\n", strerror(errno));
// 	        // }
// 	    } while(n>0);
// 	}

// 	//fecha as conexoes com o servidor externo e a conexao do cliente com o proxy
// 	//desse filho
// 	close(requisito_socket);
// 	close(conexao_cliente);
// }


// esperando requisiçoes feitas pelo browser
// returns the socket on which the conversation will take place
int esperandoRequisicao (int proxy_socket) 
{
	struct sockaddr_in cliente_addr;
	socklen_t cliente_tam;
	int conexao_cliente;



    //habilita o servidor a rceber conexoes dos clientes
    listen (proxy_socket, 1);

    // aceitando as conexoes do cliente e verificando se houve erro
    cliente_tam = sizeof (cliente_addr);
    conexao_cliente = accept (proxy_socket, (struct sockaddr *)&cliente_addr, &cliente_tam);
    if (conexao_cliente < 0) 
    {
        errx (EXIT_FAILURE, "Erro ao aceitar conexao do cliente");
    }

    return conexao_cliente;
}


// habilitando o proxy a ouvir uma porta específica
int inicioSocketProxy (int porta) 
{
	int proxy_socket, bind_status;
	struct sockaddr_in proxy_addr;

    // criando socket e verificando se houve erro
    proxy_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (proxy_socket < 0) 
    {
        errx (EXIT_FAILURE, "Erro ao criar o socket do proxy");
    }

    // configuração para fazer o proxy ouvir na porta definida
    proxy_addr.sin_family = AF_INET;
    // proxy_addr.sin_addr.s_addr = inet_addr(IP_PADRAO);
    proxy_addr.sin_addr.s_addr = INADDR_ANY;
    proxy_addr.sin_port = htons(porta);

    //faz o bind no socket do proxy com endereço e porta que ele vai funcionar
    bind_status = bind (proxy_socket, (struct sockaddr *)&proxy_addr, sizeof (proxy_addr));
    if (bind_status < 0) 
    {
        errx (EXIT_FAILURE, "Erro no bind da porta do proxy");
    }

    return proxy_socket;
}

void procuraPath (char *buffer){
	char *p = buffer;
	char *fim, *b, req[60];
	int tamanho;

	
	//para href
	b=buffer;
	while(b!=NULL){

		//procura pelo href
		p=strstr(b, "href=");
	
		//se achou, continua
		if(p!=NULL){
			//ai procura ate achar as proximas aspas
			//6 = 4 caracteres em href e mais dois em =", soma-se 6 para ultrapassar as primeiras aspas
			fim=strchr((p+6), '\"');
			//pega o tamanho de tudo contigo entre as aspas
			tamanho = fim - p;
			//joga em req
			strncpy(req, (p+6), (tamanho-6));
			req[tamanho-6] = '\0';
			pegaPath(req);
			//procura no restante do buffer
			b=fim;
		}else
			b=NULL;

	}

	//para src
	
	b=buffer;
	while(b!=NULL){

		//procura pelo href
		p=strstr(b, "src=");
	
		//se achou, continua
		if(p!=NULL){
			//ai procura ate achar as proximas aspas
			//6 = 4 caracteres em href e mais dois em =", soma-se 6 para ultrapassar as primeiras aspas
			fim=strchr((p+5), '\"');
			//pega o tamanho de tudo contigo entre as aspas
			tamanho = fim - p;
			//joga em req
			strncpy(req, (p+5), (tamanho-5));
			req[tamanho-5] = '\0';
			pegaPath(req);
			//procura no restante do buffer
			b=fim;
		}else
			b=NULL;

	}

}

int pegaPath (char * path){
	char *p;
	char *fim, *b, req[60];
	int tamanho;
	int profundidade = 0; 	

	b = path;

	//checa pra ver se o primeiro caractere é /, pra ver se é http:// ou pra ver se é caracte
	if(path[4]==':'){
		b=path+7;
		p=b;
		fim=strchr((p+1), '/');
		//pega o tamanho de tudo contigo entre as barras
		tamanho = fim - p+1;
		//joga em req
		strncpy(req, (p), (tamanho));
		req[tamanho-1] = '\0';

		//é o host mesmo?
		if(strcmp(host,req)!=0)
			return -1;

		}else{
			if(path[0]!='/'){
				while(b!=NULL){
					//se tá no início
					if(b==path)
						p=b;
					else{
						//ou se já passou no inicio
						p=strchr(b, '/');
					}
					//se achou, continua
					if(p!=NULL){
						profundidade++;
						//ai procura ate achar a proxima barra ou fim
						fim=strchr((p+1), '/');
						if(fim==NULL)
							fim=strchr((p+1), '\0');
						//pega o tamanho de tudo contigo entre as aspas
						tamanho = fim - p+1;
						//joga em req
						strncpy(req, (p), (tamanho));
						req[tamanho-1] = '\0';
						pushArvore(req, profundidade);
						//procura no restante do buffer
						b=fim;
					}else
						b=NULL;

					}
			}else{
				profundidade=0;
	
				while(b!=NULL){

					//procura pelo href
					p=strchr(b, '/');
					//se achou, continua
					if(p!=NULL){						
						profundidade++;
						//ai procura ate achar a proxima barra ou fim
						fim=strchr((p+1), '/');
						if(fim==NULL)
							fim=strchr((p+1), '\0');
						//pega o tamanho de tudo contigo entre as aspas
						tamanho = fim - p+1;
						//joga em req
						strncpy(req, (p), (tamanho));
						req[tamanho-1] = '\0';
						pushArvore(req, profundidade);
						//procura no restante do buffer
						b=fim;
					}else
						b=NULL;

				}
			}
		}



	return 0;
}



void pushArvore (char * modulo, int profundidade){
	int n = 0;	
	int i = 0;
	int j = 0;
	int status;
	struct Spider *aux = spider;
	struct Spider *pai = spider;

	//vai naquele nível de profundidade e procura pelo parça
	while(n<profundidade){
		pai = aux; 
		//primeiro ver se o filho existe
		if(pai->filho[0]!=NULL){
			aux = pai->filho[0];
		}
		n=n+1;
	}


	//o nivel 0 sempre existe. Bora ver se já tem filho
	//se nao tiver filho, o filho zero é NULL
	if(pai->filho[0]==NULL){
		//aloca memória
		aux = (struct Spider*) malloc (sizeof(struct Spider));
		//não esquecer de novo do que era mais importante que é guardar a string no novo nó		
		strcpy(aux->modulo, modulo);
		//faz o pai apontar pra esse primogênito (apontar com carinho)
		pai->filho[0] = aux;
		
	//agora o caso de já ter pelo menos um filho nesse nível	
	}else{
		i=0;
		aux=pai->filho[0];
		//se o nível não tá vazio, tem que ver se já foi escrito
		while(aux->modulo!=NULL){
			if(strcmp(aux->modulo, modulo)!=0)
				status = 1;
			i++;
			aux=pai->filho[i];
		}

		//se não achou já escrito
		if(status==1){
			aux = (struct Spider*) malloc (sizeof(struct Spider));
			strcpy(aux->modulo, modulo);
			pai->filho[i]=aux;

		}
	}
			

}

void imprimeSpider(){
	int i;
	int j;
	struct Spider *aux = spider;
	
	i=0;j=0;
	
	while(aux!=NULL){
			while(aux->filho[j]->modulo!=NULL){
				printf("%d\t%s\n", i,aux->filho[j]->modulo);
				j=j+1;
			}
			j=0;i=i+1;
			aux=aux->filho[0];
			
		
	}

}
