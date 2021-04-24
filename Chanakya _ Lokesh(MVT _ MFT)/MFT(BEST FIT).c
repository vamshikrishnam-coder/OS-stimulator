#include <stdio.h>
#include <stdlib.h>

void bestFit();
void Remove();

struct partition{
    int size;
    int process_size;
    int pid;
    int flag;
};

struct partition *P;

int t_size, n_parts, *partitions, emp_space;

int main()
{
    int r_size, n, flag=1,i;
    printf("\nEnter the Total size of memory: ");
    scanf("%d", &t_size);
    printf("\nEnter the Number of Partitions:");
    scanf("%d", &n_parts);
    P = (struct partition*)malloc(sizeof(struct partition)*n_parts);
    for(i=0; i<n_parts; i++){
        P[i].flag=0;
    }
    emp_space=t_size;
    printf("\nEnter the Size of each partitions-\n");
    r_size=t_size;
    for(i=0; i<n_parts; i++){
        printf("Size of Partition %d: ", i);
        scanf("%d", &P[i].size);
        if(P[i].size<=r_size){
            r_size=r_size-P[i].size;
        }else{
            printf("Partition %d cannot be formed due to insufficient space. Only %dKB space is remaining.\n", i, r_size);
            n_parts--;
            i--;
        }
    }
    while(flag){
        printf("\nThe operations available are:");
        printf("\n1. Insert");
        printf("\n2. Remove");
        printf("\n3. Stop");
        printf("\nEnter the appropriate operation: ");
        scanf("%d", &n);
        switch(n)
        {
        case 1:
            {
                bestFit();
                break;
            }
        case 2:
            {
                Remove();
                break;
            }
        case 3:
            {
                flag=0;
                break;
            }
        default:
            printf("\nEnter the valid input!!");
        }
    }

}

void bestFit()
{
    int min, id, size, min_part, flag=0, flag1=0, i, flag3=0;
    min=t_size+1;
    printf("\nEnter the ProcessID of the process to be entered: ");
    scanf("%d", &id);
    printf("Enter the Size of the process: ");
    scanf("%d", &size);
    for(i=0;i<n_parts; i++){
        if(P[i].flag==1){
            if(P[i].pid==id){
                printf("Process %d is already present in Partition %d.", id, i);
                return;
            }
        }
    }
    for(i=0; i<n_parts; i++){
        if(P[i].flag==0){
            flag1=1;
            if(P[i].size>=size){
                flag=1;
                if(P[i].size<min){
                    min=P[i].size;
                    min_part=i;
                }
            }
        }
    }
    if(flag1==0){
        printf("All the partitions are full. So the process cannot be accommodated\n");
    }
    if(flag==1){
        P[min_part].pid=id;
        P[min_part].process_size=size;
        P[min_part].flag=1;
        emp_space=emp_space-size;
        printf("Process %d is added to Partition %d.", id, min_part);
    }
    if(flag==0 && flag1==1){
        printf("Size of Process%d exceeds the size of empty partitions.", id);
        return;
    }else if(emp_space>=size && flag==0){
        for(i=0; i<n_parts; i++){
            if(P[i].size-P[i].process_size>=size){
                flag3=1;
                printf("Process %d cannot be accommodated due to internal fragmentation.", id);
                break;
            }
        }
        if(flag3!=1){
            printf("Process %d cannot be accommodated due to internal fragmentation.", id);
        }
    }
    if(flag==1){
        for(i=0; i<n_parts; i++){
            printf("\n\nPartition %d: ", i);
            printf("\nPartition Size = %dKB", P[i].size);
            if(P[i].flag==1){
                printf("\nProcess is allocated.");
                printf("\nProcess ID = %d", P[i].pid);
                printf("\nProcess Size = %dKB.\n", P[i].process_size);
            }else{
                printf("\nNo Process allocated.\n");
            }

        }
    }
}

void Remove()
{
    int id, i, flag=0;
    printf("\nEnter the process id to be removed: ");
    scanf("%d", &id);
    for(i=0;i<n_parts;i++){
        if(P[i].flag==1 && P[i].pid==id){
            flag=1;
            P[i].flag=0;
            printf("\nProcess %d is removed.", id);
            break;
        }
    }
    if(flag==0){
        printf("\nProcess %d is not present in any partition.", id);
    }
    if(flag==1){
        for(i=0; i<n_parts; i++){
            printf("\n\nPartition %d: ", i);
            printf("\nPartition Size = %dKB", P[i].size);
            if(P[i].flag==1){
                printf("\nProcess is allocated.");
                printf("\nProcess ID = %d", P[i].pid);
                printf("\nProcess Size = %dKB.\n", P[i].process_size);
            }else{
                printf("\nNo process allocated.\n");
            }
        }
    }
}
