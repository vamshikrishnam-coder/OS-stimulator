//MFT with first fit//
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct proc{
    //int p_id;
    int size;
    int flag;
}*p;

int total_memory,total_internalfragmentation,ext,remaining_memory ;
struct part{
    int part_no;
    int size;
    struct proc *process;
    int internal_frag;
}*memory;
int insert(struct proc *k,int n)
{
    int i =0;
    for(i=0;i<n;i++)//fisrt fit
    {
        if(memory[i].size >= k->size && memory[i].process == NULL)
        {
            k->flag = 1;
            memory[i].process = k;
            memory[i].internal_frag = memory[i].size - k->size ;
            total_internalfragmentation += memory[i].internal_frag;
            printf("This process is accomodated in partition %d\n",memory[i].part_no);
            return 1;
        }
    }
    for(i=0;i<n;i++)
    {
        if(memory[i].internal_frag >= k->size)
        {
            printf("this process cannot be accomodated due to internal fragmentation\n");
            return 0;
        }
    }
    if(total_internalfragmentation+remaining_memory >= k->size)
    {
        printf("this process cannot be accomodated due to external fragmentation\n");
        return 0;
    }
    printf("This process cannot be accomodated due to insufficient memory\n");
    return -1;

}
int main()
{
    p = malloc(50*sizeof(struct proc));
    printf("Enter total size of memory: ");
    scanf("%d",&total_memory);
    total_internalfragmentation = 0; ext = 0;
    remaining_memory  = total_memory;
    int n = 0;
    printf("Total number of partitions:");
    scanf("%d",&n);
    memory = malloc(n* sizeof(struct part));
    int i=0,t_size = 0,j=0;
    for(i=0;i<n;i++)
    {
        memory[i].part_no = i+1;
        memory[i].process = NULL;
    }
    for(i=0;i<n;i++)
    {

        printf("Size of partition [%d]:",memory[j].part_no);
        scanf("%d",&t_size);
        if(t_size > remaining_memory)
        {
            printf("This partition cannot be made as space left is only %d units\n",remaining_memory);
        }
        else
        {
            memory[j].size = t_size;
            remaining_memory -= t_size;
            j++;
        }
    }
    n = j;
    //all paritions made
    int pro_count=0;
    while(1)
    {
        int choice,p_id;
        printf("\nSelect 1.Insert\t2.Delete\t3.Stop\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:

                printf("size of process [%d]:",pro_count);
                scanf("%d",&p[pro_count].size);
                p[pro_count].flag = 0; //rn not allocated
                insert(&p[pro_count],n);
                pro_count+=1;
                break;
            case 2:
                printf("Enter process id to be deleted:");
                scanf("%d",&p_id);
                if(p[p_id].flag!=1)
                {
                    printf("Process is not currently allocated any memory to delete\n");
                    break;
                }
                else
                {
                    p[p_id].flag = 0;
                    for(i=0;i<n;i++)
                    {
                        if(memory[i].process == &p[p_id])
                        {
                            memory[i].process = NULL;
                            total_internalfragmentation -= memory[i].internal_frag;
                            memory[i].internal_frag = 0;
                            printf("Process removed\n");

                        }
                    }

                }
                break;
            case 3:
                printf("\nTotal internal fragmentation is: %d units\n",total_internalfragmentation);
                printf("The unused space in the memory is: %d units\n",remaining_memory);
                exit(0);
            default:
                printf("Invalid entry\n");
        }
    }
}
