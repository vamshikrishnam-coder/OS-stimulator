#include <bits/stdc++.h>
using namespace std;

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

int main()
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
    sort(p.begin(),p.end(),comp);
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
