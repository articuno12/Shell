#include "c_initialise.h"
#include "commands.h"
int c_pinfo(char **args)
{
		char path[buf_len],p_status[buf_len],cmdline[buf_len];
		char buffer[100],pid[50];
		if(args[1]==NULL) return 0;
		strcat(path,pid) ;
		//path is the absolute path the /proc/<pid>/ , required to read the necessary files
		strcpy(pid,args[1]) ;
		strcpy(path,"/proc/") ;
		strcat(path,pid);
		printf("PID : %s\n",pid) ; //printing the PID(process ID)
		//opening status files
		strcpy(p_status,path) ; strcat(p_status,"/status") ;
		FILE *status = fopen(p_status,"r") ;
		if(status == NULL)
		{
				perror("Check if the entered PID is correct\n") ;
				return 1 ;
		}
		// for status and virtual memory
		// status and vm corresponding to a process is stored in /proc/pid/status
		while(!feof(status))
		{
				fscanf(status,"%[^\n]\n",buffer) ;
				if(strstr(buffer,"State")!=NULL ||strstr(buffer,"VmSize")!=NULL)
						printf("%s\n",buffer) ;
		}
		//to print the execution path
		//the execution path is stored in /proc/<pid>/cmdline
		strcpy(cmdline,path) ;
		strcat(cmdline,"/cmdline") ;
		FILE *Cmdline=fopen(cmdline,"r") ;
		if(Cmdline == NULL)
		{
				perror("Check if the entered PID is correct\n") ;
				return 1 ;
		}
		printf("Execution Path : ") ;
		while(!feof(Cmdline))
		{
				fgets(buffer,50,(FILE*)Cmdline) ;
				printf("%s",buffer);
		}
		printf("\n") ;
		return 1 ;

}
