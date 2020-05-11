#include<iostream>
#include<time.h>
using namespace std;
#include<bits/stdc++.h>
void WriteLogFile(const string &msg)
{   time_t my_time = time(NULL); 
    ofstream log("log.txt",ios_base::out | ios_base::app);
    log<<"INFO"<<" "<<ctime(&my_time)<<":"<<msg<<endl;
}
int main()
{
     int q;
    cout<<"Enter the No of queries"<<"\n";
    cin>>q;
    unordered_map<string,int>umap; 
    int a,marks;
    string s;
    while(q--)
    {
       cin>>a;
       cin>>s;
       if(a==1)
       {
             cin>>marks;
             umap[s]+=marks;
             WriteLogFile(s +" Registration done");
       }
       else if(a==2)
       {
           umap[s]=0;
           WriteLogFile(s+ "Marks modified");
       }
       else if(a==3)
       {
           cout<<"The marks of the student "<<s<<" : "<<umap[s]<<"\n";
           WriteLogFile(s+" Marks Displayed");
           
       }
       else
       {
           cout<<"Enter input in correct format"<<"\n";
           break; 
       }
       
       
    }
    return 0;

}