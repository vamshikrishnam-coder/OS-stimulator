#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;

//inserting a process according to the first fit algorithm
void insert_process_ff(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int *n){
    int i,j,flag=0;
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
        if(process_size <= memory[i] && accomodated[i]>=0){
            flag=1;
        }
    }
    if(flag==1){
        cout<<"Process cannot be accomodated due to internal fragmentation\n";
    }
    else{
        cout<<"Process cannot be accomodated due to external fragmentation\n";   //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    }
    return ;
}

//inserting a process according to the best fit algorithm
void insert_process_bf(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int*n){
    int i,j,best_index=-1,flag=0;
    for(i=0;i<(*num_partitions);i++){ 
        if(process_size <= memory[i] && accomodated[i]==-1 && (best_index==-1 || memory[i]<(memory[best_index]))){   //find the unoccupied partition better than the best partition found so far
            best_index=i;
        }
        if(process_size <= memory[i] && accomodated[i]>=0){
            flag=1;
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
    if(flag==1){
        cout<<"Process cannot be accomodated due to internal fragmentation\n";
    }
    else{
        cout<<"Process cannot be accomodated due to external fragmentation\n";   //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    }
    return ;
}

//inserting a process according to the worst fit algorithm
void insert_process_wf(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int *n){
    int i,j,best_index=-1,worst_index=-1,flag=0;
    for(i=0;i<(*num_partitions);i++){
        if(process_size <= memory[i] && accomodated[i]==-1 && (worst_index==-1 || memory[i]>(memory[worst_index]))){    //find the unoccupied partition larger than the worst partition found so far
            worst_index=i;
        }
        if(process_size <= memory[i] && accomodated[i]>=0){
            flag=1;
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
    if(flag==1){
        cout<<"Process cannot be accomodated due to internal fragmentation\n";
    }
    else{
        cout<<"Process cannot be accomodated due to external fragmentation\n";   //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    }
    return ;
}

//inserting a process according to the next fit algorithm
void insert_process_nf(int index, int *next_index, int process_size, int *memory, int *num_partitions, int *accomodated, int *n){
    int i,j,flag=0;
    for(i=(*next_index);i<*num_partitions;i++){
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
            (*next_index) = (i+1)%(*num_partitions);
            return ;
        }
        if(process_size <= memory[i] && accomodated[i]>=0){
            flag=1;
        }
    }
    for(i=0;i<(*next_index);i++){
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
            (*next_index) = (i+1)%(*num_partitions);
            return ;
        }
        if(process_size <= memory[i] && accomodated[i]>=0){
            flag=1;
        }
    }
    if(flag==1){
        cout<<"Process cannot be accomodated due to internal fragmentation\n";
    }
    else{
        cout<<"Process cannot be accomodated due to external fragmentation\n";   //if partition with enough size is not found but total unused space is more than process size, its a case of external fragmentation
    }
    return ;
}

int mvt(){
    int i,j,k,l,s=1,flag=0,total_size,num_process,n,m=0,count=0,index=0,process_size,num_partitions=0,del_index,next_index=0,fit_type=0;
    int process[1001]={0};
    cout<<"Total size: ";
    cin>>total_size;
    int memory[total_size];
    memory[0] = total_size;
    num_partitions=1;
    cout<<"Enter 1 for first fit, 2 for best fit, 3 for worst fit and 4 for next fit: ";
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
            if(process[index]!=0){
                cout<<"Process with the same index already exists. Please select a different index\n";
                continue;
            }
            if(process_size<=n){
                process[index]=process_size;
                //call the insert function depending on the type of fit chosen previously
                if(fit_type==1){
                    insert_process_ff(index, process_size, memory, &num_partitions, accomodated, &n);
                }
                else if(fit_type==2){
                    insert_process_bf(index, process_size, memory, &num_partitions, accomodated, &n);
                }
                else if(fit_type==3){
                    insert_process_wf(index, process_size, memory, &num_partitions, accomodated, &n);
                }
                else if(fit_type==4){
                    insert_process_nf(index, &next_index, process_size, memory, &num_partitions, accomodated, &n);
                }
                else{
                    break;
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
                    process[del_index]=0;
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
    return 0;
}