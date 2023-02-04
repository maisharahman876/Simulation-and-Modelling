#include<bits/stdc++.h>
using namespace std;
void generate_rank(int rank[],int n)
{
    for(int i=0;i<n;i++)
    {
        rank[i]=i;
    }
    random_shuffle(rank,rank+n);
}

int main()
{
    //implement marraige problem simulation
    int n,s;
    int no_of_samples;
    srand(time(NULL));
    //write console log to file
    freopen("output.txt","w",stdout);
    //take input from file
    ifstream fin("input.txt");
    fin>>n>>s;
    int rank[n];
    bool is_called[n];
    generate_rank(rank,n);
    //print rank
    // cout<<"Ranks are: "<<endl;
    // for(int i=0;i<n;i++)
    // {
    //     cout<<i+1<<" "<<rank[i]<<endl;
    // }
    //take an array of sample size
    fin>>no_of_samples;
    cout<<"Sample size\tBest rank\tChosen Rank\tSuccess"<<endl;
    for(int i=0;i<no_of_samples;i++)
    {
        //srand(time(NULL));
        int m;
        fin>>m;
        //cout<<m<<" ";
        int best_rank=INT_MAX;
        for(int i=0;i<n;i++)
        {
            is_called[i]=false;
        }
        //randomly pick a unique number from 1 to n
        for (int i=0;i<m;i++)
        {
            int x=rand()%n;
            while(is_called[x])
            {
                x=rand()%n;
            }

            is_called[x]=true;
            if(rank[x]<best_rank)
            {
                best_rank=rank[x];
            }
        }
        //cout<<best_rank<<endl;
        for(int i=0;i<n-m;i++)
        {
            int x=rand()%n;
            while(is_called[x])
            {
                x=rand()%n;
            }

            is_called[x]=true;
            if(rank[x]<best_rank)
            {
                if(rank[x]<s)
                cout<<m<<"\t\t"<<best_rank<<"\t\t"<<rank[x]<<"\t\t"<<"Yes"<<endl;
                else
                cout<<m<<"\t\t"<<best_rank<<"\t\t"<<rank[x]<<"\t\t"<<"No"<<endl;
                break;
            }
            if(i==n-m-1)
            {
                cout<<m<<"\t\t"<<best_rank<<"\t\t"<<rank[x]<<"\t\t"<<"No"<<endl;
            }

        }
        



    }

}
