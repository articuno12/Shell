#include "c_initialise.h"
#include "main.h"
#include "commands.h"
//this array will store name of the builtin commands which the shell can run
char *builtin[] = {
  "cd",
  "echo",
  "pwd",
  "pinfo",
  "exit",
  "listjobs",
  "sendsig",
  "fg",
  "killallbg"
};
//this array will store function addresses
int (*builtin_func[]) (char **) = {
  &c_cd,
  &c_echo,
  &c_pwd,
  &c_pinfo,
  &c_exit,
  &list_jobs,
  &sendsig,
  &fg,
  &killall
};
//calculating number of builtin functions
int no_of_builtins()
{
  return (sizeof(builtin)/(sizeof(char *)));
}

void handler(int sig)
{
    // printf("something has ended\n") ;
		pid_t pid;
		pid = wait(NULL);
		if (pid==-1) return ;
		printf("Pid %d : exited.\n", pid);
    delete_pid(pid) ;
    printinfo();
    fflush(stdout) ;
}
int process_command(char **args)
{
		// this function executes processes
		pid_t pid;
		int status,w,i,j=0,t;
		char error[100];
		int last=0,bg=0 ;
		while(args[last]!=NULL) last++ ;

		if(strcmp(args[last-1],"&")==0)
		{
				bg=1 ;
				args[last-1]=NULL ;
		}
		//fork process
		pid=fork();
		//checking if the process is child process or parent process
		if(pid==0)
		{

				char path[50];
				strcpy(path,"/bin/bash");
				int r=execvp(*args,args);
				//if execvp returns an error
				if(r==-1)
				{
						perror("Process cant b run");
						exit(1);
				}

		}
		else if(pid<0)
		{
				perror("fork returned an error");
				exit(1);
		}
		else if(pid>0)
		{
				//if not background process
				//parent process will wait till child process will exit either normally or by a signal
				if(!bg)
				{
						do {
								w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
								if (w == -1) { perror("waitpid"); exit(EXIT_FAILURE); }
								if (WIFEXITED(status) && status!=0) {
										printf("exited, status=%d\n", WEXITSTATUS(status));
								} else if (WIFSIGNALED(status)) {
										printf("killed by signal %d\n", WTERMSIG(status));
								} else if (WIFSTOPPED(status)) {
										printf("stopped by signal %d\n", WSTOPSIG(status));
								} else if (WIFCONTINUED(status)) {
										printf("continued\n");
								}
						} while (!WIFEXITED(status) && !WIFSIGNALED(status));
				}
        else
        {
          add_pid(pid) ;
          printf("%s %d %lld\n","adding pid ",pid,head_PidList->pid);
        }
		}
		return 1;
}
int execute_command(char** args)
{
		//checking if an argument is passed or not
		if(args[0]==NULL) return 0;
		else
		{
				int i;
				for(i=0;i<no_of_builtins();++i)

				{
						//if the argument is a builtin command then call the function corresponding to that command
						if(strcmp(args[0],builtin[i])==0) return (*builtin_func[i])(args);
				}
				//if argument not a builtin command then it can be a process
				return process_command(args);
		}
}
