#include "c_initialise.h"
#include "main.h"
#include "commands.h"

int redirect(char **args,char * file_i,char *file_o,int option,int pipe,int end)
{

		int fd,c=1,in,out;in=0;out=1;
		//for(c=0;args[c]!=NULL;++c) printf("the args is %s %d\n",args[c],c );
		pid_t pid;
		pid=fork();
		if(pid==-1)
		{
				perror("Fork failed");
				return 0 ;
		}
		//run command in child process
		else if(pid==0)
		{
				//input redirection
				int stdin_copy = dup(0);
				fd=open(file_i,O_RDONLY, 0600);
				in=dup2(fd,STDIN_FILENO);
				close(fd);
				//output redirection
				if(option==1)
				{
						//open(or create) file in write only mode,truncating it at 0
						fd=open(file_o,O_CREAT | O_TRUNC | O_WRONLY, 0600);
						out=dup2(fd,STDOUT_FILENO);
						close(fd);
				}
				//input or input and output redirection
				else if(option==0)
				{
						fd=open(file_o,O_CREAT | O_APPEND | O_WRONLY, 0600);
						out=dup2(fd,STDOUT_FILENO);
						close(fd);
				}
				c=execute_command(args);
			//	printf("child's c %d\n",c);
				if(pipe==0 || end==1)
				{
						freopen ("/dev/tty", "a", stdout);
						dup2(stdin_copy, 0);
				}
				//freopen ("/dev/stdout", "a", stdout);
				// printf("child c=%d\n",c);
				return c ;
		}
		//in parent process

		waitpid(pid,NULL,0);
		//printf("Parents c %d\n",c);
		//printf("reached till the end of this file\n") ;
		return 0;
}
