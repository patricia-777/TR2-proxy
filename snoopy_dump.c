/*
*
*	SNOOPY
*
*	Laís Mendes & Helena
*
*	TR2 1/2018
*
*/


#include "snoopy_dump.h"
#include "snoopy.h"


/*!\brief dump funcao do dump que baixa o arquivo pedido de acordo com a url
*
* Essa funcao chama a funcao baixando_arquivo, para começar o processo de salvar o arquivo na pasta local
*/
void dump()
{
	bzero((char*)buffer_requisicao, TAM_BUFFER);
	
	sprintf(buffer_requisicao,"%s","GET http://www.saopaulo.sp.gov.br/ HTTP/1.1\nHost: www.saopaulo.sp.gov.br");

	baixando_arquivo(0);
}

/*!\brief criandoFile funcao do dump que cria o arquivo a ser baixado
*
* Essa funcao cria o arquivo de acordo com o nome e extensao passados, e grava o conteudo tambem passado
*/
void criandoFile(char *nome_arquivo, char *info_arq)
{
	// criando a variavel ponteiro para o arquivo
	FILE *pont_arq;

	pont_arq = fopen(nome_arquivo, "a");

	if (pont_arq != NULL)
	{
		//usando fprintf para armazenar a string no arquivo
		fprintf(pont_arq, "%s", info_arq);	

		printf("O arquivo %s foi  criado\n", nome_arquivo);
	}

	fclose(pont_arq);
}

/*!\brief baixando_arquivo recebe o conteudo da resposta e começa o porcesso de salva-lo em um arquivo
*
* Essa funcao chama a funcao criar_arquivo_ext para selecionar o tipo de arquivo que devera ser "baixado"
*/
void baixando_arquivo(int primeira_requisicao)
{
	char * pch, *vetor;
	char *ponteiro_reply = NULL;
	int index;
	char *info_gravar;

	ponteiro_reply = proxy(0, DUMP, primeira_requisicao);

	printf("\n");

	criar_arquivo_ext(ponteiro_reply, ponteiro_reply);

}

/*!\brief criar_arquivo_ext gerencia a criacao do arquivo de acordo com a sua extensão
*
* Essa funcao "separa" o cabeçalho HTTP da resposta em si, e chama a funcao para gerar o arquivo de acordo com a sua extensao
*/
void criar_arquivo_ext(char *reply, char *reply_novo)
{
	int index;
	char *pch, *vetor;
	char *info_gravar;
	char *aux = NULL;
	char *buffer_ext[TAM_BUFFER];


	aux = (char*)malloc((strlen(reply))*sizeof(char));
	sprintf(aux,"%s",reply);

	pch = strstr (reply,"Content-Type:");
	index = pch-reply;
	vetor = &(reply[index]);

	pch = strtok(vetor, ": ");
	pch = strtok(NULL, ": ");

	sprintf(*buffer_ext,"%s",pch);


	if (strstr (*buffer_ext,"html"))
	{
		pch = strstr (aux,"<!DOCTYPE");
		index = pch-aux;
		info_gravar = &(aux[index]);

		criandoFile("index.html", info_gravar);
	}
	else if (strstr (*buffer_ext,"png"))
	{
		pch = strstr (aux,"PNG");
		index = pch-aux-1;
		info_gravar = &(aux[index]);

		criandoFile("index.png", info_gravar);
	}
	else if (strstr (*buffer_ext,"jpg"))
	{
		criandoFile("index.jpg", reply);
	}
	else if (strstr (*buffer_ext,"jpeg"))
	{
		criandoFile("index.jpeg", reply);
	}
	else if (strstr (*buffer_ext,"css"))
	{
		criandoFile("index.css", reply);
	}
	else
	{
		printf("Arquivo não suportado!\n");
	}
}



/*!\brief criandoDiretorioDump cria o diretorio que foi passado por parametro
*
* Essa funcao cria as pastas do site em questão, simulando a estrutura do site
*/
void criandoDiretorioDump(char *diretorio)
{
	struct stat st={0};

	if (stat(diretorio, &st) == -1)
	{
		mkdir(diretorio, 0700);
	}

}


/*!\brief nomeArquivoNomeDiretorio separa a requisicao em diretorios e os cria
*
* Essa funcao identifica os diretórios do site de acordo com as urls, e chama a funcao 
* criandoDiretorioDump para cria-los.
*/
void nomeArquivoNomeDiretorio(char *host, char *requisicao)
{

	char NPasta[100], Comd[150]; 
	char nome_pasta[TAM_BUFFER], nome_arquivo[TAM_BUFFER], buffer_aux[TAM_BUFFER];
	char *aux = NULL, *aux2 = NULL;
	int comparacao, flag_fim = 0;


	//criando diretorio principal
	strcpy(nome_pasta,"/Users/patriciagoncalves/Documents/UNB/tr2_repo/dump/");
	strcat(nome_pasta, host);
	strcat(nome_pasta, "/");

	criandoDiretorioDump(nome_pasta);

	sprintf(buffer_aux,"%s",requisicao);

	
	aux = strtok(requisicao, "/");
	while(!flag_fim)
	{
		//se for igual retorna 0
		comparacao = strcmp(buffer_aux, "(null)");
		if (!comparacao)
		{
			strcat(nome_arquivo, nome_pasta);
			strcat(nome_arquivo, "index.html");
			
			// criandoFile(nome_arquivo);

			flag_fim = 1;

		}
		else
		{
			//null se nao tiver um . na palavra
			if (!strstr(buffer_aux, "."))
			{
				strcat(nome_pasta, aux);
				strcat(nome_pasta, "/");

				criandoDiretorioDump(nome_pasta);

				aux = strtok(NULL, "/");

				sprintf(buffer_aux,"%s",aux);

				flag_fim = 0;
			}
			else
			{
				// criandoFile(buffer_aux);
				flag_fim = 0;
			}

		}

	}
}
