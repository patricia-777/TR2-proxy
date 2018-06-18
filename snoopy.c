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

int main(int argc, char const *argv[])
{
	int proxy_socket, conexao_cliente, tam_requisicao;
	char buffer_requisicao[TAM_BUFFER];
	int contador_requisicao = 0;

	printf ("[PROXY] Iniciando servidor proxy SNOOPY\n");
    printf ("[PROXY] Endereço do SNOOPY http://localhost:%d/\n", PORTA_PADRAO);
    printf ("[PROXY] Esperando requisiçoes...\n");
    printf ("[PROXY] %d requisições\n", contador_requisicao);

    //criando o socket do proxy
    proxy_socket = inicioSocketProxy(PORTA_PADRAO);

    while(1)
    {
		//requisicoes vindas do navegador
        conexao_cliente = esperandoRequisicao (proxy_socket);

        //essa funcao le o que esta no socket, e retorna o tamanho da mensagem ou -1 se tiver erro
        bzero((char*)buffer_requisicao, TAM_BUFFER);
        tam_requisicao = recv (conexao_cliente, buffer_requisicao, TAM_BUFFER, 0);
<<<<<<< HEAD
	printf("BUFFEEERR->>%s",buffer_requisicao);
=======
>>>>>>> b82a256ad8af4453318fa315fc474b1a78625eac
        if (tam_requisicao < 0) 
        {
            errx (EXIT_FAILURE, "Erro ao ler a requisição");
        }

        ////mostrando a requisiçãoelo cliente 
        printf ("[REQUEST:%d] Requisição recebida: %s\n",contador_requisicao, buffer_requisicao);


        printf ("[REQUEST:%d] Enviando resposta:\n\n", contador_requisicao);
<<<<<<< HEAD
        //sendTextHeader(conexao_cliente);
        serveText (conexao_cliente, buffer_requisicao);

=======

        pedindoRequisicao (PORTA_PADRAO, buffer_requisicao);
>>>>>>> b82a256ad8af4453318fa315fc474b1a78625eac

        printf ("\n[REQUEST:%3d] Response sent\n", contador_requisicao);
        printf ("[REQUEST:%3d] Closing connection\n", contador_requisicao);

<<<<<<< HEAD
        close (conexao_cliente);
=======
        // close (conexao_cliente);
>>>>>>> b82a256ad8af4453318fa315fc474b1a78625eac
        ++contador_requisicao;
        printf ("[SERVER] Served %d requests\n", contador_requisicao);



    }

	
	return 0;
}


<<<<<<< HEAD

void sendTextHeader (int socket, char *buffer_requisicao) 
{
    char message[510];

    if(!buffer_requisicao)
    {
    	sprintf(message,"GET / HTTP/1.1\r\nHost: 10.0.2.15\r\nConnection: close\r\n\r\n");
    }
    else{
	sprintf(message,"GET /%s HTTP/1.1\r\nHost: 10.0.2.15\r\nConnection: close\r\n\r\n",buffer_requisicao);
    }

    send (socket, message, strlen (message), 0);
}

