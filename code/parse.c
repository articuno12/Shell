#include "main.h"
#include "c_initialise.h"
char **parse_line(char *line)
{
		int buffer_size=TOK_BUFFER,index=0;
		char * token;
		char **tokens_backup;
		char **tokens = malloc(buffer_size * sizeof(char*));
		//if error in memory allocation
		if (!tokens) {
				perror("memory allocation error\n");
				exit(EXIT_FAILURE);
		}

		token = strtok(line,TOK_DELIM);
		while(token!=NULL)
		{
				tokens[index++]=token;
				if(index>=TOK_BUFFER)
				{
						tokens_backup=tokens;
						buffer_size+=TOK_BUFFER;
						tokens = realloc(tokens, buffer_size * sizeof(char*));
						if (!tokens) {
								free(tokens_backup);
								perror("memory allocation error\n");
								exit(EXIT_FAILURE);
						}
				}
				token = strtok(NULL,TOK_DELIM);
		}
		tokens[index]=NULL ;
	//		printf("index is %d\n",index) ;
		return tokens;
}
