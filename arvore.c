#include "arvore.h"



int main ()
{
  char str[] = "This is a sample string sams href=\"lala/dodododo/mimi/forofa\"  src=\"lala/mmmmmmm/mimi/fafa\"ple\nsamplehref=\"lala/kkkkkkk/mimi/alface\"";
  char pch[] = "www.ba.gov.br";
	int i=0;
  	
	strcpy(host, pch);

  	spider = (struct Spider*) malloc (sizeof(struct Spider));
 	strcpy(spider->modulo, host);
 	/*while(i<30){
		spider->filho[i]=NULL;
		i++;
	}*/

  	procuraPath(str, pch);
	imprimeSpider();

  return 0;
}

void procuraPath (char *buffer, char *path){
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













