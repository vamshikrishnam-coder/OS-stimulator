//MFT WORST FIT//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#define N 1000

typedef struct
{
      int pid;
      int size;
      bool allocated;
      int partition;
}
process;

typedef struct
{
      int size;
      int allocated;
      int pid;
}
partition;

int mm_size, n, nf = 0, m, maxpa=0;
process p[N];
partition part[N];

int get_slot(int pid)
{
      int maxi = -1e9, pos = -1;

      for (int i = 0; i < nf; i++)
      {

            if (part[i].pid == -1 && part[i].size >= p[pid].size && maxi < part[i].size)
            {
                  maxi = part[i].size;
                  pos = i;
            }
      }

      return pos;
}

void free_slot(int pos)
{
      part[pos].pid = -1;
      part[pos].allocated = 0;
      // p[n].allocated = false;
      // p[n].partition = -1;
}

int external_fragment()
{
      int ret = 0;
      for (int i = 0; i < nf; i++)
            if (part[i].pid == -1)
                  ret += part[i].size;

      return ret;
}

int internal_fragment()
{
      int ret = 0;
      for (int i = 0; i < nf; i++)
            ret += part[i].size - part[i].allocated;

      return ret;
}

int main()
{
      system("clear");
      int mm_size, n, maxp, waste, ch;

      printf("Enter the total size of memory : ");
      scanf("%d", &mm_size);
      waste = mm_size;

      printf("Enter number of partitions : ");
      scanf("%d", &m);

      printf("\nEnter the partition sizes\n");
      for (int i = 0; i < m; i++)
      {
            printf("P%d : ", i);
            scanf("%d", &part[i].size);
            waste -= part[i].size;
            if (waste < 0)
            {
                  waste += part[i].size;
                  printf("partition %d cant be given space as remaining is %d\n", i, waste);
                  continue;
            }
            part[nf].size = part[i].size;
            part[nf].allocated = 0;
            part[nf].pid = -1;
            nf++;
            if (waste == 0)
            {
                  printf("Memory full...\n");
                  break;
            }
      }

      printf("Final partitions:\n");
      for (int i = 0; i < nf; ++i)
      {
            printf("partition %d --> %d\n", i, part[i].size);
      }

      printf("Memory wasted due to partitioning : %d\n", waste);

      n = 0;
      printf("Worst Fit\n");
      do {
            printf("\n1. Insertion\n2. Deletion\n3. Exit\nEnter your choice : ");
            scanf("%d", &ch);

            if (ch == 1)
            {
                  int flag=0;
                  printf("\nEnter #%d process size : ", n);
                  scanf("%d", &p[n].size);
                  p[n].pid = n;
                  p[n].allocated = false;

                  int pos = get_slot(n);
                  maxpa=part[0].size;
                  for(int i=0; i<nf; i++)
                  {
                        if(part[i].allocated==false && part[i].size>maxpa)
                        {
                              maxpa=part[i].size;
                        }
                        if(part[i].allocated==true)
                              flag++;
                  }
                  if (pos == -1)
                  {
                        if( external_fragment()<=p[n].size && external_fragment()!=0 && flag!=1)
                              printf("\nP%d can't be accomodated due to external fragmentation\n", n );
                        
                  }
                  if (maxpa<p[n].size)
                  {
                        printf("P%d can't be accomodated as it exceeds max partition (if any)\n", n  );
                  }

                  else if (part[pos].size >= p[n].size)
                  {
                        part[pos].allocated = p[n].size;
                        part[pos].pid = n;
                        p[n].allocated = true;
                        p[n].partition = pos;
                        

                        printf("\n\nMemory Table\nPartition\tSize\t\tAllocated\tProcess\n");
                        for (int i = 0; i < nf; i++)
                        {
                              printf("%d\t\t%d\t\t%d\t\t", i , part[i].size, part[i].allocated);
                              if (part[i].pid == -1)
                                    printf("None\n");
                              else
                                    printf("%d\n", part[i].pid );
                        }

                        printf("\nTotal remaining memory : %d\n\n", internal_fragment());
                        printf("\nExternal Fragments : %d\n\n", external_fragment());

                        if(p[n].size<part[pos].size)
                              printf("\nP%d causes  internal fragmentation\n", n );
                        n++;
                  }
            }
            else if (ch == 2)
            {
                  int prem,parti=-1;
                  printf("\nWhich process would you like to remove? ");
                  scanf("%d", &prem);
                  for (int i = 0; i < n; ++i)
                  {
                        if(prem==p[i].pid)
                        {
                              parti=p[i].partition;
                        }
                  }
                  printf("\npart:%d\n",parti);
                  if(parti==-1)
                  {
                        printf("Processes not in any partition\n");
                        continue;
                  }
                  
                  part[parti].pid = -1;
                  part[parti].allocated = 0;
                  printf("\n\nMemory Table\nPartition\tSize\t\tAllocated\tProcess\n");
                  for (int i = 0; i < nf; i++)
                  {
                        printf("%d\t\t%d\t\t%d\t\t", i , part[i].size, part[i].allocated);
                        if (part[i].pid == -1)
                              printf("None\n");
                        else
                              printf("%d\n", part[i].pid );
                  }
                  printf("\nTotal remaining memory : %d\n\n", internal_fragment());
                  printf("\nExternal Fragments : %d\n\n", external_fragment());
            }

      } while (ch == 1 || ch == 2);

}
