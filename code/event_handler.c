#include "c_initialise.h"

void sigintHandler(int sig_num)
{
    signal(SIGINT, sigintHandler);
}
