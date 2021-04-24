#include <bits/stdc++.h>
#include "pro.h"
using namespace std;

int main()
{
    int c;
    while(1){
        cout<<"----------OS_Simulator----------"<<endl;
        cout<<"Select the options for simulation"<<endl;
        cout<<"1.Synchronization"<<endl;
        cout<<"2.Disk Schedulling"<<endl;
        cout<<"3.Schedulling"<<endl;
        cout<<"4.MFT MVT"<<endl;
        cout<<"5.Page Replacent"<<endl;
        cout<<"6.Bankers"<<endl;
        cout<<"7.Exit"<<endl;
        cin>>c;
        // getchar();
        switch(c){
            case 1:{
                synchronization();
                break;
            }
            case 2:{
                int s;
                cout<<"1. CLOOK\n2. CSCAN\n3. FCFS\n4. LOOK\n5. SCAN\n6. SSTF"<<endl;
                cin>>s;
                switch(s){
                    case 1:{
                    CLOOK(); 
                    break;
                    }
                    case 2:{
                        CSCAN();
                        break;
                    }
                    case 3:{
                        FCFS();
                        break;
                    }
                    case 4:{
                        LOOK();
                        break;
                    }
                    case 5:{
                        SCAN();
                        break;
                    }
                    case 6:{
                        SSTF();
                        break;
                    }
                }
                break;
            }
            case 3:{
                int s;
                cout<<"1. FCFS\n2. LJFS\n3. LRTF\n4. RR\n5. SJFS\n6. SRTF\n7. HRRN\n8. Preemptive priority scheduling\n9. Non Preemptive priority scheduling"<<endl;
                cin>>s;
                switch(s){
                    case 1:{
                    FCFS_sche();
                    break;
                    }
                    case 2:{
                        LJFS();
                        break;
                    }
                    case 3:{
                        LRTF();
                        break;
                    }
                    case 4:{
                        RR();
                        break;
                    }
                    case 5:{
                        SJFS();
                        break;
                    }
                    case 6:{
                        SRTF();
                        break;
                    }
                    case 7:{
                        HRRN();
                        break;
                    }
                    case 8:{
                        prem_prio_sche();
                break;
                    }
                    case 9:{
                        non_pre();
                break;
                    }
                }
                break;
            }
            case 4:{
                int s;
                cout<<"1.MFT\n2.MVT"<<endl;
                cin>>s;
                switch(s){
                    case 1:{
                        mft_main();
                    
                        break;
                    }
                    case 2:{
                        mvt();
                        break;
                    }
                    
                }
            }
            case 5:{
                pg_rep();
                break;
            }
            case 6:{
                bankers_algo();
                break;
            }
            case 7:{
                return EXIT_SUCCESS;
                break;
            }
            default :{
                printf("Invalid Option\n");
                exit(0);
            }
        }
    }
    return 0;
}