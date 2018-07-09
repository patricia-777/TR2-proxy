#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] = "This is a sample string sample";
  char * pch;
  printf ("Looking for the string in \"%s\"...\n",str);
  pch = strstr (str,"sample");
  while (pch!=NULL)
  {
    printf ("found at %d\n",pch-str+1);
    pch = strstr (pch+1,"sample");
  }
  return 0;
}