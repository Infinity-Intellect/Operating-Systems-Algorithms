#include<stdio.h>
#include<stdlib.h>
#define teste {printf("\nExiting...");return 0;}
void swap(int *x,int *y)
{
	int t=*x;
	*x=*y;
	*y=t;
}
void sort(int **a,int n,int order)
{
	int index;
	if(order==1)
	{
		for(int i=0;i<n;i++)
		{
			index=i;
			for(int j=i+1;j<n;j++)
			{
				if(a[i][0]>a[j][0])
				{
					index=j;
				}
			}
			swap(&a[i][0],&a[index][0]);
			
		}
	}
	else
	{
		for(int i=0;i<n;i++)
		{
			index=i;
			for(int j=i+1;j<n;j++)
			{
				if(a[i][0]<a[j][0])
				{
					index=j;
				}
			}
			swap(&a[i][0],&a[index][0]);
			
		}
	}
	
	
}


int Fit(int **hole, int *process,int nP,int nH,int externalFragmentation)
{
	int internalFragmentation=0;
	for(int i=0;i<nP;i++)
	{
		for(int j=0;j<nH;j++)
		{
			if(hole[j][0]>=process[i] && hole[j][1]==-1)
			{
				externalFragmentation-=hole[j][0];
				internalFragmentation+=hole[j][0]-process[i];
				hole[j][1]+=1;
				break;
			}
		}
		
	}
	return internalFragmentation+externalFragmentation;
}
int main()
{
	int **hole;
	int *process;
	int numberOfProcesses;
	int numberOfHoles;
	int initialFragmentation=0;
	int choice;
	printf("\nEnter the number of processes:");
	scanf("%d",&numberOfProcesses);
	printf("\nEnter the number of holes:");
	scanf("%d",&numberOfHoles);
	process=(int*)malloc(numberOfProcesses*sizeof(int));
	hole=(int**)malloc(numberOfHoles*sizeof(int*));
	for(int i=0;i<numberOfHoles;i++)
	{
		hole[i]=(int*)malloc(2*sizeof(int));
	}
	printf("\nEnter the size of each process:");
	for(int i=0;i<numberOfProcesses;i++)
	{
		scanf("%d",&process[i]);
	}

	printf("\nEnter the size of each of the holes:");
	for(int i=0;i<numberOfHoles;i++)
	{
		scanf("%d",&hole[i][0]);
		initialFragmentation+=hole[i][0];
	}
	while(1)
	{
		for(int i=0;i<numberOfHoles;i++)
		{
			hole[i][1]=-1;
		}
		
		printf("\n1.First Fit\n2.Best Fit\n3.Worst Fit\n4.Exit\nEnter choice:");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("\nTotal Fragmentation:%d\n",Fit(hole,process,numberOfProcesses,numberOfHoles,initialFragmentation));
		}
		else if(choice==2)
		{
			sort(hole,numberOfHoles,1);
			printf("\nTotal Fragmentation:%d\n",Fit(hole,process,numberOfProcesses,numberOfHoles,initialFragmentation));
		}
		else if(choice==3)
		{
			sort(hole,numberOfHoles,-1);
			printf("\nTotal Fragmentation:%d\n",Fit(hole,process,numberOfProcesses,numberOfHoles,initialFragmentation));			
		}
		else if(choice==4)
		{
			exit(0);
		}
	}
	return 0;
}
