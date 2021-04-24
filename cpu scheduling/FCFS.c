
//program for FCFS scheduling 
#include<stdio.h>
int main()
{
    int n,at[10],bt[10],rt[10],wt[10],tat[10];//declarating variables
    float avgtat=0,avgwt=0;
    printf("Enter no. of processes\n");
    
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("Enter arrival time process %d\t",i+1);
        scanf("%d",&at[i]);
        printf("Enter burst time process %d\t",i+1);
        scanf("%d",&bt[i]);

    }
    //printing Gantt
    printf("\nGantt chart:\n\n");
    int time=0;
    int idt=0;//idle time
    int endtime=0;
    int remain=0;
    int finished[10]={0};//initial case 
    while(remain!=n)
    {
        int small=99999; //Smallest arrival Time
        int smallest;//smallest p_id;
        for(int i=0;i<n;i++)
        {
            if(at[i]<=small && finished[i]==0)
            {
                small=at[i];
                smallest=i;
            }
        }
        if(small > time)
        {
            idt++;
            printf("|%d| IDLE ",time);
            time+=1;
        }
        else
        {
            
            printf("|%d| P%d ",time,smallest+1);
            remain++;
            finished[smallest]=1;
            endtime=time+bt[smallest];
            tat[smallest]=endtime-at[smallest];
            wt[smallest]=endtime-at[smallest]-bt[smallest];
            time+=bt[smallest];
        }

    }
    printf("|%d|",time);
    printf("\n\nPID\tAT\tBT\tTAT\tWT\n\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],tat[i],wt[i]);
    }

     for(int i=0;i<n;i++)
    {
        avgtat=avgtat+tat[i];
        avgwt=avgwt+wt[i];
    }

    printf("Average turn around time=%f\n",avgtat/n);
    printf("Average waiting time=%f\n",avgwt/n);


}
