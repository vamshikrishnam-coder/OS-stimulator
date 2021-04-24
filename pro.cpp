#include <bits/stdc++.h>
#include "pro.h"
#include<stdio.h>
#include<stdlib.h>
//#include<semaphore.h>

#include<iostream>
#define N 1000
#define SIZE 100
using namespace std;

//keeps a track of the information of readers and writers
struct info{
    char type;
    int arrival;
    int burst;
    int index;
};

//semaphore wait
void wait(int *s){
    while(*s<=0);
    (*s)--;
}

//semaphore signal
void signal(int *s){
    (*s)++;
}

//Implementation of the write function
void write(int *mutex){
    wait(mutex);
    //writing
    signal(mutex);
    return ;
}

//Implementation of the read function
void read(int *mutex){
    wait(mutex);
    //reading
    signal(mutex);
    return ;
}

void reader_writer(){
    int i,j,k,num_readers, num_writers,complete=0,t,mutex=1,flag=0,succ_read=0,written=0;
    char ch;
    cout<<"Enter the number of writers and readers: ";
    cin>>num_writers>>num_readers;
    int readers[num_readers][3], writers[num_writers][3];
    struct info arr[num_readers+num_writers];
    //taking the input of the information of writers
    for(i=0;i<num_writers;i++){
        cout<<"Enter the arrival and burst time of writer "<<i<<": ";
        arr[i].type = 'W';
        cin>>arr[i].arrival>>arr[i].burst;
        arr[i].index = i;
    }
    //taking the input of the information of writers
    for(j=0;j<num_readers;j++,i++){
        cout<<"Enter the arrival and burst time of reader "<<j<<": ";
        cin>>arr[i].arrival>>arr[i].burst;
        arr[i].type = 'R';
        arr[i].index = j;
    }
    //sorting the readers and writers depending upon their arrival times
    for(i=0;i<(num_writers + num_readers -1);i++){
        for(j=0;j<(num_writers + num_readers - 1 - i);j++){
            if(arr[j].arrival > arr[j+1].arrival){
                t = arr[j].arrival;
                arr[j].arrival = arr[j+1].arrival;
                arr[j+1].arrival = t;
                t = arr[j].burst;
                arr[j].burst = arr[j+1].burst;
                arr[j+1].burst = t;
                ch = arr[j].type;
                arr[j].type = arr[j+1].type;
                arr[j+1].type = ch;
                t = arr[j].index;
                arr[j].index = arr[j+1].index;
                arr[j+1].index = t;
            }
        }
    }
    i=0;
    j=0;
    while(arr[i].type != 'W' && i<(num_readers+num_writers)){  //finding the writer who arrives first
        i++;
    }
    if(i==(num_readers+num_writers)){
        cout<<"Readers cannot read anything as no writers are there \n";
        return ;
    }
    while(arr[j].type != 'R' && j<(num_readers+num_writers)){   //finding the reader who arrives first
        j++;
    }
    t=arr[0].arrival;
    if(arr[0].type == 'R'){   //if a reader arrives before the 1st writer
        cout<<"A reader has arrived before the first writer. Waiting for writers to start writing\n";
        t=arr[i].arrival;
    }
    while(complete != (num_writers+num_readers)){
        if(arr[i].arrival <= t && i<=j || written==0){  //writing
            written=1;
            cout<<"Writer "<<arr[i].index<<" started writing at t = "<<t<<"\n";
            write(&mutex);
            complete++;
            t+=arr[i].burst;
            i++;
            while(i<(num_writers+num_readers) && arr[i].type != 'W'){
                i++;
            }
        }
        else if((arr[j].arrival <= t) && succ_read!=num_readers && written==1){   //reader is available 
            cout<<"Reader "<<arr[j].index<<" started reading at t = "<<t<<"\n";
            flag=0;
            read(&mutex);
            succ_read++;
            complete++;
            k=j;
            j++;
            while(arr[j].type != 'R' && j<(num_readers+num_writers)){   //finds the reader with the next least arrival time
                j++;
            }
            while(arr[j].arrival <= t+arr[k].burst && succ_read!=num_readers){  //finding all readers that can read along with the reader who is presently reading 
                if(t<arr[j].arrival){
                    t=arr[j].arrival;
                }
                cout<<"Reader "<<arr[j].index<<" started reading at t = "<<t<<"\n";
                flag=1;
                read(&mutex);
                complete++;
                succ_read++;
                k=j;
                j++;
                while(arr[j].type != 'R' && j<(num_readers+num_writers)){
                    j++;    //finds the reader with the next least arrival time
                }
            }
            t += arr[k].burst;
        }
    }
}

//producing a item
void produce(int *empty, int *full, int *mutex){
    wait(mutex);
    wait(empty);   //decreases the number of empty blocks in the buffer
    signal(full);   //Increase the number of filled blocks. This marks the completion of production
    signal(mutex);
}

//consuming a item
void consume(int *empty, int *full, int *mutex){
    wait(mutex);
    wait(full);   //decreases the number of filled blocks in the buffer
    signal(empty);    //Increase the number of empty blocks marking the completion of cosumption
    signal(mutex);
}

//keeps a track of the information of producers and consumers
struct producer_info{
    char type;
    int arrival;
    int index;
};

//keeps a track of the information of philosophers
struct dining_info{
    int arrival;
    int burst;
    int index;
};

//moving the producers or consumers to appropriate positions
int move(struct producer_info *arr, int k, int total){
    int temp1, temp2, j,i;
    char temp3;
    j=k;
    if(arr[k].type == 'P'){   //moving the producers by one position until a consumer is found.
        while(arr[k].type == 'P' && k<total){
            k++;
        }
        if(k==total){
            return -1;
        }
        temp1 = arr[k].arrival;
        temp2 = arr[k].index;
        temp3 = arr[k].type;
        for(i=k;i>j;i--){
            arr[i].arrival = arr[i-1].arrival;
            arr[i].index = arr[i-1].index;
            arr[i].type = arr[i-1].type;
        }
        arr[j].arrival = temp1;
        arr[j].index = temp2;
        arr[j].type = temp3;
    }
    else{    //moving the consumers by one position until a producer is found.
        while(arr[k].type == 'C' && k<(total)){
            k++;
        }
        if(k==total){
            return -1;
        }
        temp1 = arr[k].arrival;
        temp2 = arr[k].index;
        temp3 = arr[k].type;
        for(i=k;i>j;i--){
            arr[i].arrival = arr[i-1].arrival;
            arr[i].index = arr[i-1].index;
            arr[i].type = arr[i-1].type;
        }
        arr[j].arrival = temp1;
        arr[j].index = temp2;
        arr[j].type = temp3;
    }
    return 0;
}

