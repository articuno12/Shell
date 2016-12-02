// implementing pwd
#include "c_initialise.h"
int c_pwd(char** args)
{
  char *path=(char*) malloc(buf_len);
  getcwd(path,buf_len);
  if(path==NULL)
  {
    
    perror("Error in accessing present directory directory\n");

    exit(1);
  }
  printf("%s\n",path );
  return 1 ;
}
