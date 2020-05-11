#include <iostream>
#include <winsock2.h>
#include <string.h> 
using namespace std; 
WSADATA wsadata;
SOCKADDR_IN addr;
SOCKET server;
#define MAX_BUFFER_SIZE 256
void  send()
{
    try
    {
        /* code */
        char buffer[MAX_BUFFER_SIZE];
 
        buffer[0]='\0';
        cin.getline(buffer,MAX_BUFFER_SIZE);
 
        send(server, buffer, sizeof(buffer), 0);

        memset(buffer, 0, sizeof(buffer));
    }
    catch(exception& e)
    {
        std::cout<< e.what() << '\n';
    }
    
    
}
 
int main()
{

    try
    {
         WSAStartup(MAKEWORD(2,0), &wsadata);
 
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
      
      //  thread1 = CreateThread(NULL, 0, send, &server, 0, &threadid);
      //  if(thread1==NULL)
      //  cout<<"Thread creation error: "<<GetLastError();
      //  WaitForSingleObject(thread1,INFINITE);
      cout<<"Enter the File Name"<<"\n";
      send();
      cout<<"Enter the data "<<"\n";
      send();
      closesocket(server);
      WSACleanup();
      cout<<"Socket closed"<<"\n";
    }
    catch(exception& e)
    {
        cout << e.what() << '\n';
    }
    
    return 0;
}