int producer_consumer(){
    int i,j=0,k,n,m,l,buffer,t,complete=0,empty,full,mutex=1,flag=0;
    char ch;
    printf("Enter the buffer size:");
    scanf("%d",&buffer);
    printf("Enter the number of producers and consumers: ");
    scanf("%d%d",&n,&m);
    int prod[n][2], cons[m][2];  //information of producers and consumers
    struct producer_info arr[n+m];
    //Takes the input of the arrival and burst time of producers
    for(i=0,j=0;i<n;i++,j++){
        printf("Enter the arrival and burst time of producer %d: ",i);
        scanf("%d%d",&prod[i][0],&prod[i][1]);
        arr[j].type = 'P';
        arr[j].arrival = prod[i][0];
        arr[j].index = j;
    }
    //Takes the input of the arrival and burst time of consumers
    for(i=0;i<m;i++,j++){
        printf("Enter the arrival and burst time of consumer %d: ",i);
        scanf("%d%d",&cons[i][0],&cons[i][1]);
        arr[j].type = 'C';
        arr[j].arrival = cons[i][0];
        arr[j].index = i;
    }
    //sorting the producers and consumers depending on their arrival times
    for(i=0;i<(m+n-1);i++){
        for(j=0;j<(m+n-1-i);j++){
            if(arr[j].arrival > arr[j+1].arrival){
                t = arr[j].arrival;
                arr[j].arrival = arr[j+1].arrival;
                arr[j+1].arrival = t;
                ch = arr[j].type;
                arr[j].type = arr[j+1].type;
                arr[j+1].type = ch;
                t = arr[j].index;
                arr[j].index = arr[j+1].index;
                arr[j+1].index = t;
            }
        }
    }
    t=arr[0].arrival;   //keeps a track of the current time
    full=0;
    empty=buffer;
    i=0;
    while(arr[i].type != 'P'){   //finds the 1st producer
        i++;
    }
    j=0;
    while(arr[j].type != 'C'){    //finds the 1st consumer
        j++;
    }
    flag=0;
    for(i=0;i<(n+m);i++){
        if(arr[i].arrival >t){   //if no producer/consumer is present, update the current time to the next earliest arrival time
            t=arr[i].arrival;
        }
        if(arr[i].type == 'P'){
            if(full == buffer){   //producer has to be moved as the buffer is full
                cout<<"Buffer limit reached. Producer is waiting for consumers\n";
                k=i;
                flag = move(arr, k, n+m);
                i--;
                if(flag==-1 || i==(n+m-2)){
                    break;
                }
                continue;
            }
            else{   //Producing an item
                cout<<"Producer "<<arr[i].index<<" started producing at time "<<t<<"\n";
                produce(&empty, &full, &mutex);
                complete++;
                t+=prod[arr[i].index][1];
            }
        }
        else{
            if(empty == buffer){    //consumer has to be moved as the buffer is empty
                cout<<"Consumer has arrived before a producer but the buffer is empty\n";
                k=i;
                flag = move(arr, k, n+m);
                i--;
                if(flag==-1 || i==(n+m-2)){
                    break;
                }
                continue;
            }
            else{   //consuming an item
                cout<<"Consumer "<<arr[i].index<<" started consuming at time "<<t<<"\n";
                consume(&empty, &full, &mutex);
                complete++;
                t+=cons[arr[i].index][1];
            }
        }
    }
    return 0;
}

void dine(int *chopsticks, int i, int n){
    if(i!=(n-1)){
        wait(&chopsticks[i%n]);
        wait(&chopsticks[(i+1)%n]);
        //dining
        signal(&chopsticks[i%n]);
        signal(&chopsticks[(i+1)%n]);
    }
    else{
        wait(&chopsticks[(i+1)%n]);
        wait(&chopsticks[i%n]);
        //dining
        signal(&chopsticks[(i+1)%n]);
        signal(&chopsticks[i%n]);
    }
}

int dining_philosophers(){
    int i,j,k,n,complete=0,t;
    cout<<"Enter the number of philosophers: ";
    cin>>n;
    int chopsticks[n],rem_time[n],ongoing[n];
    struct dining_info arr[n];
    for(i=0;i<n;i++){
        cout<<"Enter the arrival and burst time of philosopher "<<i<<" : ";
        cin>>arr[i].arrival>>arr[i].burst;
        arr[i].index = i;
        chopsticks[i]=1;
        rem_time[i]=0;
        ongoing[i]=0;
    }
    for(i=0;i<(n-1);i++){
        for(j=0;j<(n-1-i);j++){
            if(arr[j].arrival > arr[j+1].arrival){
                t = arr[j].arrival;
                arr[j].arrival = arr[j+1].arrival;
                arr[j+1].arrival = t;
                t = arr[j].burst;
                arr[j].burst = arr[j+1].burst;
                arr[j+1].burst = t;
                t = arr[j].index;
                arr[j].index = arr[j+1].index;
                arr[j+1].index = t;
            }
        }
    }
    i=0;
    j=0;
    t=0;//t=arr[i].arrival;
    while(complete != n){
        for(i=0;i<n;i++){
            if(chopsticks[(arr[i].index+1)%n]==1 && chopsticks[(arr[i].index)%n]==1  && arr[i].arrival<=t && ongoing[arr[i].index]==0){
                cout<<"Philosopher "<<arr[i].index<<" has started dining at "<<t<<"\n";
                ongoing[arr[i].index]=1;
                dine(chopsticks, arr[i].index, n);
                complete++;
                rem_time[(arr[i].index+1)%n]=arr[i].burst;
                rem_time[(arr[i].index)%n]=arr[i].burst;
                chopsticks[(arr[i].index+1)%n]=0;
                chopsticks[(arr[i].index)%n]=0;
                //i++;
            }
        }
        t++;
        for(j=0;j<n;j++){
            if(rem_time[j]>0){
                rem_time[j]--;
            }
            if(rem_time[j]==0){
                //ongoing[j]=0;
                chopsticks[j]=1;
            }
            /*if(rem_time[(j+1)%n]==0){
                chopsticks[(j+1)%n]=1;
            }*/
        }
    }
    return 0;
} 

void synchronization(){
    int i,j,k;
    cout<<"\nEnter 1 for reader-writer, 2 for producer-consumer, 3 for dining philosophers and any other number to exit: ";
    cin>>k;
    if(k==1){
        reader_writer();
    }
    else if(k==2){
        j=producer_consumer();
    }
    else if(k==3){
        j=dining_philosophers();
    }
    else{
        cout<<"Please enter 1, 2 or 3\n";
    }
    return ;
}


void swap(int a[], int i, int j)    //To swap numbers
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void sort_bub(int a[], int n)   //Bubble sort
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j])
                swap(a, i, j);
}

void CLOOK()
{

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
    sort_bub(request, n);

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
void CSCAN()
{
    
    int n, numberOfTracks, choice;
    int request[N];
    float avg;
    printf("\n%s\n\n", "------------------CSCAN Disk Scheduling Algorithm------------------");
    
    printf("Enter number of tracks : ");        //Enter total number of tracks on disk
    scanf("%d", &numberOfTracks);

    printf("Enter number of requests : ");       //Enter number of requests
    scanf("%d", &n);

    j1:

    printf("Enter current track position : ");  //Enter starting position
    scanf("%d", &request[0]);

    if (request[0] >= numberOfTracks || request[0] < 0)
    {
        printf("Invalid track....\n");
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
    sort_bub(request, n);

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
    if (request[n - 1] != numberOfTracks)
        printf("Move from %d to %d with Seek %d\n", request[n - 1], numberOfTracks - 1, abs(request[n - 1] - numberOfTracks + 1));

    //Backward movement
    if (pos > 0)
        printf("Move from %d to 0 with Seek %d\n-Move from 0 to %d with Seek %d\n", numberOfTracks - 1, numberOfTracks - 1, request[0], request[0]);
    for (int i = 1; i < pos; i++)
        printf("Move from %d to %d with Seek %d\n", request[i - 1], request[i], abs(request[i - 1] - request[i]));

    ans = numberOfTracks - request[pos] - 1;
    if (pos > 0)
        ans += request[pos - 1] + numberOfTracks - 1; //Total seek time calculation

    //Results

    printf("\nTotal seek time is %d\t", ans);
    avg = ans / (float) n;
    printf("\nAverage seek time is %f\n\n", avg);
}
void FCFS()
{
    
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

    return ;
}
void LOOK()
{
    
    int n, numberOfTracks, choice;
    int request[N];
    float avg;

    printf("\n%s\n\n", "------------------LOOK Disk Scheduling Algorithm------------------");

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
    sort_bub(request, n);

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
        printf("Move from %d to %d with Seek %d\n", request[n - 1], request[pos - 1], abs(request[n - 1] - request[pos - 1]));
    for (int i = pos - 2; i >= 0; i--)
        printf("Move from %d to %d with Seek %d\n", request[i + 1], request[i], abs(request[i + 1] - request[i]));

    ans = request[n - 1] - request[pos];    //Total seek time calculation
    if (pos > 0)
        ans += request[n - 1] - request[0];     //Total seek time calculation
    
    //Results
    printf("\nTotal seek time is %d\t", ans);
    avg = ans / (float) n;
    printf("\nAverage seek time is %f\n\n", avg);
}
void SCAN()
{
   
    int n, numberOfTracks, choice;
    int request[N];
    float avg;
    printf("\n%s\n\n", "------------------SCAN Disk Scheduling Algorithm------------------");
    
    printf("Enter number of tracks : ");        //Enter total number of tracks on disk
    scanf("%d", &numberOfTracks);

    printf("Enter number of requests : ");       //Enter number of requests
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
    sort_bub(request, n);

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
    if (request[n - 1] != numberOfTracks)
        printf("Move from %d to %d with Seek %d\n", request[n - 1], numberOfTracks - 1, abs(request[n - 1] - numberOfTracks + 1));

    //Backward movement
    if (pos > 0)
        printf("Move from %d to %d with Seek %d\n", numberOfTracks - 1, request[pos - 1], abs(numberOfTracks - 1 - request[pos - 1]));
    for (int i = pos - 2; i >= 0; i--)
        printf("Move from %d to %d with Seek %d\n", request[i + 1], request[i], abs(request[i + 1] - request[i]));

    ans = 2 *numberOfTracks - 2 - firstRequest - request[0];    //Total seek time calculation

    //Results
    printf("\nTotal seek time is %d\t", ans);
    avg = ans / (float) n;
    printf("\nAverage seek time is %f\n\n", avg);
}
void SSTF()
{
   

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
    return ;
}

void FCFS_sche()
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
        int smallest;
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
void LJFS()
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
        printf("\n");
    }
    printf("\nGantt chart:\n\n");
    bt[9]=-9999;//burst time 
    int time=0;
    int idt=0;//ideal time 
    int endtime=0;
    int remain=0;//number of remained process
    int finished[10]={0};//initial case
    while(remain!=n)
    {
        int longest=9;
        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && bt[i]>bt[longest] && finished[i]==0)
            {
                longest=i;
            }
        }
        if(longest==9)
        {
            idt++;
            printf("|%d| IDLE ",time);
            time+=1;

        }
        else
        {
            printf("|%d| P%d ",time,longest+1);
            remain++;
            finished[longest]=1;
            endtime=time+bt[longest];
            tat[longest]=endtime-at[longest];
            wt[longest]=endtime-at[longest]-bt[longest];
            time+=bt[longest];
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

    printf("\nAverage turn around time=%f\n",avgtat/n);
    printf("Average waiting time=%f\n",avgwt/n);
}

