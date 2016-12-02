#include "c_initialise.h"
#include "commands.h"
int c_cd(char **args)
{
  char error[100],temp[2000],temp2[2000];int c;
  if(args[1]==NULL )
  {

    c=chdir(home_dir());
  }
  else if(args[1]!=NULL)
  {
    strcpy(temp,args[1]);
    if(temp[0]=='~')
    {
      strcpy(temp2,"~");
      strcat(temp2,temp+1);
      strcpy(temp,temp2);
    }
    c=chdir(temp);
  }
  if(c!=0)
    {
      perror("Error!Invalid argument\n");

      exit(1);
    }
  return 1;
}
