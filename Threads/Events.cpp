#include<windows.h>
#include<iostream>
#include<fstream>
using namespace std;
HANDLE h1,h2;
DWORD WINAPI read(LPVOID param)
{
    while(true)
    {
       string s;
      WaitForSingleObject(h1,INFINITE);
     ifstream fptr;
     fptr.open("file.txt",ios::in);
     cout<<"Reading the text  from the file"<<"\n";
     fptr>>s;
     cout << s << endl;
     fptr.close();
     SetEvent(h2);
    }
     
    
    
    return 0;
}
DWORD WINAPI write(LPVOID param1)
{ 
  int flag;
  while(true)
    {
       cout<<"Enter 1 to write into file or 0 to quit"<<"\n";
       cin>>flag;
      if(flag==0)
         exit(0);
       else
       {
           
           ofstream fptr;
           fptr.open("file.txt",ios::out);
           string s;
           cout<<"Enter the text to write into file"<<"\n";
           cin>>s;
           fptr<<s;
           cout<<"The text has been written to the file"<<"\n";
           fptr.close();
           SetEvent(h1);
           WaitForSingleObject(h2,INFINITE);
       }
       
     
    }
return 0;
}
int main()
{
  try
  {
         HANDLE th1,th2;
    h1=CreateEvent(NULL,false,false,NULL);
    if(h1==NULL)
    {
        cout<<"Creation failed"<<GetLastError()<<"\n";
    }
    h2 = CreateEvent(NULL,false,false,NULL);
    if(h2==NULL)
    {
        cout<<"Creation failed"<<GetLastError()<<"\n";
    }
    th1 = CreateThread(NULL,0,read,NULL,0,NULL);
     if(th1==NULL)
    {
        cout<<"Creation failed"<<GetLastError()<<"\n";
    }
    th2 = CreateThread(NULL,0,write,NULL,0,NULL);
    if(h1==NULL)
    {
        cout<<"Creation failed"<<GetLastError()<<"\n";
    }
    WaitForSingleObject(th1,INFINITE);
    WaitForSingleObject(th2,INFINITE);
    CloseHandle(th1);
    CloseHandle(th2);
    CloseHandle(h1);
    CloseHandle(h2);
    system("PAUSE");
  }
    catch(exception e)
    {
        cout<<"Exception has occured"<<e.what()<<"\n";
    }
      
    
   
   return 0;
}