#include<stdio.h>
#include<stdlib.h>
struct processInfo
{
	int id;
	int arrivalTime;
	int burstTime;
	int exitTime;
	int turnAroundTime;
	int waitingTime;
	int priority;
	int remainingTime;
};
void copyProcessInfo(struct processInfo *a,struct processInfo *b)
{
	a->id=b->id;
	a->arrivalTime=b->arrivalTime;
	a->burstTime=b->burstTime;
	a->exitTime=b->exitTime;
	a->turnAroundTime=b->turnAroundTime;
	a->waitingTime=b->waitingTime;
	a->priority=b->priority;
	a->remainingTime=b->remainingTime;
}
void copy(struct processInfo *a,struct processInfo *b, int n)
{
	for(int i=0;i<n;i++)
	{
		a[i].arrivalTime=b[i].arrivalTime;
		a[i].burstTime=b[i].burstTime;
		a[i].id=b[i].id;
		a[i].exitTime=b[i].exitTime;
		a[i].turnAroundTime=b[i].turnAroundTime;
		a[i].waitingTime=b[i].waitingTime;
		a[i].priority=b[i].priority;
		a[i].remainingTime=b[i].remainingTime;
	}
	
	
}
void getProcessDetails(struct processInfo *p,int n)
{
	 for(int i=0;i<n;i++)
	 {
	 	printf("\nProcess %d:",i);
	 	p[i].id=i;
	 	printf("\nEnter the arrival time:");
	 	scanf("%d",&(p[i].arrivalTime));
	 	printf("\nEnter the burst time:");
	 	scanf("%d",&(p[i].burstTime));
	 	p[i].remainingTime=p[i].burstTime; 	
	}
}
void swap(struct processInfo *a,struct processInfo *b)
{
	//printf("\nInside swap\n");
	struct processInfo p;
	p.id=a->id;
	p.arrivalTime=a->arrivalTime;
	p.burstTime=a->burstTime;
	p.exitTime=a->exitTime;
	p.turnAroundTime=a->turnAroundTime;
	p.waitingTime=a->waitingTime;
	p.priority=a->priority;
	p.remainingTime=a->remainingTime;
	
	a->id=b->id;
	a->arrivalTime=b->arrivalTime;
	a->burstTime=b->burstTime;
	a->exitTime=b->exitTime;
	a->turnAroundTime=b->turnAroundTime;
	a->waitingTime=b->waitingTime;
	a->priority=b->priority;
	a->remainingTime=b->remainingTime;
	
	b->id=p.id;
	b->arrivalTime=p.arrivalTime;
	b->burstTime=p.burstTime;
	b->exitTime=p.exitTime;
	b->waitingTime=p.waitingTime;
	b->turnAroundTime=p.turnAroundTime;
	b->priority=p.priority;
	b->remainingTime=p.remainingTime;
}
void sortbyArrivalTime(struct processInfo *p, int n)
{
	//printf("\nInside sort\n");
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(p[i].arrivalTime > p[j].arrivalTime)
			{
				swap(&(p[i]),&(p[j]));
			}
		}
	}
}
void printProcess(struct processInfo *p, int n)
{
	for(int i=0;i<n;i++)
	{
		printf("\nId:%d\narrivalTime:%d\nburstTime:%d\nexitTime:%d\n",p[i].id,p[i].arrivalTime,p[i].burstTime,p[i].exitTime);
	}
}
void printProcessInfo(struct processInfo p)
{
	printf("\nId:%d\narrivalTime:%d\nburstTime:%d\n",p.id,p.arrivalTime,p.burstTime);
}
void ganttChart(struct processInfo *p, int n)
{
	for(int i=0;i<n;i++)
	{
		printf("|\t%d|\t",p[i].id);	
	}
	printf("\n");
	printf("%d",p[0].arrivalTime);
	for(int i=1;i<n;i++)
	{
		printf("%d\t ",p[i].exitTime);
	}	
}
/*int findSmallest(int i,struct processInfo *p,int n)
{
	int minbT=p[i].burstTime;
	int minId=p[i].id;
	for(int j=i;j<n;j++)
	{
		if(p[j].burstTime<minbT)
		{
			minbT=p[j].burstTime;
			minId=p[j].id;
		}
	}
	return minId;
}*/
int main()
{
	int n;
	printf("\nEnter number of processes:");
	scanf("%d",&n);
	struct processInfo *p;
	p=(struct processInfo*)malloc(n*sizeof(struct processInfo));
	getProcessDetails(p,n);
	int choice;
	while(1)
	{
		printf("\n1.FCFS\t2.SFJ\t3.Priority\t4.Exit\nEnter:");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("\nApplying the FCFS algorithm ...\n");
			struct processInfo *lp;
			lp=malloc(n*sizeof(struct processInfo ));
			copy(lp,p,n);
			
			int curTime=0;
			sortbyArrivalTime(lp,n);
			//FCFS Logic
			lp[0].exitTime=lp[0].arrivalTime+lp[0].burstTime;
			curTime=lp[0].exitTime;
			for(int i=1;i<n;)
			{
				if(lp[i].arrivalTime <= curTime)
				{
					lp[i].exitTime=curTime+lp[i].burstTime;
					curTime=lp[i].exitTime;
					i++;
				}
				else
				{
					curTime+=1;
				}
			}
			//End of FCFS Logic
			//Calculate turaround and waiting time
			int tAt=0;
			int wT=0;
			float avg;
			for(int i=0;i<n;i++)
			{
				lp[i].turnAroundTime=lp[i].exitTime-lp[i].arrivalTime;
				lp[i].waitingTime=lp[i].turnAroundTime-lp[i].burstTime;
				tAt=tAt+lp[i].turnAroundTime;
				wT=wT+lp[i].waitingTime;
			}
			printProcess(lp,n);
			avg=(float)tAt/n;
			printf("\nAverage Turnaround time= %0.2f ms",avg);
			avg=(float)wT/n;
			printf("\nAverage Waiting time= %0.2f ms",avg);
			
		}
		else if(choice == 2)
		{
			struct processInfo *lp;
			lp=malloc(n*sizeof(struct processInfo));
			copy(lp,p,n);
			//Sort By arrival time
			sortbyArrivalTime(lp,n);
			
			//Assigning P[0] as the first process
			int curTime=0;
			lp[0].exitTime=lp[0].burstTime+lp[0].arrivalTime;
			curTime=lp[0].exitTime;
			
			//For every subsequent process
			int i=1;
			for(;i<n-1;i++)
			{
				int minbT=lp[i].burstTime;
				int minId=i;
				for(int j=i+1;j<n;j++)
				{
					if(lp[j].burstTime<minbT && lp[j].arrivalTime<=curTime)
					{
						minbT=lp[j].burstTime;
						minId=j;
					}
				}
				swap(&(lp[i]),&(lp[minId]));
				
				lp[i].exitTime=curTime+lp[i].burstTime;
				curTime=lp[i].exitTime;
			}
			lp[i].exitTime=curTime+lp[i].burstTime;
			curTime=lp[i].exitTime;
			
			
			printf("\nScheduled Processes ....\n");
			printProcess(lp,n);
			
			//Calculate average waiting and turnaroud time
			int taT=0;
			int wT=0;
			float avg;
			
			for(int i=0;i<n;i++)
			{
				lp[i].turnAroundTime=lp[i].exitTime-lp[i].arrivalTime;
				lp[i].waitingTime=lp[i].turnAroundTime-lp[i].burstTime;
				taT+=lp[i].turnAroundTime;
				wT+=lp[i].waitingTime;
			}
			avg=(float)taT/n;
			printf("\nAverage Turnaround time= %0.2f ms",avg);
			avg=(float)wT/n;
			printf("\nAverage Waiting time= %0.2f ms",avg);			
		}
		else if(choice==3)
		{
			struct processInfo *lp;
			lp=malloc(n*sizeof(struct processInfo));
			copy(lp,p,n);
			sortbyArrivalTime(lp,n);
			printf("\nEnter the priority of the processes:");
			for(int i=0;i<n;i++)
			{
				scanf("%d",&(lp[i].priority));
			}
			int curTime=0;
			lp[0].exitTime=lp[0].arrivalTime+lp[0].burstTime;
			curTime=lp[0].exitTime;
			int i=1;
			for(;i<n-1;i++)
			{
				int maxPriority=lp[i].priority;
				int maxId=i;
				for(int j=i+1;j<n;j++)
				{
					if(lp[j].priority>maxPriority && lp[j].arrivalTime<=curTime)
					{
						maxPriority=lp[j].priority;
						maxId=j;
					}
				}
				swap(&(lp[i]),&(lp[maxId]));
				lp[i].exitTime=curTime+lp[i].burstTime;
				curTime=lp[i].exitTime;
			}
			lp[i].exitTime=lp[i].burstTime+curTime;
			curTime=lp[i].exitTime;
			printf("\nScheduled Processes ....\n");
			printProcess(lp,n);
			
			//Calculate average waiting and turnaroud time
			int taT=0;
			int wT=0;
			float avg;
			
			for(int i=0;i<n;i++)
			{
				lp[i].turnAroundTime=lp[i].exitTime-lp[i].arrivalTime;
				lp[i].waitingTime=lp[i].turnAroundTime-lp[i].burstTime;
				taT+=lp[i].turnAroundTime;
				wT+=lp[i].waitingTime;
			}
			avg=(float)taT/n;
			printf("\nAverage Turnaround time= %0.2f ms",avg);
			avg=(float)wT/n;
			printf("\nAverage Waiting time= %0.2f ms",avg);	
			
		}
		
		else if(choice==4)
		{
			return 0;
		}
	}
	return 0;
}
