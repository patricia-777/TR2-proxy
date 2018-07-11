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




void criandoFile(char *nome_arquivo)
{
	// criando a variável ponteiro para o arquivo
	FILE *pont_arq;


	pont_arq = fopen(nome_arquivo, "a");

	if (pont_arq != NULL)
	{
		printf("O arquivo %s foi  criado", nome_arquivo);	
	}

	fclose(pont_arq);

}


void criandoDiretorioDump(char *diretorio)
{
	struct stat st={0};

	if (stat(diretorio, &st) == -1)
	{
		mkdir(diretorio, 0700);
	}

}

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

	// printf("NOME PASTA -->>%s\n", requisicao);
	//passa o valor do diretorio para outra variavel
	sprintf(buffer_aux,"%s",requisicao);


	// "/pasta/index.html"
	// "index.html"
	
	aux = strtok(requisicao, "/");
	while(!flag_fim)
	{
		//se for igual retorna 0
		comparacao = strcmp(buffer_aux, "(null)");
		if (!comparacao)
		{
			strcat(nome_arquivo, nome_pasta);
			strcat(nome_arquivo, "index.html");
			
			criandoFile(nome_arquivo);

			flag_fim = 1;
			//cria arquivoooo
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
				criandoFile(buffer_aux);
				//criar arquivo de nome buffer_aux
				flag_fim = 0;
			}

		}

	}
}



void baixando_arquivo()
{
	char *ponteiro_reply = NULL;

	ponteiro_reply = proxy(0, DUMP, 1);

	printf("DUMP---->>%s\n", ponteiro_reply);
}







void dumpOption(char *host, char *requisicao)
{
	// char buffer_requisicao[TAM_BUFFER];

	// nomeArquivoNomeDiretorio(buffer_requisicao, host, requisicao);
	// printf("HOST-->%s\nARQUIVO-->%s\nDIRETORIO-->%s\n", host, nome_arquivo, diretorio);

	//criando diretorios
	nomeArquivoNomeDiretorio(host, requisicao);

	
}


// void salvandoArquivos(char *nome_diretorio, char *porta, char *nome_arquivo)
// {
// 	CURL *curl_handle;
// 	FILE *pagefile;
// 	static const char *pagefilename;



// 	//concatenar strings para salvar arquivos nas respectivas pastas
// 	strcat(nome_diretorio, nome_arquivo);

// 	//abrindo arquivos
// 	sprintf(pagefilename,"%s",nome_arquivo);
	

// 	curl_global_init(CURL_GLOBAL_ALL);

// 	/* init the curl session */ 
// 	curl_handle = curl_easy_init();

// 	/* set URL to get here */ 
// 	curl_easy_setopt(curl_handle, CURLOPT_URL, host);

// 	/* Switch on full protocol/debug output while testing */ 
// 	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

// 	 disable progress meter, set to 0L to enable and disable debug output  
// 	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

// 	/* send all data to this function  */ 
// 	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

// 	/* open the file */ 
// 	pagefile = fopen(pagefilename, "wb");
// 	if(pagefile) 
// 	{

// 		/* write the page body to this file handle */ 
// 		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

// 		/* get it! */ 
// 		curl_easy_perform(curl_handle);

// 		/* close the header file */ 
// 		fclose(pagefile);
// 	}

// 	/* cleanup curl stuff */ 
// 	curl_easy_cleanup(curl_handle);

// 	curl_global_cleanup();
// }



// void nomeArquivoNomeDiretorio(char *buffer_requisicao, char *host, char *nome_arquivo, char *diretorio)
// {
// 	char *aux = NULL, *aux_req = NULL;
// 	char aux_concat[TAM_BUFFER];
// 	char dados_lixo[TAM_BUFFER];
// 	char requisicao[TAM_BUFFER];

// 	//pegando a parte GET do cabeçalho da requisição
// 	//dividido em GET http://site HTTP
// 	aux = strtok(buffer_requisicao,"\n");
// 	sscanf(aux,"%s %s", dados_lixo, requisicao);

// 	//pegando atributo host do cabeçalho
// 	//no formato Host: site.com.br
// 	aux = strtok(NULL,"\n");
// 	sscanf(aux,"%s %s", dados_lixo, host);



// 	//pegando a parte de requisição e isolando somenete o diretorio que foi pedido
// 	//http://site.com.br/diretorio.html
// 	aux_req = strtok(requisicao, "/");
// 	aux_req = strtok(NULL, "/");

// 	//pegando a raiz do diretorio
// 	sprintf(diretorio,"%s",aux_req);

// 	//pegando o diretorio
// 	aux_req = strtok(NULL, "/");

// 	//passa o resultado para o nome do arquivo
// 	sprintf(nome_arquivo,"%s",aux_req);

// 	//verifica se tem mais de um diretorio na requisição
// 	//pega outros diretorios da requisição e concatena com o primeiro
// 	aux_req = strtok(NULL, "/");
// 	while (aux_req != NULL)
// 	{
// 		//concatena com a /
// 		strcat(diretorio, "/");
// 		strcat(diretorio, nome_arquivo);
// 		// strcat(requisicao, "/");
		
		
// 		sprintf(nome_arquivo,"%s",aux_req);

		
// 		// strcat(requisicao, aux_concat);
		
		
// 		aux_req = strtok(NULL, "/");
// 	}
// }