void serveText (int proxy_socket, char *buffer_requisicao) 
{
    struct sockaddr_in proxy_addr;
    int requisito_socket, bind_status, requisicao_conexao, n;
    char buffer[TAM_BUFFER], buffer_host[TAM_BUFFER], s1[TAM_BUFFER], get_parte[TAM_BUFFER], http_parte[TAM_BUFFER];
    char* temp=NULL;
=======
// habilitando o proxy a ouvir uma porta específica
void pedindoRequisicao (int porta, char *buffer_requisicao) 
{
	int requisito_socket, bind_status, requisicao_conexao;
	struct sockaddr_in host_addr;
	int n, tam_requisicao;
	char buffer[TAM_BUFFER], buffer_host[TAM_BUFFER], s1[TAM_BUFFER], get_parte[TAM_BUFFER], http_parte[TAM_BUFFER];
	char* temp=NULL;
	struct hostent* host;


	temp=strtok(buffer_requisicao,"\n");
	sscanf(temp,"%s %s %s",s1,get_parte, http_parte);
	// printf("PRIMEIRA PARTEEE -->>##%s##\n##%s##", get_parte, http_parte);
	temp=strtok(NULL,"\n");
	sscanf(temp,"%s %s",s1,buffer_host);

	host=gethostbyname(buffer_host);
	// printf("BUFFER -->>2222%s2222\n", buffer_host);
	if (!host)
	{
		printf("DEU ERRO NO DNS\n");
	}
>>>>>>> b82a256ad8af4453318fa315fc474b1a78625eac

    // criando socket e verificando se houve erro
    requisito_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (requisito_socket < 0) 
    {
        errx (EXIT_FAILURE, "Erro ao criar o socket do proxy");
    }

<<<<<<< HEAD

    temp=strtok(buffer_requisicao,"\n");
    sscanf(temp,"%s %s",s1,get_parte);
    
     temp=strtok(get_parte,"//");
     temp=strtok(NULL,"/");
     temp=strtok(NULL,"/");	
	printf("GET->>%s\n", temp);



    proxy_addr.sin_family = AF_INET;
    proxy_addr.sin_addr.s_addr = inet_addr("10.0.2.15");
    //proxy_addr.sin_addr.s_addr = INADDR_ANY;
    proxy_addr.sin_port = htons(8001);

    requisicao_conexao = connect(requisito_socket,(struct sockaddr*)&proxy_addr,sizeof(struct sockaddr));
=======
    // configuração para fazer o proxy ouvir na porta definida
    host_addr.sin_family = AF_INET;
    bzero((char*)&host_addr,sizeof(host_addr));
    host_addr.sin_port = htons(80);
    bcopy((char*)host->h_addr,(char*)&host_addr.sin_addr.s_addr,host->h_length);
    printf("AQUI4\n");

    requisicao_conexao = connect(requisito_socket,(struct sockaddr*)&host_addr,sizeof(struct sockaddr));
>>>>>>> b82a256ad8af4453318fa315fc474b1a78625eac
    if (requisicao_conexao < 0) 
    {
        errx (EXIT_FAILURE, "Erro de conexao ao servidor remoto");
    }

<<<<<<< HEAD
    sendTextHeader (requisito_socket, temp);

    do
    {
        bzero((char*)buffer,TAM_BUFFER);
        n=recv(requisito_socket,buffer,TAM_BUFFER,0);
	printf("ENVIAARR-->%s", buffer);
        if(!(n<=0))
        {
            send(proxy_socket,buffer,n,0);
        }
    }while(n>0);

}


=======
    temp=strtok(get_parte,"//");
    temp=strtok(NULL,"/");
    temp=strtok(NULL,"/");
    
    // sscanf(temp,"%s",get_parte);
    printf("CHEGEEEUU4\n");
    printf("PASTAS -->>2222%s2222\n", temp);
	n=sendTextHeader(requisito_socket, buffer_host, temp, http_parte);

	if(n<0)
	{
		errx (EXIT_FAILURE, "Error writing to socket");
	}
	else
	{
		printf("ENTREEEIII AQUIII\n");
		do
		{
			bzero((char*)buffer,TAM_BUFFER);
			n=recv(requisito_socket,buffer,TAM_BUFFER,0);
			// printf("BUUFFERRR CLIENTE-->>##%s##\n", buffer);
			if(!(n<=0))
			{
				printf("ENVIEI PARA O cliente\n");
				send(requisito_socket,buffer,n,0);
			}
		}while(n>0);
	}
}


int sendTextHeader (int socket, char *host, char *pastas, char *htt_parte)
{
    char message[1000];

	if (pastas)
	{
		sprintf(message,"GET /%s %s\r\nHost: %s\r\nConnection: close\r\n\r\n",pastas, htt_parte, host);
	}
	else
	{
		sprintf(message,"GET / %s\r\nHost: %s\r\nConnection: close\r\n\r\n",htt_parte, host);	
	}
    
    printf("MENSAGEM-->>%s\n", message);
    return send (socket, message, strlen (message), 0);
}



>>>>>>> b82a256ad8af4453318fa315fc474b1a78625eac
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
    proxy_addr.sin_addr.s_addr = INADDR_ANY;
    proxy_addr.sin_port = htons(porta);

    bind_status = bind (proxy_socket, (struct sockaddr *)&proxy_addr, sizeof (proxy_addr));
    if (bind_status < 0) 
    {
        errx (EXIT_FAILURE, "Erro no bind da porta do proxy");
    }

    return proxy_socket;
}
