//Kunal Arora
//737/IT/12
//Program to implement Round robin scheduling algorithm
#include<stdio.h>
#include<stdlib.h>
#define executed 1
#define not_exec 0
#define Yes 1
#define No 0

typedef struct process
{
    int id;
    int arr;
    int bt;
    int wt;
    int ft;
    int status;
    int queued;
} process;

typedef struct node_q
{
    process* pr;
    struct node_q* next;
} node_q;
node_q* top_q;
void enqueue(process* n)
{
    node_q* temp_q=(node_q*)malloc(sizeof(node_q));
    if(temp_q==NULL)
    {
        printf("Memory could not be allocated successfully");
    }
    temp_q->pr=n;
    if(top_q==NULL)
    {
        top_q=temp_q;
        top_q->next=NULL;
    }
    else
    {
        node_q* ptr=top_q;

        while(ptr->next!=NULL)
        {

            ptr=ptr->next;
        }
        temp_q->next=NULL;
        ptr->next=temp_q;
    }
}
process* dequeue()
{
    process* k;
    if(top_q==NULL)
    {
        //printf("The queue is empty");
        k=NULL;
    }
    else
    {
        node_q* temp_q=top_q;
        k=top_q->pr;
        top_q=top_q->next;
        free(temp_q);
    }
    return k;
}

process* getnode(int id,int arr,int bt)
{
    process *pr=(process*)malloc(sizeof(process));
    pr->id=id;
    pr->arr=arr;
    pr->bt=bt;
    pr->wt=0;
    pr->ft=0;
    pr->status=not_exec;
    pr->queued=Yes;
    return pr;
}
void disp_q()
{
    node_q *temp=top_q;
    while(temp!=NULL)
    {
        printf("%d ",temp->pr->id);
        temp=temp->next;
    }
}

void roundRobin(process *pr,int size,int quanta,float *awt,float *atat)
{

    process *p,*p1;
    node_q *temp;
    int ct=0,tempQuanta,i;
    //putting all the processes that have arrived into the queue
    for(i=0; i<size; i++)
    {
        if(ct>=pr[i].arr && pr[i].queued==No)
        {
            p1=getnode(i,pr[i].arr,pr[i].bt);
            pr[i].queued=Yes;
            p1->queued=Yes;
            enqueue(p1);
        }
    }
    do
    {
        //printf("\nquanta-%d",quanta);
        p=dequeue();
        if(p==NULL)
        {
            //all processes executed
            break;
        }
        else
        {
            //printf("hey");
            tempQuanta=-1;
            if(p->bt-quanta<0)
            {
                tempQuanta=p->bt;
                p->bt=0;
            }
            else
                p->bt-=quanta;
            temp=top_q;
            //increasing the waiting time of all those in the q
            while(temp!=NULL)
            {
                if(tempQuanta>0)
                    temp->pr->wt+=tempQuanta;
                else
                    temp->pr->wt+=quanta;
                temp=temp->next;
            }
            //putting all the processes that have arrived into the queue
            for(i=0; i<size; i++)
            {
                if(ct>=pr[i].arr && pr[i].queued==No)
                {
                    p1=getnode(i,pr[i].arr,pr[i].bt);
                    p1->queued=Yes;
                    pr[i].queued=Yes;
                    enqueue(p1);
                }
            }
            if(tempQuanta>0)
            {
                ct+=tempQuanta;
            }
            else
                ct+=quanta;
            if(p->bt!=0)
                enqueue(p);
            else
            {
                //if the process is executed , update the process structure array
                pr[p->id].wt=p->wt;
                //printf("\npr=%d and p=%d",pr[p->id].wt,p->wt);
                pr[p->id].status=executed;
                pr[p->id].ft=ct-pr[p->id].arr;
                //printf("\nft=%d",pr[p->id].ft);

            }
        }

        //display the queue

        if(tempQuanta>0)

            printf("\nThe ready queue after time %d ms is:",ct-tempQuanta);

        else
            printf("\nThe ready queue after time %d ms is:",ct-quanta);


        disp_q();
    }
    while(ct);
    //after all processes executed;
    //calculating the awt and atat
    for(i=0; i<size; i++)
    {
        (*awt)+=pr[i].wt;
        (*atat)+=pr[i].ft;
    }
    *awt=*awt/size;
    *atat=*atat/size;
}
int main()
{
    int n,i,quanta;
    float awt,atat;
    process pr[20];
    printf("\nEnter the no. of processes:");
    scanf("%d",&n);

    for(i=0; i<n; i++)
    {
        printf("\nEnter the arrival and burst time of process %d: ",i+1);
        pr[i].id=i;
        pr[i].queued=No;
        scanf("%d %d",&pr[i].arr,&pr[i].bt);
    }
    printf("\nEnter the time quanta: ");
    scanf("%d",&quanta);

    roundRobin(pr,n,quanta,&awt,&atat);
    printf("\nThe average waiting(AWT)=%.2f",awt);
    printf("\nThe average turnaround time(ATAT)=%.2f\n",atat);
    return 0;
}


