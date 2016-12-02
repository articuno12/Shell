#include "c_initialise.h"

//defining node
 node* add_linkedlist(node* head,ll pid,ll nu)
 {
     node *temp = (node*)malloc(sizeof(node)) ;
     temp->next = NULL ;
     temp->pid = pid ;
     temp->jobNo = nu ;
     if(head == NULL) return head=temp ;
     else
     {
      //  printf("%s\n","added101" );
         node *cur = head ;
         while(cur->next!=NULL) cur=cur->next ;
         cur->next = temp ;
     }
     return head ;
 }
node * delete_linkedlist(node *head,ll pid)
{
    if(head==NULL)
    {
        // perror("The requested element not present in the list\n") ;
        return head ;
    }
    if(head->pid == pid)
    {
        node *temp = head->next ;
        free(head) ;
        return temp ;
    }
    node *cur = head ;
    while(cur->next!=NULL && cur->next->pid!=pid) cur=cur->next ;
    if(cur->next==NULL)
    {
        return head ;
    }
    node *temp = cur->next ;
    cur->next = cur->next->next ;
    free(temp) ;
    return head ;
}
void empty_list(node *head)
{
    while(head!=NULL)
    {
        node *temp = head ;
        head = head->next ;
        free(temp) ;
    }
}
