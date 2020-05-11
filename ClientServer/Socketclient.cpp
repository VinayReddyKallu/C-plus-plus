#include <iostream>
#include <winsock2.h>
#include <string.h> 
using namespace std; 
DWORD WINAPI receive(LPVOID lpParam)
{
    try
    {
       char buffer[1024]={0};
    SOCKET server = *(SOCKET *)lpParam;
    while(1)
     {
        if(recv(server, buffer, sizeof(buffer), 0)==SOCKET_ERROR)
        {
            cout<<"receive function caused an error: "<<WSAGetLastError()<<endl;
            return 0;
        }
        
        
        cout<<"Server: "<<buffer<<endl;
        if(strcmp(buffer,"exit")==0)
           break;
        memset(buffer,0,sizeof(buffer));
     } 
    }
    catch(exception& e)
    {
        cout << e.what() << '\n';
    }
    
    
    return 0;
}
 
DWORD WINAPI send(LPVOID lpParam)
{
    try
    {
        /* code */
        char buffer[1024]={0};
    SOCKET server = *(SOCKET *)lpParam;
    while(1)
     {
        cout<<"Enter some text to send or Enter exit"<<"\n";+
        gets(buffer);
 
        if(send(server, buffer, sizeof(buffer), 0)==SOCKET_ERROR)
        {
            cout<<"send function caused an error: "<<WSAGetLastError()<<endl;
            return 0;
        }
        if(strcmp(buffer,"exit")==0)
            break;
     }
    }
    catch(exception& e)
    {
        std::cout<< e.what() << '\n';
    }
    
    
    return 0;
}
 
int main()
{
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    HANDLE thread1,thread2;
    try
    {
        WSAStartup(MAKEWORD(2,2), &WSAData);
 
      if((server = socket(AF_INET, SOCK_STREAM, 0))==INVALID_SOCKET)
      {
        cout<<"Socket creation"<<WSAGetLastError()<<endl;
        return 0;
      }
      addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
      addr.sin_family = AF_INET;
      addr.sin_port = htons(5555);
 
     if(connect(server, (SOCKADDR *) &addr, sizeof(addr))==SOCKET_ERROR)
     {
        cout<<"Server connection failed "<<WSAGetLastError()<<endl;
        return 0;
     }
     cout << "Connected to server." << endl;
 
     DWORD threadid;
     thread1 = CreateThread(NULL, 0, receive, &server, 0, &threadid);
     if(thread1==NULL)
        cout<<GetLastError();
     thread2 = CreateThread(NULL, 0, send, &server, 0, &threadid);
     if(thread2==NULL)
        cout<<"Thread creation error: "<<GetLastError();
     WaitForSingleObject(thread1,INFINITE);
     WaitForSingleObject(thread2,INFINITE);
     closesocket(server);
     WSACleanup();
     cout<<"Socket closed"<<"\n";
    }
    catch(exception& e)
    {
        cout << e.what() << '\n';
    }
    
    
}