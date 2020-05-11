#include <iostream>
#include <windows.h>
#include<fstream>
#include <winsock2.h>
#include <tchar.h>
#include <string>
#include <cstdio>
using namespace std;
#define SERVICE_NAME  TEXT("My Service") 
SERVICE_STATUS s_status={0};
SERVICE_STATUS_HANDLE s_handle=0;
HANDLE stop_event=INVALID_HANDLE_VALUE;
WSADATA WSAData;
SOCKET server, client;
SOCKADDR_IN serverAddr, clientAddr;
DWORD WINAPI receive1(LPVOID lpParam);
void writeToFile(char* file_name,char* data){
    string path="C:\\Users\\VK185157\\OneDrive - NCR Corporation\\Desktop\\repos\\Services\\";
    path+=file_name;
    FILE *fp = fopen(path.c_str(), "a+");
    fputs(data,fp);
    fclose(fp);

}
void createSocket()
{
    WSAStartup(MAKEWORD(2,0), &WSAData);
      if((server = socket(AF_INET, SOCK_STREAM, 0))==INVALID_SOCKET)
    {
        cout<<"Socket creation failed"<<WSAGetLastError()<<endl;
        //return 0;
    }
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
 
    if(bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr))==SOCKET_ERROR)
    {
       // cout<<"bind function caused an error "<<WSAGetLastError()<<endl;
        //return 0;
    }
 
}
void listenAndAccept()
{
    if(listen(server, 0)==SOCKET_ERROR)
    {
        cout<<"listen function caused an error"<<WSAGetLastError()<<endl;
        
    }
 
    cout << "Listening..." << endl;
 
    //char buffer[100];
    int clientAddrSize = sizeof(clientAddr);
    if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) == INVALID_SOCKET)
    {
        cout<<"accept function caused an error"<<WSAGetLastError()<<endl;
       
    }
    cout << "Client is  connected." << endl;
    char buffer[1024], buffer1[1024];

    recv(client, buffer, sizeof(buffer), 0);
    recv(client, buffer1, sizeof(buffer1), 0);
    writeToFile(buffer,buffer1);
}

           
DWORD WINAPI ServiceWorkerThread (LPVOID lpParam)
{
    //  Periodically check if the service has been requested to stop
    while (WaitForSingleObject(stop_event, 0) != WAIT_OBJECT_0)
    {        
        listenAndAccept();
        Sleep(3000);
    }
 
    return ERROR_SUCCESS;
}
 
VOID WINAPI ServiceCtrlHandler (DWORD CtrlCode)
{
    switch (CtrlCode) 
    {
        case SERVICE_CONTROL_STOP :
    
            if (s_status.dwCurrentState != SERVICE_RUNNING)
                break;
    
            //closesocket(server); //CLOSING THE SOCKETS
            closesocket(client);
            s_status.dwControlsAccepted = 0;
            s_status.dwCurrentState = SERVICE_STOP_PENDING;
            s_status.dwWin32ExitCode = 0;
            s_status.dwCheckPoint = 4;
    
            if (SetServiceStatus (s_handle, &s_status) == FALSE)
            {
                OutputDebugString(TEXT("My Service: ServiceCtrlHandler: SetServiceStatus returned error"));
            }
    
            // This will signal the worker thread to start shutting down
            SetEvent (stop_event);
    
            break;
    
        default:
            break;
    }
}
 
VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv) // SERVICE ENTRY POINT 
{
    DWORD Status = E_FAIL;
 
   // Register our service control handler with the SCM
    s_handle = RegisterServiceCtrlHandler (SERVICE_NAME, ServiceCtrlHandler);
 
    if (s_handle == NULL) 
    {
        return;
    }
 
    // Tell the service controller we are starting
    ZeroMemory (&s_status, sizeof (s_status));
    s_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    s_status.dwControlsAccepted = 0;
    s_status.dwCurrentState = SERVICE_START_PENDING;
    s_status.dwWin32ExitCode = 0;
    s_status.dwServiceSpecificExitCode = 0;
    s_status.dwCheckPoint = 0;
 
    if (SetServiceStatus (s_handle , &s_status) == FALSE)
    {
        OutputDebugString(TEXT("My Service: ServiceMain: SetServiceStatus returned error"));
    }

    createSocket();
    // Create a service stop event to wait on later
    stop_event = CreateEvent (NULL, TRUE, FALSE, NULL);
    if (stop_event == NULL) 
    {   
        // Error creating event
        // Tell service controller we are stopped and exit
        s_status.dwControlsAccepted = 0;
        s_status.dwCurrentState = SERVICE_STOPPED;
        s_status.dwWin32ExitCode = GetLastError();
        s_status.dwCheckPoint = 1;
 
        if (SetServiceStatus (s_handle, &s_status) == FALSE)
        {
            OutputDebugString(TEXT("My Service: ServiceMain: SetServiceStatus returned error"));
        }
        return;
    }    
    
    // Tell the service controller we are started
    s_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    s_status.dwCurrentState = SERVICE_RUNNING;
    s_status.dwWin32ExitCode = 0;
    s_status.dwCheckPoint = 0;
 
    if (SetServiceStatus (s_handle, &s_status) == FALSE)
    {
        OutputDebugString(TEXT("My Service: ServiceMain: SetServiceStatus returned error"));
    }
    HANDLE hThread = CreateThread (NULL, 0, ServiceWorkerThread, NULL, 0, NULL);
    WaitForSingleObject (hThread, INFINITE);
    CloseHandle (stop_event);
    s_status.dwControlsAccepted = 0;
    s_status.dwCurrentState = SERVICE_STOPPED;
    s_status.dwWin32ExitCode = 0;
    s_status.dwCheckPoint = 3;
    if (SetServiceStatus (s_handle, &s_status) == FALSE)
    {
        OutputDebugString(TEXT("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }
    EXIT:return;
}
int _tmain (int argc, TCHAR *argv[]) // MAIN ENTRY FUNCTION
{
    SERVICE_TABLE_ENTRY ServiceTable[] = 
    {
        {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
        {NULL, NULL}
    };
    if (StartServiceCtrlDispatcher (ServiceTable) == FALSE)
        return GetLastError ();
    return 0;
}