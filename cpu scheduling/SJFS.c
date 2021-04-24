#include<stdio.h>
int main()
{
    int n,at[10],bt[10],rt[10],wt[10],tat[10];
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

    printf("\nGantt chart:\n\n");
    bt[9]=9999;
    int time=0;
    int idt=0;
    int endtime=0;//similar to completion time;;
    int remain=0;
    int finished[10]={0};
    while(remain!=n)
    {
        int longest=9;
        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && bt[i]<bt[longest] && finished[i]==0)
            {
                longest=i;
            }
        }
        if(longest==9)
        {
            idt++;
            printf("%d IDLE ",time);
            time+=1;
        }
        else
        {
            
            printf("%d P%d ",time,longest+1);
            remain++;
            finished[longest]=1;
            endtime=time+bt[longest];
            tat[longest]=endtime-at[longest];
            wt[longest]=endtime-at[longest]-bt[longest];
            time+=bt[longest];
        }

    }
    printf("%d",time);
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