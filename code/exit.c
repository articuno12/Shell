#include "c_initialise.h"
//implementing exit command
int c_exit(char **args)
{
  empty_process_queue() ;
  return 0;
}
