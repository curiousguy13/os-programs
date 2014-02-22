//KUNAL ARORA
//737/IT/12
//Program to implement First come first serve scheduling algorithm

#include<stdio.h>
//structure for a process
typedef struct process
{
    int arr;        //arrival time
    int bt;         //burst time
} process;

void fcfs(process *pr,int n,float *awt,float *atat);
int sumArray(int *arr,int n);
void dispArray(int *arr,int n);

int main()
{
    int n,i;
    float awt,atat;
    process pr[20];
    printf("\nEnter the no. of processes:");
    scanf("%d",&n);

    for(i=0; i<n; i++)
    {
        printf("\nEnter the arrival and burst time of process %d: ",i+1);
        scanf("%d %d",&pr[i].arr,&pr[i].bt);
    }
    fcfs(pr,n,&awt,&atat);
    printf("\nThe average waiting(AWT)=%.2f",awt);
    printf("\nThe average turnaround time(ATAT)=%.2f",atat);
    return 0;
}
void fcfs(process *pr,int n,float *awt,float *atat)
{
    //for average waiting time
    int temp[20],i;
    printf("\nThe order of execution of processes is:");
    for(i=0; i<n; i++)
    {
        if(i==0)
        {
            temp[i]=pr[i].arr;
        }
        else
        {
            temp[i]=temp[i-1]+pr[i-1].bt-pr[i].arr+pr[i-1].arr;
        }
        printf("P%d\t",i+1);
    }
    *awt=(float)sumArray(temp,n)/n;

    //for average turnaround time
    for(i=0; i<n; i++)
    {
        if(i==0)
        {
            temp[i]=pr[i].bt;
        }
        else
        {
            temp[i]=temp[i-1]+pr[i].bt-pr[i].arr+pr[i-1].arr;
        }
    }
    *atat=(float)sumArray(temp,n)/n;

}

int sumArray(int *arr,int n)
{
    int sum=0,i;
    for(i=0; i<n; i++)
    {
        sum+=arr[i];
    }
    return sum;
}
void dispArray(int *arr,int n)
{
    int i=0;
    for(i=0; i<n; i++)
    {
        printf("%d",arr[i]);
    }
}
