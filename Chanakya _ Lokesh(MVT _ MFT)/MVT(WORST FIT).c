//MVT WORST FIT//
#include <stdio.h>
#include <stdlib.h>

struct memory
{
    int partition_id;
    int p_id;
    int partition;
    struct memory *next_partition;
    int left;
};

struct process
{
    int p_id;
    struct memory *position;
    int req;
};

struct memory *main_memory;
int parts = 1;
int main_mem;
int left_mem; //EXTERNAL FRAGEMANTION
struct process *p = NULL;

void rmv_proc(int id, int limit)
{
    if (p[id - 1].position != NULL)
    {
        p[id - 1].position->left = p[id - 1].req;
        p[id - 1].position->p_id = -1;
        p[id - 1].position = NULL;
        left_mem = left_mem + p[id - 1].req;
        printf("process %d is deallocated in the main memory\n", id);
    }
    else
    {
        printf(" process %d is not allocted in the memory", id);
    }
    //merging the free consecutive partitions

    struct memory *tem;
    tem = main_memory;
    while (tem->next_partition != NULL)
    {
        if (tem->p_id == -1 && tem->next_partition->p_id == -1)
        {
            printf("partitions have size %d and %d are merged as there are no process present in both the partitions\n", tem->partition, tem->next_partition->partition);
            tem->partition = tem->partition + tem->next_partition->partition;
            tem->next_partition = tem->next_partition->next_partition;
        }
        else
        {
            tem = tem->next_partition;
        }
    }
}
void print_pr(struct process *pj, int pr)
{
    printf("____________________PROCESS TABLE__________________________\n");
    int i = 0;
    for (i; i < pr; i++)
    {
        if (pj[i].position == NULL)
        {
            printf("process %d is not allotted\n", i + 1);
        }
        else
        {
            printf("process %d is allocated at partition %d\n", pj[i].p_id, pj[i].position->partition_id);
        }
    }
}
void order()
{
    struct memory *Temp;
    Temp = main_memory;
    int count = 1;
    while (Temp != NULL)
    {
        Temp->partition_id = count;
        Temp = Temp->next_partition;
        count++;
    }
}

void Worst_fit()
{
    int processes = 0;
    int choc;
    printf("Enter 1 for adding a process to the main memory \nEnter 2 to delete a process \nEnter 0 if processes are finished\nENTER YOUR CHOICE! :");
    scanf("%d", &choc);
    while (choc)
    {
        switch (choc)
        {
        case 1:
            if (p == NULL)
            {
                p = malloc(++processes);
            }
            else
            {
                p = realloc(p, (++processes * sizeof(struct process)));
            }
            printf("memeory requirement of process %d : ", processes);
            scanf("%d", &p[processes - 1].req);
            p[processes - 1].p_id = processes;
            p[processes - 1].position = NULL;
            if (p[processes - 1].req <= left_mem)
            {
                struct memory *mini;
                mini = NULL;
                struct memory *t;
                t = main_memory;
                while (t != NULL)
                {
                    if (t->p_id < 0)
                    {
                        if (t->partition >= p[processes - 1].req)
                        {
                            if (mini == NULL)
                            {
                                mini = t;
                            }
                            else if (mini->partition < t->partition)
                            {
                                mini = t;
                            }
                        }
                    }
                    t = t->next_partition;
                }

                if (mini == NULL)
                {
                    printf(" Process %d cant be allotted due to external frag\n", p[processes - 1].p_id);
                }
                else
                {
                    if (mini->partition > p[processes - 1].req)
                    {
                        parts++;
                        main_memory[parts - 1].next_partition = mini->next_partition;
                        mini->next_partition = main_memory + parts - 1;
                        main_memory[parts - 1].partition = mini->partition - p[processes - 1].req;
                        mini->partition = p[processes - 1].req;
                        main_memory[parts - 1].p_id = -1;
                    }

                    if (mini->partition == p[processes - 1].req)
                    {
                        mini->p_id = p[processes - 1].p_id;
                        p[processes - 1].position = mini;
                        left_mem = left_mem - mini->partition;
                        order();

                        printf("process %d is allocted in the partition %d of the main memory \n", processes, mini->partition_id);
                    }
                }
            }
            else
            {
                printf("memory isnt suffice to allot the process\n");
            }
            break;
        case 2:
            printf("Enter the process id to delete");
            scanf("%d", &choc);
            rmv_proc(choc, processes);
            break;
        default:
            printf("Your choice is incorrect please enter the coorect choice!!!\n enter the choice again :");

            break;
        }
        printf("enter the choice again :");
        scanf("%d", &choc);
    }
    print_pr(p, processes);
}
void print(struct memory *pr)
{
    puts("______________________________MEMORY______________________________\n");
    int int_frag = 0;
    int i = 0;
    while (pr != NULL)
    {
        if (pr[i].p_id == -1)
        {
            printf("partition %d having size %d occupied NO PROCESS\n", pr[i].partition_id, pr[i].partition);
        }
        else
        {
            printf("partition %d having size %d occupied process %d \n", pr[i].partition_id, pr[i].partition, pr[i].p_id);
        }
        pr = pr->next_partition;
    }
    printf("left over memory in the main memory %d\n", left_mem);
}
int main()
{
    printf("Enter  the size of the main memory :");
    scanf("%d", &main_mem);
    left_mem = main_mem;
    main_memory = malloc(sizeof(struct memory) * 100);
    main_memory->next_partition = NULL;
    main_memory->partition_id = 1;
    main_memory->partition = main_mem;
    main_memory->p_id = -1;
    int choice;
    Worst_fit();
        print(main_memory);
}
