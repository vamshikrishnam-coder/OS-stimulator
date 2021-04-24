//FCFS Disk Scheduling Implementation

//Contributor: Vinesh S Talpankar 191CS265

#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("clear");
    int queue[100], q_size, head, seek = 0, diff, n;
    float avg;

    printf("\n%s\n\n", "------------------FCFS Disk Scheduling Algorithm------------------");

    printf("Enter number of tracks: ");     //Enter total number of tracks on disk
    scanf("%d", &n);

    printf("\nEnter the no of tracks you want to traverse: ");  //Enter number of requests
    scanf("%d", &q_size);

    j1:
    printf("\nEnter position of head: ");   //Enter starting position
    scanf("%d", &head);

    if (head >= n || head < 0)              //Track out of range
    {
        printf("Invalid track....\n");
        goto j1;
    }

    printf("\nEnter tracks of disk queue: \n");
    for (int i = 1; i <= q_size; i++)
    {
        j2: printf("Enter track request %d: ", i);
        scanf("%d", &queue[i]);
        if (queue[i] >= n || queue[i] < 0)
        {
            printf("Invalid track....\n");              //Track out of range
            goto j2;
        }
    }

    printf("\nHead movement\n");
    queue[0] = head;
    printf("\n");
    for (int j = 0; j <= q_size - 1; j++)           //Loop for head movement according to fcfs
    {
        diff = abs(queue[j] - queue[j + 1]);        //Seek calculation
        seek += diff;                               //Total seek calculation
        printf("Move from %d to %d with Seek %d\n", queue[j], queue[j + 1], diff);
    }
    //Results
    printf("\nTotal seek time is %d\t", seek);
    avg = seek / (float) q_size;
    printf("\nAverage seek time is %f\n\n", avg);

    return 0;
}