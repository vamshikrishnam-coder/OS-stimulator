//HRRN
#include <iostream>
#include <stdio.h>

int main()
{
    int i, j, t,n;
    float avgwt = 0, avgtt = 0;
    printf("Enter no of process : ");
    scanf("%d",&n);
    struct process
	{
    	int at, bt, wt, tt, pos, completed;
	} p[n];

    int arriv[n];
    int burst[n];
    for(i=0;i<n;i++)
    {
        printf("\nEnter arrival time and burst time of  Process %d  : ",i);
        scanf("%d %d",&arriv[i],&burst[i]);
        if(burst[i]<=0||arriv[i]<0)
        {
        	printf("Invalid input\n");
        	i--;
		}
    }
    for (i = 0; i < n; i++) 
	{
        p[i].at = arriv[i];
        p[i].bt = burst[i];
        p[i].completed = 0;
        p[i].pos=i;
    }

    // Sorting the structure by arrival times
    struct process temp;
    for (i = 0; i < n - 1; i++)
	 {
        for (j = i+1; j < n; j++) 
		{
            if (p[i].at > p[j].at)
			 {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int time[100000];
    for(i=0;i<100000;i++)
    {
    	time[i]=-1;
	}
    printf("\nProcess Number\tArrival Time\tBurst Time\tWaiting Time");
    printf("\tTurnAround Time");
    t = p[0].at;
    while(1) 
	{
        float hrr = -1.00;
        float temp;
        int loc;
        for (i = 0; i < n; i++)
		 {
            // Checking if process has arrived and is Incomplete
            if (p[i].at <= t && p[i].completed != 1)
			 {
                 // Calculating Response Ratio
                temp = (p[i].bt + (t - p[i].at)) / (p[i].bt+0.0);
                // Checking for Highest Response Ratio
                if (hrr < temp)
				{
                    hrr = temp;
                    loc = i;
                }
            }
        }
		if(hrr==-1.00)
		{
			int a=100000;
			int po;
		    for (i = 0; i < n; i++) 
			{
	            if (p[i].completed != 1)
				 {
	                if(p[i].at<a)
	                {
	                	a=p[i].at;
	                	po=i;
	                }
	            }
            
			}
			bool x=false;
	        for(i=0;i<n;i++)
	        {
	        	if(p[i].completed==0)
	        	{
	        		x=true;
	        		break;
				}
			}
			if(x==false)
			{
				break;
			}
			t=p[po].at;
			continue;
			
		}        
        for(j=t;j<(t+p[loc].bt);j++)
        {
        	time[j]=p[loc].pos;
		}
		t += p[loc].bt;
        p[loc].wt = t - p[loc].at - p[loc].bt;  // Calculation of waiting time
        p[loc].tt = t - p[loc].at;  // Calculation of Turn Around Time
        avgtt += p[loc].tt;
        p[loc].completed = 1;
        avgwt += p[loc].wt;
        printf("\n%d\t\t%d\t\t", p[loc].pos, p[loc].at);
        printf("%d\t\t%d\t\t", p[loc].bt, p[loc].wt);
        printf("%d", p[loc].tt);
      
    }
    printf("\nGantt chart-\n0 ");
    if(time[0]==-1)
    {
    	printf("idle ");
	} 
	else
	{
		printf("P%d ",time[0]);
	}
    for(i=1;i<100000;i++)
    {
    	if(i==t)break;
    	if(time[i]!=time[i-1])
    	{
    		printf("%d ",i);
    		if(time[i]==-1)
    		{
    			printf("idle ");
			}
			else
			{
				printf("P%d ",time[i]);
			}
		}
	
	}
	printf("%d ",t);
    printf("\nAverage waiting time:%f\n", avgwt / n);
    printf("Average Turn Around time:%f\n", avgtt / n);
}