struct lrtf
{
    int AT;
    int BT;
    int CT;
    int m;
    int TAT;
    int WT;
    bool completed;
    int RT;

};
bool comp(const lrtf &a,const lrtf &b)
{
    return a.AT<b.AT;
}
void LRTF()
{
    cout<<"Enter no of processes"<<endl;
    int n,a,b;
    cin>>n;
    string output="";
    vector<struct lrtf>p(n);

    for(int i=0;i<n;i++)
    {
        cout<<"Enter Arrival time process "<<i+1<<endl;
        cin>>a;
        cout<<"Enter Brust time process "<<i+1<<endl;
        cin>>b;
        p[i].m=i+1;
        p[i].AT=a;
        p[i].BT=b;
        p[i].completed=false;
        p[i].RT=p[i].BT;


    }
    int t=0;
    int k;
    int done=n;
    int longest;
    float avgtat=0,avgwt=0;
    // sort(p.begin(),p.end(),comp);
    cout<<"P.No  AT   BT   CT   TAT   WT  "<<endl;
    while(done!=0)
    {
        k=-1;
        longest=INT_MIN;

        for(int i=0;i<n;i++)
        {

            if(p[i].completed==false &&p[i].AT<=t)
            {

                if(p[i].RT>longest)
                {
                    longest=p[i].RT;
                    k=i;

                }
                else if(p[i].RT==longest)
                {
                    if(p[i].AT<p[k].AT)
                    {
                        k=i;
                    }
                }


            }
        }
        if(k==-1)
        {
            output+="|"+to_string(t)+" IDLE "+to_string(t+1)+" | ";
            t++;
        }
        else
        {

                output+="|"+to_string(t)+" P"+to_string(p[k].m)+" "+to_string(t+1)+" | ";
                p[k].RT--;

            if(p[k].RT==0)
            {
                p[k].CT=t+1;
                p[k].completed=true;

                p[k].TAT=p[k].CT-p[k].AT;
                p[k].WT=p[k].TAT-p[k].BT;
                done--;
                avgtat+=p[k].TAT;
                avgwt+=p[k].WT;

                cout<<p[k].m<<"     "<<p[k].AT<<"    "<<p[k].BT<<"    "<<p[k].CT<<"    "<<p[k].TAT<<"    "<<p[k].WT<<endl;



            }
            t++;




        }

    }

    cout<<"Average Turnaround Time \t"<<avgtat/n<<endl;
    cout<<"Average Waiting Time\t"<<avgwt/n<<endl;
    cout<<"Gantt Chart\t"<<endl<<output<<endl;
}
void RR()
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
    return ;
}

void SJFS()
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
    int endtime=0;
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
// struct srtf
// {
//     int AT;
//     int BT;
//     int CT;
//     int m;
//     int TAT;
//     int WT;
//     bool completed;
//     int RT;

// };

void SRTF()
{

            struct srtf
{
    int AT;
    int BT;
    int CT;
    int m;
    int TAT;
    int WT;
    bool completed;
    int RT;
};
    cout << "Enter no of processes" << endl;
    int n, a, b;
    cin >> n;
    string output = "";
    vector<struct srtf> p(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival time of process " << i + 1 << endl;
        cin >> a;
        cout << "Enter the burst time of process " << i + 1 << endl;
        cin >> b;
        p[i].m = i + 1;
        p[i].AT = a;
        p[i].BT = b;
        p[i].completed = false;
        p[i].RT = p[i].BT;
    }
    int t = 0;
    int k;
    int done = n;
    int shortest;
    float avgtat = 0, avgwt = 0;
    sort(p.begin(), p.end(), [](const srtf& a, const srtf& b) -> bool
    {
        return a.AT > b.AT;
    });
    cout << "P.No  AT   BT   CT   TAT   WT  " << endl;
    while (done != 0)
    {
        k = -1;
        shortest = INT_MAX;

        for (int i = 0; i < n; i++)
        {

            if (p[i].completed == false && p[i].AT <= t)
            {

                if (p[i].RT < shortest)
                {
                    shortest = p[i].RT;
                    k = i;
                }
                else if (p[i].RT == shortest)
                {
                    if (p[i].AT < p[k].AT)
                    {
                        k = i;
                    }
                }
            }
        }
        if (k == -1)
        {
            output += "|" + to_string(t) + " IDLE " + to_string(t + 1) + " | ";
            t++;
        }
        else
        {

            output += "|" + to_string(t) + " P" + to_string(p[k].m) + " " + to_string(t + 1) + " | ";
            p[k].RT--;

            if (p[k].RT == 0)
            {
                p[k].CT = t + 1;
                p[k].completed = true;

                p[k].TAT = p[k].CT - p[k].AT;
                p[k].WT = p[k].TAT - p[k].BT;
                done--;
                avgtat += p[k].TAT;
                avgwt += p[k].WT;

                cout << p[k].m << "     " << p[k].AT << "    " << p[k].BT << "    " << p[k].CT << "    " << p[k].TAT << "    " << p[k].WT << endl;
            }
            t++;
        }
    }
    cout << "Average Turnaround Time\t" << avgtat / n << endl;
    cout << "Average Waiting Time\t" << avgwt / n << endl;
    cout << "Gantt Chart" << endl
         << output << endl;
    return ;

}

