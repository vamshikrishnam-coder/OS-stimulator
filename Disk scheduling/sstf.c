//shortest seek time first Disk Scheduling Implementation

//Contributor: Vinesh S Talpankar 191CS265
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    system("clear");

    int i, j, sum = 0, n, pos, trc, ind, temp;
    float avg;
    printf("\n%s\n\n", "------------------SSTF Disk Scheduling Algorithm------------------");

    printf("Enter number of tracks: ");     //Enter total number of tracks on disk
    scanf("%d", &n);

    j1:
    printf("\nEnter position of head: ");   //Enter starting position
    scanf("%d", &pos);

    if (pos >= n || pos < 0)
    {
        printf("Invalid track....\n");              //Track out of range
        goto j1;
    }
    printf("\nEnter the no of tracks you want to traverse: ");  //Enter number of requests
    scanf("%d", &trc);

    int ar[trc];

    printf("\nEnter tracks of disk queue: \n");
    for (i = 0; i < trc; i++)
    {
        j2: printf("Enter track request %d: ", i + 1);
        scanf("%d", &ar[i]);
        if (ar[i] >= n || ar[i] < 0)
        {
            printf("Invalid track....\n");              //Track out of range
            goto j2;
        }
    }

    printf("\nHead movement\n");
    for (i = 0; i < trc; i++)       
    {
        int st = 1000;
        for (j = 0; j < trc; j++)   //Loop for finding position of track with shortest seek time
        {
            if ((abs(pos - ar[j])) == st)
            {
                if (ar[j] > ar[ind])
                    ind = j;
                else
                    ind = ind;
            }

            if ((abs(pos - ar[j])) < st && st > 0)
            {
                st = abs(pos - ar[j]);
                ind = j;
            }
        }

        pos = ar[ind];
        ar[ind] = 10000;
        printf("New pos is %d\n", pos);
        sum += st;
    }

    //Results
    printf("\nTotal seek time is %d\t", sum);
    avg = sum / (float) trc;
    printf("\nAverage seek time is %f\n\n", avg);
    return 0;
}