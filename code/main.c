
#include "c_initialise.h"
#include "main.h"
int main()
{
  initialise();
  signal(SIGINT, sigintHandler);
  signal(SIGCHLD, handler);
  signal(SIGTSTP,sigintHandler_Z) ;
  int status=1;
  char *line;
  char **args;
  while(status==1)
  {
    printinfo();
    line=readline();
    args=parse_line(line);

    status = check(args,0,0);
    //printf("status%d\n",25 );
    // printf("pis ma%d\n",head_PidList->pid );
    free(line);
    free(args);
  }
  return 0;
}
