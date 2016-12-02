#include "c_initialise.h"
//global variable storing home directory path
char *home;
char * setting_home()
{

		//getting present directory
		char *home=(char*) malloc(buf_len);
		char *p=(char*) malloc(buf_len);
		getcwd(p,buf_len);
		if(p==NULL)
		{
				char error[100];
				perror("Error in accessing present directory directory\n");

				exit(1);
		}
		return p;
}
//this will run when main file will be run , home will store the path of the directory in which the script is being run
int initialise()
{
		home=setting_home();
		head_PidList=NULL ;
		Avail_Job=1 ;
		// printf("%s\n","i was here init" );
		return 1;
}
//function to return value of home
char * home_dir(void)
{

		return home;
}
//function to get the username and hostname and store them in a string
char* getname()
{
		char hostname[buf_len],username[buf_len];
		char *name=(char*) malloc(buf_len);
		strcpy(name,"<");
		int check;
		check=gethostname(hostname,buf_len);
		if(check!=0)
		{
				fprintf(stderr, "cant get hostname\n");
				exit(EXIT_FAILURE);
		}
		check=getlogin_r(username,buf_len);
		if(check!=0)
		{
				fprintf(stderr, "cant get username\n");
				exit(EXIT_FAILURE);
		}
		strcat(name,username);
		strcat(name,"@");
		strcat(name,hostname);
		strcat(name,":");
		return name;
}
//function to get the present directory path in the way it has to be displayed
char* current_directory()
{
		char *path=(char*) malloc(buf_len);
		char temp[buf_len];
		getcwd(path,buf_len);
		if(path==NULL)
		{
				char error[100];
				perror("Error in accessing present directory\n");

				exit(1);
		}
		//c will store the pointer to the first occurence of home directory path in getcwd result
		char* c=strstr(path,home_dir());
		int len=strlen(home_dir());
		if(c!=NULL)
		{
				strcpy(temp,"~");
				strcat(temp,path+len);
				strcpy(path,temp);
		}
		return path;
}

void printinfo()
{
		char *name=(char*) malloc(buf_len);
		char *path=(char*) malloc(buf_len);
		name=getname();
		path=current_directory();
		strcat(name,path);
		strcat(name,">");
		printf("%s",name);
		fflush(stdout);
}
