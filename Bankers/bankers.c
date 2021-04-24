// bankers algorithm
// 191CS263
#include<stdio.h>
#include<stdlib.h>
#define SIZE 20


int safe_sequence(int processes, int resources,int avail_mat[],int size,int processes_mat[][size]){
    int i,j;
    // safe sequence
    int safe_sequence[processes];
    int flag[processes];
    for(i=0;i<processes;i++){
        safe_sequence[i]=-1;
        flag[i]=0;   
    }
    int k;
    int l=0;
    //int x=0;
    int count = 0;
    while(1<2 ){
        for(k=0;k<processes;k++){
            if(flag[k]==1){
                count++;
                //printf("c=%d\n",count);
            } 
            if(count==processes){
                goto next;
            }
        }
        for(i=0;i<processes;i++){
            for(j=1;j<=resources;j++){
                if(processes_mat[i][2*resources+j]<=avail_mat[j-1]){
                    if(j==resources && flag[i]!=1){
                        safe_sequence[l++]=processes_mat[i][0];
                        flag[processes_mat[i][0]-1]=1;
                        for(k=0;k<j;k++){
                            avail_mat[k] = avail_mat[k] + processes_mat[i][k+1];
                        }
                    }
                }
                else{
                    break;
                }
            }
        }
        //x=(x+1)%processes;
    }
    for(i=0;i<processes;i++){
        if(safe_sequence[i] == -1){
                printf("This processes are not safe\n");
                return EXIT_FAILURE;
        }
    }
    next:{
    printf("The processes are safe\n");
    for(i=0;i<processes;i++){
        printf(" P%d -",safe_sequence[i]);
    }
    }
}

int main()
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
    
    
    printf("P_Num\tAllocated\tMaximum\t Need \n");
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
    safe_sequence(process_no,resources_no,avail_instance,res_size,process_resources);

    return 0;
}
