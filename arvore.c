#include <stdio.h>
#include <string.h>

void procuraPath (char *buffer, char *path){

int main ()
{
  char str[] = "This is a sample string sample\nsample";
  char * pch;
 /* printf ("Looking for the string in \"%s\"...\n",str);
  pch = strstr (str,"sample");
  puts(str);
  while (pch!=NULL)
  {
    printf ("found at %d\n",pch-str+1);
    pch = strstr (pch+1,"sample");
  }*/

	


  return 0;
}

void procuraPath (char *buffer, char *path){
	char *href = "href=";
	char *src = "src=";

	//busca por href:
	while(buffer!=NULL){
		path = strstr(buffer, href);		
		pegaPath(p);
		buffer = buffer-path;
		puts(path)
	}

}
