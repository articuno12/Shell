#include "c_initialise.h"

int c_echo(char **args)
{
  int i=1;
  //while there are arguments,print them.
  while(args[i]!=NULL)
  {
    printf("%s ",args[i]);
    i++;
  }
  printf("\n");
  return 1;
}
