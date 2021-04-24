//implementing Round Robin (RR)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    struct OS
{
    int p_no,at,bt,ct,tat,wt,flag; //process id,arrival time,burst time,completion time,term around time and wait time

}*p;
    int n,i;
    printf("  Enter number of processes: ");
    scanf("%d",&n);
    struct OS arr[n];
  
    for(i=0;i<n;i++)
    {
        arr[i].p_no = i+1;
        //printf("\n  Process %d\n",arr[i].p_no);
        printf("  Enter arrival time  of %d\t",i+1);
        scanf("%d",&arr[i].at);
        printf("  Enter burst time of %d\t",i+1);
        scanf("%d",&arr[i].bt);
    }
    p=arr; //assigning base address of structure array to a pointer for easy handling of data

   {
    int time=0,slice=2,i=0;//slice time set to 2
    printf("enter the time slice");
    scanf("%d",&slice);
    int temp_bt[n];
    for(i=0;i<n;i++)
    {
        temp_bt[i] = (p+i)->bt;
        (p+i)->flag = 0;
    }
    char over;
    printf("\nGantt chart:\n");
    while(1)
    {
        for(i=0;i<n;i++)
        {
            over = 'y';//let it yes
            for(int k=0;k<n;k++)
            {
                if((p+k)->flag ==0)
                    over = 'n';//there are still elements left
            }
            //looping and reducing the time slice
            for(int j=1;j<=slice;j++)
            {
                
                if((p+i)->at <= time )
                {
                    
                    if((p+i)->flag == 0)
                    {
                        printf(" P%d ",(p+i)->p_no);
                       
                        time++;
                        printf(" |%d| ",time);
                        temp_bt[i]--;
                        if(temp_bt[i] == 0)
                        {
                            (p+i)->ct = time;
                            //printf("|%d|",time);

                            (p+i)->flag = 1;
                            break;
                        }
                    }
                }
                else //in case no process has arrived yet
                {
                    printf("|%d|",time);
                    printf(" IDLE ");
                    //
                    time++;
                    printf("|%d|",time);
                    
                    j=0;//to avoid odd slicing of time

                }
            }
        }
        if(over == 'y')
            break;
    }
    for(i=0;i<n;i++)
    {
        (p+i)->tat = (p+i)->ct - (p+i)->at ;
        (p+i)->wt = (p+i)->tat - (p+i)->bt ;
    }
}

    float avg_tat,avg_wt;
    printf("\n\n  P.ID\tAT\tBT\tCT\tTAT\tWT");
    for(i=0;i<n;i++)
    {
        printf("\n  %d\t%d\t%d\t%d\t%d\t%d\t",(p+i)->p_no,(p+i)->at,(p+i)->bt,(p+i)->ct,(p+i)->tat,(p+i)->wt);
        avg_tat+=(p+i)->tat; avg_wt+=(p+i)->wt;
    }
    avg_tat/=n; avg_wt/=n;
    printf("\n\n  The average  TAT is %f\n  The average WT is %f\n",avg_tat,avg_wt);
    return 0;
}



