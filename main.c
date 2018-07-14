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
#include "snoopy.h"
#include "snoopy_dump.h"

int print_options(void);


/*! \brief main funcao principal que mostra as opcoes do projeto
 *
 * Chama a funcao print_options para mostrar as opcoes do projeto
 */
int main(int argc, char const *argv[])
{
	int conexao_cliente;
	int contador_requisicao = 0, n;
	int flag_dump;
	int comparacao, servidor_conectado;


	//Pegando porta pela linha de comando caso o usuario tenha escrito
	if (argc < 3)
	{
		PORTA = PORTA_PADRAO;
	}
	else
	{
		PORTA = atoi(argv[2]);
	}

	print_options();


	return 0;
}


/*! \brief print_options funcao que coordena a execucao de cada funcionalidade do projeto
 *
 * Chama a funcao correspondente de cada funcionalidade, de acordo com a opcao escolhida
 */
int print_options(void)
{
	int option = 0;
	char *reply=NULL;


	printf("###########################################\n");
	printf("\tSELECIONE A OPCAO DESEJADA:\n\n");
	printf("\t1- Proxy\n");
	printf("\t2- Inspeção\n");
	printf("\t3- Spider\n");
	printf("\t4- Dump\n");
	printf("###########################################\n\n");	

	scanf("%d", &option);

	switch (option)
	{
		case PROXY:
			printf ("[PROXY] Iniciando servidor proxy SNOOPY\n");
		    printf ("[PROXY] Endereço do SNOOPY http://%s:%d/\n", IP_PADRAO, PORTA);
			proxy(1, PROXY, 1);
			break;
		case INSPECAO:
			printf ("[INSPECTOR] Iniciando inspector SNOOPY\n");
		    printf ("[INSPECTOR] Endereço do SNOOPY http://%s:%d/\n", IP_PADRAO, PORTA);
			proxy(1, INSPECAO, 1);
			break;
		case SPIDER:
			reply=proxy(0, SPIDER, 1);
			procuraPath(reply);
			imprimeSpider();
			break;
		case DUMP:
			dump();
			break;
		default:
			printf("Opção inválida\n");
	}

	return option;
}
