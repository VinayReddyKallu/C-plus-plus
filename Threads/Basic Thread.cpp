#include<iostream>
#include<windows.h>
using namespace std;
HANDLE hevent;
DWORD WINAPI Thread1(LPVOID lpparam)
{
   
   cout<<"thread 1 running"<<"\n";
   return 0;

}
DWORD WINAPI Thread2(LPVOID lparam)
{
   cout<<"thread 2 running"<<"\n";
   
   return 0;

}
int main()
{

    HANDLE h1,h2;
    DWORD d1,d2;

    h1=CreateThread(NULL,0,Thread1,NULL,0,&d1); 
    if(h1==NULL)
      cout<<GetLastError();
    h2=CreateThread(NULL,0,Thread2,NULL,0,&d2); 
    if(h2==NULL)
      cout<<GetLastError();
   WaitForSingleObject(h1,INFINITE);
   WaitForSingleObject(h2,INFINITE);
    CloseHandle(h1);
    CloseHandle(h2);
    system
    
    ("Pause");
   return 0;
}