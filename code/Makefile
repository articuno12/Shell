main: main.o cd.o echo.o execute.o exit.o initialise_shell.o parse.o pinfo.o pwd.o readline.o redirection.o check.o piping.o listjobs.o linkedlist.o event_handler.o signal.o
	gcc -o main *.o
main.o:main.c main.h c_initialise.h
	gcc -c main.c main.h c_initialise.h
check.o:check.c main.h c_initialise.h commands.h
	gcc -c check.c c_initialise.h main.h commands.h
piping.o:piping.c main.h c_initialise.h commands.h
	gcc -c piping.c c_initialise.h main.h commands.h
redirection.o:redirection.c main.h c_initialise.h commands.h
	gcc -c redirection.c c_initialise.h main.h commands.h
execute.o:execute.c c_initialise.h main.h commands.h
	gcc -c execute.c c_initialise.h main.h commands.h
parse.o:parse.c main.h c_initialise.h
	gcc -c parse.c main.h c_initialise.h
readline.o:readline.c main.h c_initialise.h
	gcc -c readline.c main.h c_initialise.h
initialise_shell.o : initialise_shell.c c_initialise.h
	gcc -c initialise_shell.c c_initialise.h
signal.o:signals.c c_initialise.h commands.h
	gcc -c signals.c c_initialise.h commands.h
event_handler.o: event_handler.c c_initialise.h
	gcc -c event_handler.c c_initialise.h
listjobs.o:listjobs.c c_initialise.h main.h commands.h
	gcc -c listjobs.c c_initialise.h main.h commands.h
linkedlist.o:linkedlist.c c_initialise.h
	gcc -c linkedlist.c c_initialise.h
cd.o :cd.c c_initialise.h commands.h
	gcc -c cd.c c_initialise.h commands.h
echo.o:echo.c c_initialise.h commands.h
	gcc -c echo.c c_initialise.h commands.h
exit.o:exit.c c_initialise.h commands.h
	gcc -c exit.c c_initialise.h commands.h
pinfo.o:pinfo.c c_initialise.h commands.h
	gcc -c pinfo.c c_initialise.h commands.h
pwd.o:pwd.c	c_initialise.h commands.h
	gcc -c pwd.c c_initialise.h commands.h

	.PHONY: clean

	clean:
		rm -f *.o
