#include "c_initialise.h"
#include "main.h"
#include "commands.h"
int print_info(char *pid)
{
    char path[buf_len],buffer[200];
    strcpy(path,"/proc/") ;
    strcat(path,pid) ; //path is the absolute path the /proc/<pid>/ , required to read the necessary files
    strcat(path,"/status") ;
    printf("PID : %s ",pid) ; //printing the PID(process ID)

    FILE *status = fopen(path,"r") ;
    if(status == NULL)
    {
        perror("Error in opening the required File. Check if the entered PID is correct\n") ;
        return 0 ;
    }
    while(!feof(status))
    {
        fscanf(status,"%[^\n]\n",buffer) ;
        if(strstr(buffer,"Name")!=NULL)
        {
            printf("%s\n",buffer) ;
            break ;
        }
    }
    fclose(status) ;
    return 1 ;
}
void convert_to_String(long long pid,char S[])
{
    int i,j;
    char temp[100] ;
    for(i=0;pid>0;++i,pid/=10) temp[i]=(char)('0'+pid%10) ;
    if(i==0) temp[i]='0' ;
    else --i ;
    for(j=0;i-j>=0;++j) S[j]=temp[i-j];
    S[j]='\0' ;

}
int list_jobs(char **args)
{
//  printf("%s\n","inside list" );
    node *cur = head_PidList ;
    char pid[buf_len] ;
  //  while(cur!=NULL) printf("in list %lld\n",cur->pid ) ,cur = cur->next;
    cur = head_PidList ;
    while(cur!=NULL)
    {
        convert_to_String(cur->pid,pid) ;
        printf("[ %lld ] ",cur->jobNo) ;
        if( print_info(pid)==0) return 0 ;
        cur = cur->next ;
    }
    return 1 ;
}
void add_pid(ll pid)
{
  // printf("here to insert\n") ;
  head_PidList = add_linkedlist(head_PidList,pid,Avail_Job++);
  // if(head_PidList==NULL) printf("%s\n","you are doomed" );
}
void delete_pid(ll pid)
{
  //printf("%s\n","here to delete" );
  node *cur = head_PidList ;
  // while(cur!=NULL) printf("in list %lld\n",cur->pid ) ,cur = cur->next;
  head_PidList = delete_linkedlist(head_PidList,pid);
  cur = head_PidList ;
  //while(cur!=NULL) printf("in list %lld\n",cur->pid ) ,cur = cur->next;
  //
//  if(head_PidList==NULL)printf("%s\n","empty" );
}
void empty_process_queue(void) { empty_list(head_PidList);}
