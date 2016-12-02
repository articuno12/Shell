#include "c_initialise.h"
#include "commands.h"
ll To_Int(char S[])
{
    ll ans=0 ;
    int len = strlen(S),i ;
    for(i=0;i<len;++i) ans = (ans*10 + S[i]-'0') ;
    return ans ;
}
ll get_pid_from_job(ll nu)
{
    node *cur =head_PidList ;
    while(cur!=NULL)
    {
        if(cur->jobNo == nu) return cur->pid ;
        cur = cur->next ;
    }
    return -1 ;
}
int sendsig(char **args)
{
    ll sig = To_Int(args[2]) ;
    ll job_nu = To_Int(args[1]) ;
    ll pid = get_pid_from_job(job_nu) ;
    if(pid == -1)
    {
        perror("Illegal job number\n") ;
        return 0 ;
    }
    if( kill(pid,sig)==-1)
    {
        perror("Unable to send the signal") ;
        return 0 ;
    }
    return 1 ;
}
int fg(char **args)
{
    ll job_nu = To_Int(args[1]) ;
    ll pid = get_pid_from_job(job_nu) ;
    if(pid == -1)
    {
        perror("Illegal job number\n") ;
        return 0 ;
    }
    int status ;
    pid_t w  ;
    // w = waitpid(pid, &status, WUNTRACED | WCONTINUED);

    kill(pid,18) ;

    delete_pid(pid) ;
    return 1 ;
}
void sigintHandler_Z()
{
  ll pid=getpid();
  kill(pid,18);
  return ;

}
int killall(char **args)
{
    node *cur = head_PidList ;
    while(cur!=NULL)
    {
        if ( kill(cur->pid,9)==-1)
        {
            perror("Unable to exit the process") ;
            return 0 ;
        }
        cur = cur->next ;
    }
    empty_process_queue() ;
    head_PidList=NULL ;
    return 1 ;
}
