#include<stdio.h>
#include<stdlib.h>
struct Queue
{
	int front,rear;
	int size;
	int *array;
};
struct Queue* createQueue(int cap)
{
	struct Queue *q=(struct Queue*)malloc(sizeof(struct Queue));
	q->size=cap;
	q->front=-1;
	q->rear=-1;
	q->array=(int*)malloc(cap*sizeof(int));
	return q;
}
int isFull(struct Queue *q )
{
	if(q->rear == q->size -1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
int isEmpty(struct Queue *q)
{
	if(q->front == -1 || (q->front > q->rear)) 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void enqueue(struct Queue* q,int item)
{
	if(isFull(q))
	{
		printf("\nQueue full !");
	}
	else
	{
		if(isEmpty(q))
		{
			q->front=0;
			q->rear=0;
			q->array[q->rear]=item;
		}
		else
		{
			q->rear+=1;
			q->array[q->rear]=item;
		}
	}
	
}
int dequeue(struct Queue* q)
{
	if(isEmpty(q))
	{
		printf("\nNothing to dequeue");
		return -1;
	}
	else
	{
		q->front+=1;
		return q->array[q->front-1];
		
	}
}
void printQ(struct Queue*q )
{
	if(isEmpty(q))
	{
		printf("\nEMpty!");
	}
	else
	{
		for(int i=q->front;i<=q->rear;i++)
		{
			printf("%d\t",q->array[i]);
			//printf("\nFront:%d Rear:%d",q->front,q->rear);
		}
		printf("\n");
	}
	
}
struct process
{
	int pid;
	int arrivalTime;
	int exitTime;
	int burstTime;
	int burstTimeUnmodified;
	int turnaroundTime;
	int waitingTime;
};
void printProcess(struct process* p,int nP)
{
	for(int i=0;i<nP;i++)
	{
		printf("\n\nProcess %d",i+1);
		printf("\nId:%d",p[i].pid);
		printf("\nArrival Time:%d",p[i].arrivalTime);
		printf("\nExit time:%d",p[i].exitTime);
		printf("\nBurst TIme:%d",p[i].burstTimeUnmodified);
		printf("\nWaiting time:%d",p[i].waitingTime);
		printf("\nTurnaround time:%d\n",p[i].turnaroundTime);
	}
}
void swap(struct process *a,struct process *b)
{
	struct process temp;
	temp.pid=a->pid;
	temp.arrivalTime=a->arrivalTime;
	temp.burstTime=a->burstTime;
	temp.exitTime=a->exitTime;
	temp.turnaroundTime=a->turnaroundTime;
	temp.waitingTime=a->waitingTime;
	temp.burstTimeUnmodified=a->burstTimeUnmodified;
	
	a->pid=b->pid;
	a->arrivalTime=b->arrivalTime;
	a->burstTime=b->burstTime;
	a->exitTime=b->exitTime;
	a->turnaroundTime=b->turnaroundTime;
	a->waitingTime=b->waitingTime;
	a->burstTimeUnmodified=b->burstTimeUnmodified;
	
	b->pid=temp.pid;
	b->arrivalTime=temp.arrivalTime;
	b->burstTime=temp.burstTime;
	b->exitTime=temp.exitTime;
	b->turnaroundTime=temp.turnaroundTime;
	b->waitingTime=temp.waitingTime;
	b->burstTimeUnmodified=temp.burstTimeUnmodified;
	
	
	
}
void sortbyArrival(struct process *p,int nP)
{
	int min=0;
	for(int i=0;i<nP-1;i++)
	{
		min=i;
		for(int j=i+1;j<nP;j++)
		{
			if(p[j].arrivalTime < p[min].arrivalTime)
			{
				min=j;
			}
		}
		swap(&p[i],&p[min]);
		
	}
}
int getProcessId(struct process *p,int id,int nP)
{
	
	for(int i=0;i<nP;i++)
	{
		if(p[i].pid == id)
		{
			return i;
		}
	}
}
int main()
{
	struct Queue *q;
	q=createQueue(40);
	/*enqueue(q,10);
	enqueue(q,20);
	enqueue(q,30);
	printQ(q);
	dequeue(q);
	dequeue(q);
	dequeue(q);
	printQ(q);*/
	
	struct process *p;
	int p_id,index;
	int p_count=1;
	int nP;
	int curTime=0;
	int tQ=2;
	
	printf("\nEnter the number of processes:");
	scanf("%d",&nP);
	p=(struct process*)malloc(nP*sizeof(struct process));
	for(int i=0;i<nP;i++)
	{
		p[i].pid=i+1;
		printf("\nEnter arrival time for process %d:",i+1);
		scanf("%d",&(p[i].arrivalTime));
		printf("\nEnter burst time for process %d:",i+1);
		scanf("%d",&(p[i].burstTime));
		p[i].burstTimeUnmodified=p[i].burstTime;		
	}
	sortbyArrival(p,nP);
	enqueue(q,p[0].pid);
	
	while(!isEmpty(q))
	{
		p_id=dequeue(q);
		index=getProcessId(p,p_id,nP);
		//printf("\nProcess %d being serviced\n",p[index].pid);
		if(p[index].burstTime > tQ)
		{
			
			p[index].burstTime=p[index].burstTime-tQ;
			p[index].exitTime=curTime+tQ;
			curTime=p[index].exitTime;
			if(p_count<nP)
			{
				for(int i=p_count;i<nP;i++)
				{
					if(p[i].arrivalTime <= curTime)
					{
						enqueue(q,p[i].pid);
						p_count++;
					}
				}
			}
			enqueue(q,p[index].pid);
			
		}
		else if(p[index].burstTime <= tQ)
		{
			p[index].exitTime=curTime+p[index].burstTime;
			p[index].burstTime=0;
			curTime=p[index].exitTime;
		}	
		//printf("\nIN Q:");
		//printQ(q);			
	}
	
	
	float tat=0;
	float wt=0;
	for(int i=0;i<nP;i++)
	{
		p[i].turnaroundTime=p[i].exitTime-p[i].arrivalTime;
		p[i].waitingTime=p[i].turnaroundTime-p[i].burstTimeUnmodified;
		tat+=p[i].turnaroundTime;
		wt+=p[i].waitingTime;		
	}
	printProcess(p,nP);
	float avgw;
	float avgt;
	avgw=wt/nP;
	avgt=tat/nP;
	printf("\nTurnaround=%f\nWaiting=%f",avgt,avgw);
	//printQ(q);
	//printProcess(p,nP);	
	return 0;
}
