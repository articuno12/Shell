#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#define buf_len 2000
#define ll long long
char * setting_home();
int initialise();
char * home_dir(void);
char* getname();
char* current_directory();
void printinfo();
typedef struct node
{
    ll pid,jobNo ;
    struct node* next ;
}node ;
node *head_PidList ;
int Avail_Job ;
node *add_linkedlist(node* head,ll pid,ll nu) ;
node *delete_linkedlist(node *head,ll pid) ;
void add_pid(ll pid) ;
void delete_pid(ll pid) ;
void empty_list(node *head) ;
void empty_process_queue(void) ;
// bool typed=false ;
ll get_pid_from_job(ll nu) ;
ll To_Int(char S[]) ;

void sigintHandler(int sig_num);
void sigintHandler_Z() ;
int push_to_background ;
