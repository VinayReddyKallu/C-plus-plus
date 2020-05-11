#include <Windows.h>
#include <tchar.h>
#include <string>
#include <cstdio>
#include <winsock2.h>
#include <iostream>
using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1234
#define MAX_BUFFER_SIZE 256

SOCKET server, client;
WSADATA WSAData;
SOCKADDR_IN serverAddr, clientAddr;
HANDLE  hThread ;

void writeToFile(char* file_name,char* data){
    string path="C:\\Users\\VK185157\\OneDrive - NCR Corporation\\Desktop\\repos\\Services\\";
    path+=file_name;
    FILE *fp = fopen(path.c_str(), "a+");
    fputs(data,fp);
    fclose(fp);
    //SetEvent(g_ServiceStopEvent)
}
void createserver()
{
    
 
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1234);
    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
}

void listen_accpet()
{
    listen(server, 0);

    cout << "Waiting for client to come online\n" << endl;

    int clientAddrSize = sizeof(clientAddr);
    if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {   

    char buffer[1024], buffer1[1024];

    recv(client, buffer, sizeof(buffer), 0);
     recv(client, buffer1, sizeof(buffer1), 0);
    writeToFile(buffer,buffer1);
        
       
    }
}


SERVICE_STATUS        g_ServiceStatus = {0};
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
HANDLE                g_ServiceStopEvent = INVALID_HANDLE_VALUE;

VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv);
VOID WINAPI ServiceCtrlHandler (DWORD);
DWORD WINAPI ServiceWorkerThread (LPVOID lpParam);
 
#define SERVICE_NAME  _T("My Sample Service")   
int _tmain (int argc, TCHAR *argv[])
{
    SERVICE_TABLE_ENTRY ServiceTable[] = 
    {
        {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
        {NULL, NULL}
    };
 
    if (StartServiceCtrlDispatcher (ServiceTable) == FALSE)
    {
        return GetLastError ();
    }
 
    return 0;
}
VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv)
{
    DWORD Status = E_FAIL;
 
    // Register our service control handler with the SCM
    g_StatusHandle = RegisterServiceCtrlHandler (SERVICE_NAME, ServiceCtrlHandler);
 
    if (g_StatusHandle == NULL) 
    {
        goto EXIT;
    }
 
    // Tell the service controller we are starting
    ZeroMemory (&g_ServiceStatus, sizeof (g_ServiceStatus));
    g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;
 
    if (SetServiceStatus (g_StatusHandle , &g_ServiceStatus) == FALSE)
    {
        OutputDebugString(_T(
          "My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }
 
    /*
     * Perform tasks necessary to start the service here
     */
    createserver();
 
    // Create a service stop event to wait on later
    g_ServiceStopEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL) 
    {   
        // Error creating event
        // Tell service controller we are stopped and exit
        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        g_ServiceStatus.dwWin32ExitCode = GetLastError();
        g_ServiceStatus.dwCheckPoint = 1;
 
        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
	{
	    OutputDebugString(_T(
	      "My Sample Service: ServiceMain: SetServiceStatus returned error"));
	}
        goto EXIT; 
    }    
    
    // Tell the service controller we are started
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;
 
    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        OutputDebugString(_T(
          "My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }
 
    // Start a thread that will perform the main task of the service
     hThread = CreateThread (NULL, 0, ServiceWorkerThread, NULL, 0, NULL);
   
    // Wait until our worker thread exits signaling that the service needs to stop
    WaitForSingleObject (hThread, INFINITE);
   
    
    /*
     * Perform any cleanup tasks 
     */
 
    CloseHandle (g_ServiceStopEvent);
 
    // Tell the service controller we are stopped
    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 3;
 
    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        OutputDebugString(_T(
          "My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }
    
EXIT:return;
}

VOID WINAPI ServiceCtrlHandler (DWORD CtrlCode)
{
    switch (CtrlCode) 
	{
     case SERVICE_CONTROL_STOP :
 
        if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
           break;
 
        /* 
         * Perform tasks necessary to stop the service here 
         */
         

        closesocket(client); 
        closesocket(server);
        
        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
        g_ServiceStatus.dwWin32ExitCode = 0;
        g_ServiceStatus.dwCheckPoint = 4;
 
        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
        {
            OutputDebugString(_T(
              "My Sample Service: ServiceCtrlHandler: SetServiceStatus returned error"));
        }
 
        // This will signal the worker thread to start shutting down
        SetEvent (g_ServiceStopEvent);
 
        break;
 
     default:
         break;
    }
}
DWORD WINAPI ServiceWorkerThread (LPVOID lpParam)
{
    //  Periodically check if the service has been requested to stop
    while (WaitForSingleObject(g_ServiceStopEvent, 0) != WAIT_OBJECT_0)
    {        
        /* 
         * Perform main service function here
         */
        listen_accpet();
        //  Simulate some work by sleeping
        Sleep(3000);
    }
 
    return ERROR_SUCCESS;
}