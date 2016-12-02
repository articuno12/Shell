#include "main.h"
#include "c_initialise.h"
char * readline(void)
{
		char *line=NULL;
		ssize_t bufsize = 0;
		//reading input thru getdelim function,setting delimiter character to ";"
		getdelim(&line, &bufsize,';', stdin);
		//eliminating delimiter character from string line
		int length =strlen(line);
		if(feof(stdin))
    {
        printf("The shell is exiting.With love <3 :)\n") ;
        exit(0) ;
    }

		line[length-1]='\0';
		int i;
		for(i=0;i<length;++i)
		{
			if(line[i]!='\n' && line[i]!=' ') break;
		}
		strcpy(line,line + i);
		return line;
}
