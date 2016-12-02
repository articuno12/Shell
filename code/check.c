#include "c_initialise.h"
#include "main.h"
#include "commands.h"
int check(char **args,int pipe,int end)
{
		//checking if an argument is passed or not
	//	printf("%s\n","i am inside check" );
		if(args[0]==NULL) return 1;
		int last=0,i,option=-1,k;
		while(args[last]!=NULL) last++ ;
		// if there is piping in command,call corresponding function
		for(i=0;i<last;++i) if(strcmp(args[i],"|")==0) { return piping(args); }
		//check for redirection
		char file1[buf_len],file2[buf_len];
		char **command = (char**) malloc(buf_len * sizeof(char*));
		strcpy(file1,"STDOUT_FILENO");
		strcpy(file2,"STDIN_FILENO");
		k=0; //denotes the kth command
		for(i=0;i<last;++i)
		{
        // printf("current arg is %s with i as %d \n",args[i],i );
				if((strcmp(file1,"STDOUT_FILENO")!=0 || strcmp(file2,"STDIN_FILENO")!=0) && i <last)
				{
						perror("Invalid input") ; return 1;
				}

				if(strcmp(args[i],">")==0||strcmp(args[i],">>")==0)
				{

						if(strcmp(args[i],">")==0)  option=1;
            else if (strcmp(args[i],">>")==0) option=0;

            if(args[++i]!=NULL )strcpy(file1,args[i]);
            else break;

						if(args[i+1]!=NULL)
						{
              if(strcmp(args[++i],"<")==0) strcpy(file2,args[++i]);
            }
						else break;
				}


				else if(strcmp(args[i],"<")==0)
				{
						strcpy(file2,args[++i]);
						if(args[i+1]!=NULL)
						{
								if(strcmp(args[++i],">")==0||strcmp(args[i],">>")==0)
								{
										if(strcmp(args[i],">")==0)option=1; else if (strcmp(args[i],">>")==0) option=0;
										strcpy(file1,args[++i]);
								}
						}

						else break;
				}
				else
        {
          command[k] = (char*)malloc(sizeof(char)*(strlen(args[i])+2)) ;
          strcpy(command[k++],args[i]);
        }

		}
		//  for (i=0;i<last;++i) printf("%s\n",command[i]);
		command[k]=NULL;
		    //printf("command array is set\n") ;
    return redirect(command,file2,file1,option,pipe,end);
}
