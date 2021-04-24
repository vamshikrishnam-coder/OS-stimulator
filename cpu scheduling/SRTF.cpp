#include<bits/stdc++.h>
using namespace std;


int srtf_main()
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
    return 0;
}


int main()
{
    srtf_main();
    return 0;
}