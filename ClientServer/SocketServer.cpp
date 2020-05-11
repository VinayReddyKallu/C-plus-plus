#include <iostream>
#include <winsock2.h>
#include <string.h>
 using namespace std;
 
DWORD WINAPI receive(LPVOID lpParam)
{
    try
    {
        /* code */
        char buffer[1024]={0};
    SOCKET client = *(SOCKET *)lpParam;
    while(1)
    {
        if(recv(client, buffer, sizeof(buffer), 0)==SOCKET_ERROR)
        {
            cout<<"receive function failed"<<WSAGetLastError()<<endl;
            return 0;
        }
        if(strcmp(buffer,"exit")==0)
           break;
        cout<<"Client: "<<buffer<<endl;
 
        memset(buffer,0,sizeof(buffer));
    }
    }
    catch(exception& e)
    {
        cout<< e.what() << '\n';
    }
    
    
    return 0;
}
 
DWORD WINAPI send(LPVOID lpParam)
{
    try
    {
        /* code */
        char buffer[1024]={0};
    SOCKET client = *(SOCKET *)lpParam;
    while(1)
    {
        cout<<"Enter some text to send or Enter exit"<<"\n";
        gets(buffer);
 
        if(send(client, buffer, sizeof(buffer), 0)==SOCKET_ERROR)
        {
            cout<<"send falied with error: "<<WSAGetLastError()<<endl;
            return 0;
        }
        if(strcmp(buffer,"exit")==0)
        {
            break;
        }
    }
    }
    catch(exception& e)
    {
        cout<< e.what() << '\n';
    }
    
    
    return 0;
}
 
int main()
{
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    HANDLE thread1,thread2;
    try
    {
        if((server = socket(AF_INET, SOCK_STREAM, 0))==INVALID_SOCKET)
    {
        cout<<"Socket creation failed"<<WSAGetLastError()<<endl;
        return 0;
    }
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
 
    if(bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr))==SOCKET_ERROR)
    {
        cout<<"bind function caused an error "<<WSAGetLastError()<<endl;
        return 0;
    }
 
    if(listen(server, 0)==SOCKET_ERROR)
    {
        cout<<"listen function caused an error"<<WSAGetLastError()<<endl;
        return 0;
    }
 
    cout << "Listening..." << endl;
 
    char buffer[100];
    int clientAddrSize = sizeof(clientAddr);
    if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) == INVALID_SOCKET)
    {
        cout<<"accept function caused an error"<<WSAGetLastError()<<endl;
        return 0;
    }
    cout << "Client is  connected." << endl;
 
    DWORD threadid;
    thread1 = CreateThread(NULL, 0, receive, &client, 0, &threadid);
    if(thread1 == NULL)
        cout<<GetLastError();
    thread2 = CreateThread(NULL, 0, send, &client, 0, &threadid);
    if(thread2==NULL)
        cout<<"Thread creation error: "<<GetLastError();
    WaitForSingleObject(thread1,INFINITE);   
    WaitForSingleObject(thread2,INFINITE);
 
    closesocket(client);
    cout << "Client disconnected." << endl;
 
    if(closesocket(server)==SOCKET_ERROR)
    {
        cout<<"closeSocket failed with error: "<<WSAGetLastError()<<endl;
        return 0;
    }
 
    WSACleanup();
    }
    
    catch(exception& e)
    {
        cout<< e.what() << '\n';
    }
    
    
}