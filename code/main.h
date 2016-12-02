void handler(int sig);
int process_command(char **args);
int execute_command(char** args);
int piping(char** args);
int redirect(char **args,char * file_i,char *file_o,int option,int pipe,int end);
int check(char  **args,int pipe,int end);
#define TOK_DELIM " "
#define TOK_BUFFER 1024
char **parse_line(char *line);
char * readline(void);
