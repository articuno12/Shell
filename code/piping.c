#include "c_initialise.h"
#include "main.h"
#include "commands.h"
int piping(char **args)
{
    if(args[0]==NULL) return 0;
		int file_odd[2],file_even[2];
    int last_flag=0;
		int i=0,j=0,k=0,end=0,num_cmd=0,p,c=1,it,option=0,pi,l,redirection;
		pid_t pid;
		char **command = (char**)malloc(buf_len * sizeof(char*));
		//num_cmd will store number of commands to be executed
		while(args[i]!=NULL)
		{
				if(strcmp(args[i],"|")==0) num_cmd++;
				i++;
		}
		num_cmd++,i=0;
    int stdin_copy = dup(0);

		while(args[j]!=NULL && end==0)
		{
       //printf("%s\n","loop is runnig" );
				k=0;
				while(strcmp(args[j],"|")!=0)
				{
            command[k] = (char*)malloc(sizeof(char)*(strlen(args[j])+2)) ;
						strcpy(command[k],args[j]);
        //    printf("command is %s\n",command[k]) ;
            j++;
            k++;
						if(args[j]==NULL)
            {
              end=1;j--;break;
            }
				}
				command[k]=NULL;
        //printf("%d\n",end);
				//now for next iteration ,take command after "|",so skip null/"|" and go to next index
				j++;
				//we will pipe depending whether we are in odd iteration or even.
				//in this way file descriptors can be shared among different iterations
				if(i%2==0) p=pipe(file_even);
        else p=pipe(file_odd);
				if(p==-1) { perror("Pipe failed"); return(0);}
				pid=fork();
				if(pid==-1)
				{
						// if this is not the last command to be executed
						if(i!=(num_cmd-1))
						{
								//close the corresponding output file descriptors as fork failed
								if(i%2==0) close(file_even[1]); else close(file_odd[1]);
						}
						perror("Cant create child process");
						return 0;
				}
				if(pid==0)
				{

						// If we are in the first command
						if (i == 0) {dup2(file_even[1], STDOUT_FILENO);close(file_even[1]);}
						// if it is last command then depending on whether it is placed at
						//even number or odd ,corresponding filedescriptor will be duplicated for stdout
						else if(i==(num_cmd-1))
						{
								if(num_cmd % 2==0){ dup2(file_even[0],STDIN_FILENO); close(file_even[0]);}
								else { dup2(file_odd[0],STDIN_FILENO);close(file_odd[0]);}
                //freopen ("/dev/tty", "a", stdout);
                last_flag=1;
						}
						else
						{
								if(i%2==0)
								{
										dup2(file_odd[0],STDIN_FILENO);
										dup2(file_even[1],STDOUT_FILENO);
                    close(file_even[1]);
    								close(file_odd[0]);
								}
								else
								{
										dup2(file_even[0],STDIN_FILENO);
										dup2(file_odd[1],STDOUT_FILENO);
                    close(file_even[0]);
                    close(file_odd[1]);
								}
						}

            c=check(command,1,last_flag);
            exit(0);
				}
				// in parent process , close corresponding file descriptors
        else if(pid > 0)
        {
        waitpid(pid,NULL,0);

        if(i==0) close(file_even[1]);
				else if(i==(num_cmd-1))
				{

						if(num_cmd&1) close(file_odd[0]);
						else close(file_even[0]);
          //  dup2(0,stdin_copy);
        }
				else
				{
						if(i%2==0)
						{
								close(file_even[1]);
								close(file_odd[0]);
						}
						else
						{
								close(file_even[0]);
								close(file_odd[1]);
						}
				}

    }
    i++;
		}
  //  printf("%d\n",c);
    return c;
}
