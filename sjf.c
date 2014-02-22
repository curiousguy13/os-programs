//KUNAL ARORA
//737/IT/12
//Program to implement Shortest Job First Scheduling Program

#include<stdio.h>
#define executed 1
#define not_exec 0
//structure for a process
typedef struct process
{
    int arr;        //arrival time
    int bt;         //burst time
    int wt;		//waiting time
    int ft;		//finish time
    int status;
} process;

void sjf(process *pr,int n,float *awt,float *atat);
int shortestProcess(process *pr,int n,int ct);
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
    sjf(pr,n,&awt,&atat);
    printf("\nThe average waiting time(AWT)=%.2f",awt);
    printf("\nThe average turnaround time(ATAT)=%.2f\n",atat);
    return 0;
}
void sjf(process *pr,int n,float *awt,float *atat)
{
	int i,ct=0,spi;	//ct->current time,spi->shortest process index
	//initialising each process as not executed
	for(i=0;i<n;i++)
	{
		pr[i].status=not_exec;
	}
	printf("\nThe order of execution of processes is:");
	for(i=0;i<n;i++)
	{
	    //printf("spi=%d",spi);
		spi=shortestProcess(pr,n,ct);
		printf("P%d\t",spi+1);
		pr[spi].wt=ct-pr[spi].arr;   //waiting time of executed process=(current time) - (it's arrival time)
		//printf("wt=%d",pr[spi].wt);
		ct+=pr[spi].bt;		//updating current time
		pr[spi].ft=ct-pr[spi].arr;		//finish time of the executed process
		pr[spi].status=executed;


	}

	for(i=0;i<n;i++)
	{
		(*awt)+=pr[i].wt;
		(*atat)+=pr[i].ft;
	}
	*awt=*awt/n;
	*atat=*atat/n;
	/*for debugging
	printf("\nWaiting Times:");
	for(i=0;i<n;i++)
	{
		printf("%d\t",pr[i].wt);
	}

	printf("\nturnaround Times:");
	for(i=0;i<n;i++)
	{
		printf("%d\t",pr[i].ft);
	}
*/
}
//returns the index of shortest process arrived beore the current time ct
int shortestProcess(process *pr,int n,int ct)
{
	int i,min_bt=99999,min_index=-1;
	for(i=0;i<n;i++)
	{
		if(pr[i].status==not_exec && pr[i].arr<=ct)
		{
			if(pr[i].bt<min_bt)
			{
			    min_bt=pr[i].bt;
				min_index=i;
			}
		}
	}
	return min_index;
}

//to give the sum of the array
int sumArray(int *arr,int n)
{
    int sum=0,i;
    for(i=0; i<n; i++)
    {
        sum+=arr[i];
    }
    return sum;
}

//to display an array
void dispArray(int *arr,int n)
{
    int i=0;
    for(i=0; i<n; i++)
    {
        printf("%d",arr[i]);
    }
}
