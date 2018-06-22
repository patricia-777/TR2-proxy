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
	char host[TAM_BUFFER];
	char http[TAM_BUFFER];
	char requisicao[TAM_BUFFER];
	int contador_requisicao = 0;
	int comparacao;
	//pid_t usado para pegar a referencia do processo filho, depois do fork
	pid_t pid;

	printf ("[PROXY] Iniciando servidor proxy SNOOPY\n");
    printf ("[PROXY] Endereço do SNOOPY http://localhost:%d/\n", PORTA_PADRAO);
    printf ("[PROXY] Esperando requisiçoes...\n");
    // printf ("[PROXY] %d requisições\n", contador_requisicao);

    //criando o socket do proxy
    proxy_socket = inicioSocketProxy(PORTA_PADRAO);

    while(1)
    {
		//requisicoes vindas do navegador
        conexao_cliente = esperandoRequisicao (proxy_socket);


        //a funcao fork cria uma thread filho rodando as mesmas coisas a partir daqui
		pid=fork();
		//se a thread for o filho entao entra nesse if
		if(pid==0)
		{

	        //essa funcao le o que esta no socket, e retorna o tamanho da mensagem ou -1 se tiver erro
	        bzero((char*)buffer_requisicao, TAM_BUFFER);
	        tam_requisicao = recv (conexao_cliente, buffer_requisicao, TAM_BUFFER, 0);
	        if (tam_requisicao < 0) 
	        {
	            errx (EXIT_FAILURE, "Erro ao ler a requisição");
	        }


            //tratando da requisição
    		//separando as informacoes de host, pasta, e http
	        camposRequisicao(buffer_requisicao, host, requisicao, http);

	        //se a requisição for http entao entra no if e faz a conexao
	    	comparacao = strncmp(http, "HTTP/", 5);
	        if (!comparacao)
	        {
		        ////mostrando a requisiçãoelo cliente 
		        printf ("[REQUEST] Requisição recebida: %s\n", buffer_requisicao);
		        printf ("[REQUEST] Enviando resposta...\n\n");

		        //fazendo a conexao e enviando o resultado para o usuario
		        serveText (conexao_cliente, host, requisicao, http);


		        printf ("\n[REQUEST] Resposta enviada\n");
		        printf ("[REQUEST] Conexão fechada\n");

		        ++contador_requisicao;
	        }
	        //se a conexao nao for http, uma mensagem é enviada para o usuario
    		else
			{
				send(conexao_cliente,"ERROR : SORRY DUDE!\nAPENAS CONEXÕES HTTP SÃO PERMITIDAS",60,0);
			} 
	        	
	        // printf ("[SERVER] Served %d requests\n", contador_requisicao);
	        close(proxy_socket);
	        _exit(0);
	    }
	    //se nao for filho, a conexao com o cliente é fechada
	    else
	    {
	    	close(conexao_cliente);
	    }     
    }

	return 0;
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

void serveText (int conexao_cliente, char *host, char *requisicao, char *http) 
{
    struct sockaddr_in ext_addr;
    int requisito_socket, requisicao_conexao, n;
    char buffer[TAM_BUFFER];

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

    //mandando header para o servidor externo
    n = sendTextHeader (requisito_socket, requisicao, host, http);


    //lendo a resposta do servidor externo e enviando de volta para o cliente
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
	            send(conexao_cliente,buffer,n,0);
	        }
	        // else
	        // {
	        // 	printf("Erro recv -->%s\n", strerror(errno));
	        // }
	    } while(n>0);
	}

	//fecha as conexoes com o servidor externo e a conexao do cliente com o proxy
	//desse filho
	close(requisito_socket);
	close(conexao_cliente);
}


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

    //faz o bind no socket do proxy com endereço e porta que ele vai funcionar
    bind_status = bind (proxy_socket, (struct sockaddr *)&proxy_addr, sizeof (proxy_addr));
    if (bind_status < 0) 
    {
        errx (EXIT_FAILURE, "Erro no bind da porta do proxy");
    }

    return proxy_socket;
}