//inserting a process according to the first fit algorithm
void insert_process_ff(int index, int process_size, vector<int> &partition, int *num_occupied_process, int *num_partitions, int *accomodated, int *n){
    int i,j,flag=0;
    for(i=0;i<*num_partitions;i++){
        if(process_size <= partition[i] && accomodated[i]==-1){  //occupy the first unoccupied partition with enough size
            partition[i] -= process_size;
            accomodated[i]=index;
            (*n)-=process_size;
            (*num_occupied_process)++;
            cout<<"Process has been accomodated in partition "<<i<<"\n";
            return ;
        }
        if(process_size <= partition[i] && accomodated[i]>=0){
            flag=1;  //case for internal fragmentation
        }
    }
    if(flag==1){
        cout<<"Process cannot be accomodated due to internal fragmentation\n";   //if an occupied partition has enough space for a process to accomodate, its a case of internal fragmentation
    }
    else if(process_size <= *n){
        cout<<"Process cannot be accomodated due to external fragmentation\n";   //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    }
    else{
        cout<<"No enough space\n";
    }
    return ;
}

//inserting a process according to the best fit algorithm
void insert_process_bf(int index, int process_size, vector<int> &partition, int *num_occupied_process, int *num_partitions, int *accomodated, int*n){
    int i,j,best_index=-1,flag=1;
    for(i=0;i<(*num_partitions);i++){ 
        cout<<"in";
        if(process_size <= partition[i] && accomodated[i]==-1 && (best_index==-1 || partition[i]<(partition[best_index]))){   //find the unoccupied partition better than the best partition found so far
            best_index=i;
        }
        if(process_size <= partition[i] && accomodated[i]>=0){
            flag=1;  //internal fragmentation if best index is -1 at the end
        }
    }
    if(best_index != -1){
        partition[best_index] = partition[best_index]-process_size;   //free space
        accomodated[best_index] = index;
        (*num_occupied_process)++;
        (*n)-=process_size;
        cout<<"Process has been accomodated in partition "<<best_index<<"\n";
        return ;
    }
    if(flag==1){
        cout<<"Process cannot be accomodated due to internal fragmentation\n";   //if an occupied partition has enough space for a process to accomodate, its a case of internal fragmentation
    }
    else if(process_size <= *n){
        cout<<"Process cannot be accomodated due to external fragmentation\n";   //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    }
    else{
        cout<<"No enough space\n";
    }
    return ;
}

//inserting a process according to the worst fit algorithm
void insert_process_wf(int index, int process_size, vector<int> &partition, int *num_occupied_process, int *num_partitions, int *accomodated, int *n){
    int i,j,best_index=-1,worst_index=-1;
    for(i=0;i<(*num_partitions);i++){
        if(process_size <= partition[i] && accomodated[i]==-1 && (worst_index==-1 || partition[i]>(partition[worst_index]))){    //find the unoccupied partition larger than the worst partition found so far
            worst_index=i;
        }
    }
    if(worst_index != -1){
        partition[worst_index] -= process_size;    //process allocated to the worst (largest) partition i
        accomodated[worst_index] = index;
        (*num_occupied_process)++;
        (*n)-=process_size;
        cout<<"Process has been accomodated in partition "<<worst_index<<"\n";
        return ;
    }
    cout<<"Process cannot be accomodated due to external fragmentation\n";    //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    return ;
}

void mft_main(){
    int i,j,k,l,n,s=1,flag=0,total_size,num_process,num_occupied_process=0,m=0,count=0,index=0,process_size,num_partitions=0,del_index,fit_type=0;
    vector<int> partition;
    int process[1001];
    cout<<"Enter 1 for first fit, 2 for best fit and 3 for worst fit: ";
    cin>>fit_type;
    cout<<"Enter the total size: ";
    cin>>total_size;
    cout<<"Total number of partitions: ";
    cin>>num_partitions;
    n = total_size;
    int occupied[num_partitions];
    for(i=0;i<num_partitions;i++){
        cout<<"Size of partition "<<i<<": ";
        cin>>k;
        partition.push_back(k);
        occupied[i]=-1;
    }
    /*cout<<"Total number of processes: ";
    cin>>num_process;
    for(i=0;i<num_process;i++){
        cout<<"Size of process "<<i+1<<": ";
        cin>>k;
        process.push_back(k);
    }*/
    for(i=0;i<num_partitions;i++){
        k = partition[i];
        if(n-k<0){
            cout<<"Partition "<<i<<" cannot be made due to insufficient space\n";
            occupied[i]=-2; //indicates that it should not be given to anyone
        }
        else{
            n-=k;
        }
    }
    n = total_size;
    while(true){
        cout<<"\nEnter 1 to add a process, 2 to delete a process and 3 to print details of process and other number to exit: ";
        cin>>k;
        if(k==1){
            cout<<"Enter the process id: ";
            cin>>index;
            cout<<"Enter the size of process "<<index<<": ";
            cin>>process_size;
            process[index]=process_size;
                //call the insert function depending on the type of fit chosen previously
                if(fit_type==1){
                    insert_process_ff(index, process_size, partition, &num_occupied_process, &num_partitions, occupied, &n);
                }
                else if(fit_type==2){
                    insert_process_bf(index, process_size, partition, &num_occupied_process, &num_partitions, occupied, &n);
                }
                else{
                    insert_process_wf(index, process_size, partition, &num_occupied_process, &num_partitions, occupied, &n);
                }
        }
        //deleting the process
        else if(k==2){
            cout<<"Enter the index of process to be deleted: ";
            cin>>del_index;
            flag=0;
            for(j=0;j<num_partitions;j++){
                if(occupied[j]==del_index){   //finding the partition accomodating the process with index del_index
                    occupied[j]=-1;
                    partition[j] += process[del_index];  
                    n += process[del_index];   //available space increases by the process size of the process deleted now
                    flag=1;
                    break;
                }
            }
            if(flag==0){    //if theres no process with the given process id
                cout<<"Process cannot be removed\n";
            }
        }
        //displaying the information of partitions and processes
        else if(k==3){
            cout<<"Total Space remaining: "<<n<<"KB\n";
            for(j=0;j<num_partitions;j++){
                if(occupied[j]>=0){
                    cout<<"Partition "<<j<<" has P"<<occupied[j]<<" with size "<<process[occupied[j]]<<"KB and internal fragmentation "<<partition[j]<<"\n";
                }
                else if(occupied[j]==-1){   //free space has accomodated[j] = -1
                    cout<<"Partition "<<j<<" is empty with size "<<partition[j]<<"KB free space\n";    
                }
            }
        }
        else{   //end of menu driven program
            break;
        }
    }
}
void insert_process_ff1(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int *n){
    int i,j;
    for(i=0;i<*num_partitions;i++){
        if(process_size <= memory[i] && accomodated[i]==-1){  //occupy the first unoccupied partition with enough size
            if(process_size == memory[i]){  //if process size is same as partition size, just allocate the process to the partition
                memory[i]=process_size;
                accomodated[i] = index;
            }
            else{   //if process size is less than that of the partition, allocate the process and make a new partition with the remaining space
                for(j=*num_partitions;j>i;j--){   //move partitions by one position
                    memory[j] = memory[j-1];
                    accomodated[j] = accomodated[j-1];
                }
                memory[i+1] = memory[i+1]-process_size;   //free space
                accomodated[i+1] = -1;
                memory[i]=process_size;    
                accomodated[i] = index;   //process allocated to partition i
                (*num_partitions)++;
            }
            (*n)-=process_size;
            return ;
        }
    }
    cout<<"Process cannot be accomodated due to external fragmentation\n";   //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    return ;
}

//inserting a process according to the best fit algorithm
void insert_process_bf1(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int*n){
    int i,j,best_index=-1;
    for(i=0;i<(*num_partitions);i++){ 
        if(process_size <= memory[i] && accomodated[i]==-1 && (best_index==-1 || memory[i]<(memory[best_index]))){   //find the unoccupied partition better than the best partition found so far
            best_index=i;
        }
    }
    if(best_index != -1){
        if(process_size == memory[best_index]){   //if process size is same as partition size, just allocate the process to the partition
            memory[best_index]=process_size;
            accomodated[best_index] = index;
        }
        else{   //if process size is less than that of the partition, allocate the process and make a new partition with the remaining space
            for(j=*num_partitions;j>best_index;j--){  //move partitions by one position
                memory[j] = memory[j-1];
                accomodated[j] = accomodated[j-1];
            }
            memory[best_index+1] = memory[best_index+1]-process_size;   //free space
            accomodated[best_index+1] = -1;
            memory[best_index]=process_size;   
            accomodated[best_index] = index;    //process allocated to the best partition i
            (*num_partitions)++;
        }
        (*n)-=process_size;
        return ;
    }
    cout<<"Process cannot be accomodated due to external fragmentation\n";   //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    return ;
}

//inserting a process according to the worst fit algorithm
void insert_process_wf1(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int *n){
    int i,j,best_index=-1,worst_index=-1;
    for(i=0;i<(*num_partitions);i++){
        if(process_size <= memory[i] && accomodated[i]==-1 && (worst_index==-1 || memory[i]>(memory[worst_index]))){    //find the unoccupied partition larger than the worst partition found so far
            worst_index=i;
        }
    }
    if(worst_index != -1){
        if(process_size == memory[worst_index]){   //if process size is same as partition size, just allocate the process to the partition
            memory[worst_index]=process_size;
            accomodated[worst_index] = index;
        }
        else{   //if process size is less than that of the partition, allocate the process and make a new partition with the remaining space
            for(j=*num_partitions;j>worst_index;j--){   //move partitions by one position
                memory[j] = memory[j-1];
                accomodated[j] = accomodated[j-1];
            }
            memory[worst_index+1] = memory[worst_index+1]-process_size;    //free space
            accomodated[worst_index+1] = -1;
            memory[worst_index]=process_size;    //process allocated to the worst (largest) partition i
            accomodated[worst_index] = index;
            (*num_partitions)++;
        }
        (*n)-=process_size;
        return ;
    }
    cout<<"Process cannot be accomodated due to external fragmentation\n";    //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    return ;
}

void mvt(){
    int i,j,k,l,s=1,flag=0,total_size,num_process,n,m=0,count=0,index=0,process_size,num_partitions=0,del_index,fit_type=0;
    int process[1001];
    cout<<"Total size: ";
    cin>>total_size;
    int memory[total_size];
    memory[0] = total_size;
    num_partitions=1;
    cout<<"Enter 1 for first fit, 2 for best fit and 3 for worst fit: ";
    cin>>fit_type;
    int accomodated[total_size]={-1};
    n=total_size;
    while(true){
        cout<<"\nEnter 1 to add a process, 2 to delete a process and 3 to print details of process and other number to exit: ";
        cin>>k;
        if(k==1){
            cout<<"Enter the process id: ";
            cin>>index;
            cout<<"Enter the size of process "<<index<<": ";
            cin>>process_size;
            if(process_size<=n){
                process[index]=process_size;
                //call the insert function depending on the type of fit chosen previously
                if(fit_type==1){
                    insert_process_ff1(index, process_size, memory, &num_partitions, accomodated, &n);
                }
                else if(fit_type==2){
                    insert_process_bf1(index, process_size, memory, &num_partitions, accomodated, &n);
                }
                else{
                    insert_process_wf1(index, process_size, memory, &num_partitions, accomodated, &n);
                }
            }
            else{
                cout<<"Process cannot be accomodated as only "<<n<<"KB is remaining\n";   //if total available space is less than process size
            }
        }
        //deleting the process
        else if(k==2){
            cout<<"Enter the index of process to be deleted: ";
            cin>>del_index;
            flag=0;
            for(j=0;j<num_partitions;j++){
                if(accomodated[j]==del_index){   //finding the partition accomodating the process with index del_index
                    accomodated[j]=-1;
                    memory[j]=process[del_index];  
                    if(j-1>=0 && accomodated[j-1]==-1){   //if partiton which was made empty and its previous partition are empty, combine them
                        memory[j-1]+=memory[j];
                        for(l=j;l<(num_partitions-1);l++){
                            memory[l]=memory[l+1];
                            accomodated[l]=accomodated[l+1];
                        }
                        (num_partitions)--;
                        j--;
                    }
                    if(accomodated[j+1]==-1){    //if partiton which was made empty and its next partition are empty, combine them
                        memory[j]+=memory[j+1];
                        for(l=j+1;l<(num_partitions-1);l++){
                            memory[l]=memory[l+1];
                            accomodated[l]=accomodated[l+1];
                        }
                        (num_partitions)--;
                    }
                    n+=process[del_index];   //available space increases by the process size of the process deleted now
                    flag=1;
                    break;
                }
            }
            if(flag==0){    //if theres no process with the given process id
                cout<<"Process cannot be removed\n";
            }
        }
        //displaying the information of partitions and processes
        else if(k==3){
            cout<<"Total Space remaining: "<<n<<"KB\n";
            for(j=0;j<num_partitions;j++){
                if(accomodated[j]>=0){
                    cout<<"Partition "<<j+1<<" has P"<<accomodated[j]<<" with size "<<process[accomodated[j]]<<"KB\n";
                }
                else{   //free space has accomodated[j] = -1
                    cout<<"Partition "<<j+1<<" is empty with size "<<memory[j]<<"KB free space\n";    
                }
            }
        }
        else{   //end of menu driven program
            break;
        }
    }
    return ;
}
int QUEUE[SIZE];
int matrix[10][SIZE]; //atmost 10 number of frames
int string1[SIZE];
int counter[SIZE];
int front = -1;
int rear = -1;

//this is for LRU and MRU
struct node{
    int data;
    int count_;
};
typedef struct node NODE;
int page_fault=0;

// node for storing the data pagetable
struct FIFO_node{
    int data;
};
typedef struct FIFO_node F_NODE;
int page_replacement();

//The next three structs are for paging with offset
//page table
struct pageTable{
    int pageNum;
    int p_flag;
    int offset;
};
// disk memory
struct VirMemory{ //ignore the name virmemory
    int process_id;
};
// physical memory
struct phyMemory{
    int frame_num;
    int page_num;
};



// queue is used in FIFO page replacement.
void qinsert(int data, int size){
    if(rear==size-1){
        printf("Queue is overflow\n");
        system("PAUSE");
        return;
    }
    ++rear;
    if(rear==0)
        front=0;
    QUEUE[rear]=data;
    return;
}
int qdelete()
{
    int data;
    if(rear==-1){
        printf("Queue is Underflow\n");
        system("PAUSE");
        return -1;
    }
    data = QUEUE[front];
    int i;
    for(i=0;i<rear;i++){
        QUEUE[i]=QUEUE[i+1];
    }
    --rear;
    if(rear==-1)
        front=-1;
    return data;
}

void print_chart(int matrix_t[][100], int string_t[],int number_f,int string_count){
    int i, j, k;
    for(i=0;i<string_count+1;i++){
        matrix[0][i]=string1[i];
    }
    for(i=0;i<1;i++){
        for(j=0;j<string_count;j++){
            printf("---");
        }
    }
    printf("\n");
    for(i=0;i<1;i++){
        for(j=0;j<string_count;j++){
            printf(" %d ",matrix[i][j]);
        }
    }
    printf("\n");
    for(i=0;i<1;i++){
        for(j=0;j<string_count;j++){
            printf("---");
        }
    }
    printf("\n");
    for(i=1;i<number_f+1;i++){
        for(j = 0;j<string_count;j++){
            if(matrix[i][j]==0 || matrix[i][j]==-1){
                printf("   ");
            }
            else{
                printf(" %d ",matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("Number of strings entered:%d\n",string_count);
    printf("\nTotal number of page faults : %d\n",page_fault);
    printf("\npage fault ratio : %f\n\n",(float)(page_fault)/(string_count));
}

// fifo replacement policy
int fifo_replacement()
{
    int row=0,column=0;
    int circ_row=1;
    int frame_count,choice;
    printf("Enter the number of frames : ");
    scanf("%d",&frame_count);
    QUEUE[frame_count];
    matrix[frame_count+1][SIZE];
    NODE pagetable[frame_count];
    int i,j,page_value,poped;
    int string_count=0;
    for(i=0;i<frame_count;i++){
        pagetable[i].data=-1;
    }
    while(1){
        end_fifo:
        printf("1. Add pages into frame\n");
        printf("2. Display\n");
        printf("3. Exit\n");
        printf("Enter the choice:\n");
        scanf("%d",&choice);
        switch (choice){
        case 1:{
                printf("Enter the page : ");
                scanf("%d",&page_value);
                // case 1 for searching the data we in the table
                for(i=0;i<frame_count;i++){
                    if(pagetable[i].data==page_value){
                        printf("\nP%d is already present in F%d\n",page_value,i);
                        string1[string_count++]=page_value;
                        row=0;
                        for(j=1;j<frame_count+1;j++){
                            matrix[j][column]=pagetable[j-1].data;
                        }
                        column++;
                        goto end_fifo;
                    }
                }
                // case 2 for accomodating
                for(i=0;i<frame_count;i++){
                    matrix[++row][column]=pagetable[i].data;
                    if(pagetable[i].data==-1){
                        printf("\nP%d got accomodated in F%d\n",page_value,i);
                        pagetable[i].data=page_value;
                        matrix[circ_row][column++]=page_value;
                        circ_row=(circ_row+1)%(frame_count+1);
                        if(circ_row==0){
                            circ_row=1;
                        }
                        qinsert(page_value,frame_count);
                        string1[string_count++]=page_value;
                        row=0;
                        page_fault++;
                        goto end_fifo;
                    }
                }
                // case 3 for replacing
                poped=qdelete();
                // printf("\npoped\n");
                for(i=0;i<frame_count;i++){
                    if(pagetable[i].data==poped){
                        printf("\nP%d got accomodated by replacing P%d in F%d\n",page_value,poped,i);
                        pagetable[i].data=page_value;
                        matrix[circ_row][column++]=page_value;
                        circ_row=(circ_row+1)%(frame_count+1);
                        qinsert(page_value,frame_count);
                        string1[string_count++]=page_value;
                        page_fault++;
                        row=0;
                        break;                        
                    }
                }   
            break;
        }
        case 2:{
                print_chart(matrix,string1,frame_count,string_count);
                break;
        }
        case 3:{
            // give the global vars original value again
            front = -1;
            rear = -1;
            page_fault =0;
            return 0;
            // page_replacement();
            // return EXIT_SUCCESS;
            break;
        }
        default:
            printf("Invalid option\n");
            break;
        }
    }
}

// LRU _ MRU Function
int lru_mru_replacement(int function) // function decides if its LRU or MRU
{
    int row=0,column=0;
    int circ_row=1;
    int frame_count,choice,low;
    printf("Enter the number of frames : ");
    scanf("%d",&frame_count);
    matrix[frame_count+1][SIZE];
    NODE pagetable[frame_count];
    int i,j,page_value,poped;
    int string_count=0;
    int time=0;
    for(i=0;i<frame_count;i++){
        pagetable[i].data=-1;
    }
    while(1){
        end_lru_mru:
        printf("1. Add pages into frame\n");
        printf("2. Display\n");
        printf("3. Exit\n");
        printf("Enter the choice:\n");
        scanf("%d",&choice);
        switch (choice){
        case 1:{
                printf("Enter the page : ");
                scanf("%d",&page_value);

                for(i=0;i<frame_count;i++){
                    if(pagetable[i].data==page_value){
                        printf("\nP%d is already present in F%d\n",page_value,i);
                        pagetable[i].count_=time;
                        time++;
                        string1[string_count++]=page_value;
                        row=0;
                        for(j=1;j<frame_count+1;j++){
                            matrix[j][column]=pagetable[j-1].data;
                        }
                        column++;
                        goto end_lru_mru;
                    }
                }

                for(i=0;i<frame_count;i++){
                    matrix[++row][column]=pagetable[i].data;
                    if(pagetable[i].data==-1){
                        printf("\nP%d got accomodated in F%d\n",page_value,i);
                        pagetable[i].data=page_value;
                        pagetable[i].count_=time;
                        time++;
                        matrix[circ_row][column++]=page_value;
                        circ_row=(circ_row+1)%(frame_count+1);
                        if(circ_row==0){
                            circ_row=1;
                        }
                        string1[string_count++]=page_value;
                        row=0;
                        page_fault++;
                        goto end_lru_mru;
                    }
                }
                if(function == 2) // from the choice its LRU
                {
                    low=pagetable[0].count_;
                    poped=pagetable[0].data;
                    for(i=0;i<frame_count;i++){
                        if(pagetable[i].count_<low){
                            low = pagetable[i].count_;
                            poped = pagetable[i].data;
                        }
                    }
                }
                else // it will be MRU
                {
                    {
                    low=pagetable[0].count_; // here low act as high, pickes the process with max count= Most recent
                    poped=pagetable[0].data;
                    for(i=0;i<frame_count;i++){
                        if(pagetable[i].count_>low){
                            low = pagetable[i].count_;
                            poped = pagetable[i].data;
                        }
                    }
                }
                }
                for(i=0;i<frame_count;i++){
                    if(pagetable[i].data==poped){
                        printf("\nP%d got accomodated by replacing P%d in F%d\n",page_value,poped,i);
                        pagetable[i].data=page_value;
                        pagetable[i].count_=time;
                        time++;
                        matrix[i+1][column++]=page_value;
                        circ_row=(circ_row+1)%(frame_count+1);
                        string1[string_count++]=page_value;
                        page_fault++;
                        row=0;
                        break;
                    }
                }   
            break;
        }
        case 2:{
            print_chart(matrix,string1,frame_count,string_count);
            
            break;
        }
        case 3:{
            //give the global vars the default values
            front = -1;
            rear = -1;
            page_fault = 0;
            return 0;
            // page_replacement();
            // return EXIT_SUCCESS;
            break;
        }
        default:
            printf("Invalid Choice\n");
            break;
        }
    }
    return 0;
}


// optimal page replacement
int optimal_replacement()
{
    int row=0,column=0;
    int circ_row=1;
    int frame_count,choice,low;
    printf("Enter the number of frames : ");
    scanf("%d",&frame_count);
    int flag1,flag2;
    int temp[frame_count+1];
    int frames[20];
    matrix[frame_count+1][SIZE];
    int i,j,page_value,poped,pos,max,flag3;
    int string_count=0;
    int time=0;
    while(1){
        end:
        printf("1. Enter the strings\n");
        printf("2. Display and exit\n");
        printf("Enter the choice:\n");
        scanf("%d",&choice);
        switch (choice){
        case 1:{
                    printf("Enter the number of strings : ");
                    // scanf("%d",&page_value);
                    scanf("%d",&string_count);
                                
                    printf("Enter the page strings: ");
                    for(i = 0; i < string_count; ++i){
                        scanf("%d", &string1[i]);
                    }
                    for(i = 0; i <  frame_count; ++i){
                        frames[i] = -1;
                    }
                    for(i = 0; i <  string_count; ++i){
                        flag1 = flag2 = 0;
                        for(j = 0; j <  frame_count; ++j){
                            if(frames[j] == string1[i]){
                                flag1 = flag2 = 1;
                                break;
                            }
                        }
                        if(flag1 == 0){
                            for(j = 0; j <  frame_count; ++j){
                                if(frames[j] == -1){
                                    page_fault++;
                                    frames[j] = string1[i];
                                    flag2 = 1;
                                    break;
                                }
                            }    
                        }
                        if(flag2 == 0){
                            flag3 =0;
                            for(j = 0; j < frame_count; ++j){
                                temp[j] = -1;
                                for(int k = i + 1; k < string_count; ++k){
                                    if(frames[j] == string1[k]){
                                        temp[j] = k;
                                        break;
                                    }
                                }
                            }
                            for(j = 0; j < frame_count; ++j){
                                if(temp[j] == -1){
                                    pos = j;
                                    flag3 = 1;
                                    break;
                                }
                            }
                            if(flag3 ==0){
                                max = temp[0];
                                pos = 0; 
                                for(j = 1; j < frame_count; ++j){
                                    if(temp[j] > max){
                                        max = temp[j];
                                        pos = j;
                                    }
                                }            	
                            }
                            frames[pos] = string1[i];
                            page_fault++;
                        }
                        // printf("\n");
                        for(j = 0; j < frame_count; ++j){
                            if(circ_row==0){
                                circ_row++;
                            }
                            matrix[circ_row][column]=frames[j];
                            circ_row=(circ_row+1)%(frame_count+1);
                        }
                        column++;
                    }
                printf("\nPress 2 to display and exit!\n");
            break;
        }
        case 2:{
            print_chart(matrix,string1,frame_count,string_count);
            // set tthe globals to default vals
            front = -1;
            rear = -1;
            page_fault = 0;
            return 0;
            // page_replacement();
            break;
        }
        default:
            printf("Invalid Option\n");
            break;
        }
    }
    return 0;
}

int fifo_offset()
{
    int size_vm,size_pm,size_page;
    
    printf("Enter the size of Virtual Memory : ");
    scanf("%d",&size_vm);    
    printf("Enter the size of Physical Memory : ");
    scanf("%d",&size_pm);    
    printf("Enter the size each page : ");
    scanf("%d",&size_page);

    int num_vm = size_vm/size_page;
    int num_pm = size_pm/size_page;

    struct pageTable ptable[num_vm];    //1
    struct phyMemory physicalM[num_pm]; //2
    struct VirMemory VirtualM[num_vm];  //3 // disk memeory

    QUEUE[num_pm];

    printf("Num of Pages in Virtual Memory : %d\n",num_vm);
    printf("Num of Pages in Physical Memory : %d\n",num_pm);

    int i,j,k;
    int page_fault = 0;
    int string_count = 0;
    // printf("Enter the processes in Virtual Memory : \n");
    for(i=0;i<num_vm;i++){
        // printf("Enter the process number/id at %d: ",i+1);
        // scanf("%d",&VirtualM[i].process_id);
        VirtualM[i].process_id=i;

    }
    for(i=0;i<num_vm;i++){
        ptable[i].p_flag=0;
        ptable[i].pageNum=-1;
    }
    for(i=0;i<num_pm;i++){
        physicalM[i].page_num=-1;
        physicalM[i].frame_num=i;
    }   
//   ptable;
    int choice;
    int page_number,Word_offset,poped;
    while (1){
endit:
        printf("\n1.Enter the Virtual Address\n");
        printf("2.Display\n");
        printf("3.Exit\n");
        printf("Enter the choice : ");
        scanf("%d",&choice);
        switch (choice){       
        case 1:{
                printf("format: pageNumber|Word_offset\n");
                scanf("%d %d",&page_number,&Word_offset);
                if(Word_offset>4096 || Word_offset<0){
                    printf("Word offset lies between 0 to 4096\n");
                    goto endit;
                }

                // pagehit
                for(i=0;i<num_pm;i++){
                    if(physicalM[i].page_num==page_number){
                        printf("Phy Address for the above Virtual Address\n");
                        printf("%d %d",physicalM[i].frame_num,Word_offset);
                        ptable[page_number].pageNum=physicalM[i].frame_num;
                        ptable[page_number].offset;
                        string_count++;
                        // ptable[page_number].p_flag=1;                    
                        goto endit;    
                    }
                }


                //new_input;
                for(i=0;i<num_pm;i++){
                    if(physicalM[i].page_num==-1){
                        physicalM[i].page_num = page_number;
                        printf("P%d NOt present in PM, and is accomodated at in Frame F%d\n",page_number,(physicalM[i].frame_num));
                        ptable[page_number].pageNum=physicalM[i].frame_num;
                        ptable[page_number].p_flag=1;                    
                        ptable[page_number].offset;
                        // ptable[poped].pageNum=-1;
                        page_fault++;
                        string_count++;
                        physicalM[i].page_num=page_number;
                        qinsert(page_number,num_pm);
                        goto endit;
                    }
                }
                poped = qdelete();
                // replace
                for (i=0;i<num_pm;i++){
                    if(physicalM[i].page_num == poped){
                        printf("P%d is not presentin PM. Accomodated at Frame F%d by replacing P%d\n",page_number,physicalM[i].frame_num,poped);
                        physicalM[i].page_num = page_number;
                        ptable[page_number].pageNum=physicalM[i].frame_num;
                        ptable[page_number].p_flag=1;                    
                        ptable[page_number].offset;
                        ptable[poped].pageNum=-1;
                        page_fault++;
                        string_count++;
                        qinsert(page_number,num_pm);
                        goto endit;
                    }
                }
            break;
        }
        case 2:{
            printf("\nPage Table\n");
            for(i=0;i<num_vm;i++){
                if(ptable[i].pageNum != -1){
                    // if(ptable[i].pageNum==-1){}
                    printf("%d. %d\n",i,ptable[i].pageNum);
                }
                else{
                    printf("%d.\n",i);
                }
            }
            printf("\nPhysical Memory\n");
            for(i=0;i<num_pm;i++){
                if(physicalM[i].page_num!=-1){
                    printf("%d. %d\n",i,physicalM[i].page_num);
                }
                else
                    printf("\n");
            }
            printf("\nDisk\n");
            for(i=0;i<num_vm;i++){
                printf("%d. %d\n",i,VirtualM[i].process_id);
            }
            printf("\ntotal number of page faults : %d\n",page_fault);
            printf("total number of strings : %d\n",string_count);
            printf("Page fault ratio : %f\n",(float)page_fault/(float)string_count);
            break;
        }
        case 3: {
            //default values
            front = -1;
            rear = -1;
            page_fault=0;
            return 0;
            // page_replacement();
            break;
            // return EXIT_SUCCESS;
        }
        default:{
            printf("Invalid Option\n");
            break;
        }
        }
    }
    
    // return 0;
}




//main page replacement function that calls rest
int page_replacement()
{   
    int key_choice;
    while(1){
        printf("Press 1. FIFO\n");
        printf("Press 2. LRU\n");
        printf("Press 3. MRU\n");
        printf("Press 4. Optimal\n");
        printf("Press 5. Paging with offset using FIFO replacement\n");
        printf("Press 6. Exit\n");
        scanf("%d",&key_choice);
        switch(key_choice){
            case 1:{
                fifo_replacement();
                break;
            }
            case 2:{
                lru_mru_replacement(key_choice);
                break;
            }
            case 3:{
                lru_mru_replacement(key_choice);
                break;
            }
            case 4:{
                optimal_replacement();
                break;
            }
            case 5:{
                fifo_offset();
                break;
            }
            case 6:{
                // here return to the calling function(main menu driven)
                // goto exit_now;
                return 0; // remove later
                break;
            }
            default:{
                printf("Invalid Option\n");
                break;
            }
        }
    }
    return 0;
}
void pg_rep(){
    if(page_replacement()==0)
        return ;
    // exit_now:
    return ;
}
void prem_prio_sche(){
    int i,j,k,t,ti,n,l,min,index,flag,complete=0;
    float avg_tat=0,avg_wt=0;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    if(n<=0){
        printf("Enter a positive number\n");
        return ;
    }
    int a[n],b[n],tat[n],ind[n],wt[n],rem[n],comp[n], priority[n];
    //tat is turn around time and wt is the waiting time
    int time[10000];
    for(i=0;i<10000;i++)
    {
    	time[i]=-1;
	}
    for(i=0;i<n;i++){
        printf("\nEnter the arrival ,burst time and priority of process %d: ",i+1);
        scanf("%d%d%d",&a[i],&b[i],&priority[i]);
        if(a[i]<0||b[i]<=0)
        {
        	printf("Invalid input");
        	i--;
        	continue;
		}
        ind[i]=i;    //this array keeps a track of the process ids
        tat[i]=0;
        rem[i]=b[i];
        comp[i]=0;
    }
    //sorting the processes based on their arrival times.
    for(i=0;i<n-1;i++)
	{
        for(j=0;j<n-i-1;j++)
		{
            if(a[j]>a[j+1])
			{
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                t=b[j];
                b[j]=b[j+1];
                b[j+1]=t;
                t=ind[j];
                ind[j]=ind[j+1];
                ind[j+1]=t;
                t=priority[j];
                priority[j]=priority[j+1];
                priority[j+1]=t;
                t=rem[j];
                rem[j]=rem[j+1];
                rem[j+1]=t;
            }
            else if(a[j]==a[j+1])
			{
                if(priority[j]>priority[j+1])
				{    //if arrival times are same, then process with lesser priority is preferred
                    t=a[j];
                    a[j]=a[j+1];
                    a[j+1]=t;
                    t=b[j];
                    b[j]=b[j+1];
                    b[j+1]=t;
                    t=ind[j];
                    ind[j]=ind[j+1];
                    ind[j+1]=t;
                    t=priority[j];
                    priority[j]=priority[j+1];
                    priority[j+1]=t;
                    t=rem[j];
                    rem[j]=rem[j+1];
                    rem[j+1]=t;
                }
            }
        }
    }
    ti=0;    //this variable keeps a track of the time completed
    i=0;
    while(complete!=n){
        //cout<<t<<" ";
        if(rem[i]==0 && comp[i]==0){
            tat[i]=ti-a[i];
            wt[i]=(tat[i]-b[i]);
            comp[i]=1;
            for(j=0;j<n;j++){
                if(comp[j]==0){
                    i=j;
                    break;
                }
            }
            complete++;
            //cout<<i<<" ";
        }
        if(ti<a[i]){
            ti=a[i];
        }
        j=i;
        k=priority[j];
        for(l=0;l<n;l++){
            if(a[l]<=ti && priority[l]<k && comp[l]==0){
                k=priority[l];
                j=l;
            }
        }
        rem[j]--;
        time[ti]=ind[j]+1;
        ti++;
        i=j;
    }
    //The sorted processes are brought back to their initial ordering
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(ind[j]>ind[j+1]){
                t=ind[j];
                ind[j]=ind[j+1];
                ind[j+1]=t;
                t=tat[j];
                tat[j]=tat[j+1];
                tat[j+1]=t;
                t=wt[j];
                wt[j]=wt[j+1];
                wt[j+1]=t;
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                t=b[j];
                b[j]=b[j+1];
                b[j+1]=t;
            }
        }
    }
    printf("\nProcess Number\tArrival Time\tBurst Time\tWaiting Time\tTurn Around Time");
    for(i=0;i<n;i++)
	{
    	printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",ind[i]+1,a[i],b[i],wt[i],tat[i]);
        avg_tat+=tat[i];
        avg_wt+=wt[i];
    }
    printf("\nGantt Chart-\n0 ");
    for(i=0;i<ti-1;i++)
    {
    	if(time[i]==-1)
    	{
    		printf("idle ");
		}
		else 
		{
			printf("P%d ",time[i]);
		}
		printf("%d ",i+1);
		
	}
    printf("\nThe average turnaround time is %f and the average waiting time is %f",avg_tat/n,avg_wt/n);
}
void non_pre()
{
    int i, j, t,n;
    float avgwt = 0, avgtt = 0;
    printf("Enter no of process : ");
    scanf("%d",&n);
	struct process
	{
    	int at, bt, wt, tt, pos, priority, completed;
	} p[n];

    for(i=0;i<n;i++)
    {
        printf("\nEnter arrival time and burst time and priority of Process %d  : ",i);
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].priority);
        if(p[i].at<0||p[i].bt<=0)
        {
        	printf("Invalid input");
        	i--;
		}
    }

    for (i = 0; i < n; i++)
	{
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

    	int pr=10000;
        int loc;
        for (i = 0; i < n; i++)
		 {

            // Checking if process has arrived and is Incomplete
            if (p[i].at <= t && p[i].completed != 1)
			 {

                if (p[i].priority < pr)
				 {

                   pr=p[i].priority;
                    loc = i;
                }
            }
        }
		if(pr==10000)
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
void HRRN()
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

int bankers_algo()
{
     int i,j,k,x;
    int l,m,n;
    int resources_no;
    int process_no;
    printf("Enter the number of process: ");
    scanf("%d",&process_no);
    printf("Enter the number of resources: ");
    scanf("%d",&resources_no);
    int max_instance[resources_no];
    int avail_instance[resources_no];
    //max_instance[resources_no];
    for(i=0;i<resources_no;i++){ // total max instances
        printf("Enter the MAX available INSTANCES of RESOURCE %d: ",i+1);
        scanf("%d",&max_instance[i]);
    }
    printf("\n");
    int res_size = 1+3*resources_no; // for the size of the matrix; 3 sets 
    int process_resources[process_no][res_size];
    //process_resources[process_no][res_size];
    m=1; // index of the startind resorces instance
    n = 0;
    for( i = 0 ; i < process_no ; i++){
        printf("Details of PROCESS %d :\n",i+1);
        process_resources[i][0] = i+1;
        //printf("pno %d\n",process_resources[i][0]);
        for(j=1;j<=resources_no;j++){ // index 0 is filled with process id
            printf("  ALLOCATED  instances for  Resource  %d : ",j);
            scanf("%d",&process_resources[i][j]);
        }
        l=j;

        for(k=j;k<=resources_no*2;k++){
            //printf("%d %d\n",k,resources_no*2);
            printf("  Max resources REQUIRED for Resource %d : ",n+1);
            scanf("%d",&process_resources[i][k]);
            if(process_resources[i][k]<process_resources[i][k-resources_no])
            {
            	printf("Invalid because maximum is less than alloted\n");
            	n--;
            	k--;
			}
            n++;
            //printf("\n");
        }
        
        for( x = k;x<=resources_no*3;x++){
            process_resources[i][x] = process_resources[i][l] - process_resources[i][m];
            //printf(" %d %d %d\n",process_resources[i][x],process_resources[i][l],process_resources[i][m]);
            l++;
            m++;
        }
        printf("\n");
        m=1;
        n=0;
    }
    
    
    printf("P_Num\tAllocated\tMaximum\t   Need \n");
    printf("\t");

    for(j=0;j<3;j++){
        for(i=0;i<resources_no;i++){
            printf(" R%d ",i+1);
        }
        printf("\t");
    }
    printf("\n");
    for(i=0;i<process_no;i++){
        printf("%d\t",process_resources[i][0]);
        for(j=1;j<res_size;j++){
            printf(" %d  ",process_resources[i][j]);
        if(j%resources_no==0)
            printf("\t");
        }
        printf("\n");
    }
    
    //avail instances
    for(i=0;i<resources_no;i++){
        avail_instance[i]=0;
    }
    int tot=0;
    for(j=1;j<=resources_no;j++){
        for(i=0;i<process_no;i++){
            tot = tot + process_resources[i][j];
        }
        avail_instance[j-1]=tot;
        tot=0;
    }
    for(i=0;i<resources_no;i++){
        avail_instance[i]=max_instance[i]-avail_instance[i];
        if(avail_instance[i]<0)
        {
        	printf("Invalid input");
        	return 0;
		}
    }
    printf("The total available resources after allocation:\n");
    for(i=0;i<resources_no;i++){
            printf(" R%d\t",i+1);
    }
    printf("\n");
    for(i=0;i<resources_no;i++){
        printf(" %d\t",avail_instance[i]);
    }
    printf("\n");
    printf("\n");
    
    int safe_sequence[process_no];
    int flag[process_no];
    for(i=0;i<process_no;i++){
        safe_sequence[i]=-1;
        flag[i]=0;   
    }
    // int k;
    l=0;
    x=0;
    int count = 0;
    while(x<20){
        for(k=0;k<process_no;k++){
            if(flag[k]==1){
                count++;
                // printf("c=%d\n",count);
            } 
            if(count==process_no){
                goto next;
            }

        }
        for(i=0;i<process_no;i++){
            for(j=1;j<=resources_no;j++){
                if(process_resources[i][2*resources_no+j]<=avail_instance[j-1]){
                    if(j==resources_no && flag[i]!=1){
                        safe_sequence[l++]=process_resources[i][0];
                        flag[process_resources[i][0]-1]=1;
                        for(k=0;k<j;k++){
                            avail_instance[k] = avail_instance[k] + process_resources[i][k+1];
                            // printf("asdf");
                        }
                    }
                }
                else{
                    break;
                }
            }
        }
        //x=(x+1)%processes;
        x++;
    }
        for(i=0;i<process_no;i++){
            if(safe_sequence[i] == -1){
                    printf("This processes are not safe\n");
                    return EXIT_FAILURE;
            }
        }
    next:{
    printf("The processes are safe\n");
    for(i=0;i<process_no;i++){
        printf(" P%d -",safe_sequence[i]);
    }
    }
    return 0;
}