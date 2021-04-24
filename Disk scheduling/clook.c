//clook Disk Scheduling Implementation

//Contributor: Vinesh S Talpankar 191CS265

#include <stdio.h>
#include <stdlib.h>
#define N 1000

void swap(int a[], int i, int j)    //To swap numbers
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void sort(int a[], int n)   //Bubble sort
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j])
                swap(a, i, j);
}

int main()
{
    system("clear");
    int n, numberOfTracks, choice;
    int request[N];
    float avg;
    printf("\n%s\n\n", "------------------CLOOK Disk Scheduling Algorithm------------------");
    printf("Enter number of tracks : ");        //Enter total number of tracks on disk
    scanf("%d", &numberOfTracks);

    printf("Enter number of requests : ");      //Enter number of requests
    scanf("%d", &n);
    j1:

    printf("Enter current track position : ");  //Enter starting position
    scanf("%d", &request[0]);

    if (request[0] >= numberOfTracks || request[0] < 0)
    {
        printf("Invalid track....\n");              //Track out of range
        goto j1;
    }

    printf("\nEnter the requests\n");
    for (int i = 1; i <= n; i++)
    {
        j2: printf("Enter track request %d: ", i);
        scanf("%d", &request[i]);
        if (request[i] >= numberOfTracks || request[i] < 0)
        {
            printf("Invalid track....\n");              //Track out of range
            goto j2;
        }
    }
    n++;

    int ans, pos, firstRequest = request[0];
    sort(request, n);

    //Find position of first request
    for (int i = 0; i < n; i++)
        if (request[i] == firstRequest)
        {
            pos = i;
            break;
        }
    printf("\nHead movement\n");
    //Forward movement
    for (int i = pos + 1; i < n; i++)
        printf("Move from %d to %d with Seek %d\n", request[i - 1], request[i], abs(request[i - 1] - request[i]));

    //Backward movement
    if (pos > 0)
        printf("Move from %d to %d with Seek %d\n", request[n - 1], request[0], abs(request[n - 1] - request[0]));
    for (int i = 1; i < pos; i++)
        printf("Move from %d to %d with Seek %d\n", request[i - 1], request[i], abs(request[i - 1] - request[i]));

    ans = request[n - 1] - request[pos];    //Total seek time calculation
    if (pos > 0)
        ans += request[pos - 1] - request[0] + (request[n - 1] - request[0]);   //Total seek time calculation

    //Results
    printf("\nTotal seek time is %d\t", ans);
    avg = ans / (float) n;
    printf("\nAverage seek time is %f\n\n", avg);
}