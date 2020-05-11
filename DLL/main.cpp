#include "main.h"
#include<fstream>
#include<iostream>
#include<windows.h>
using namespace std;
// a sample exported function
void DLL_EXPORT file_write(char txt[])
{
    ofstream file1;
    file1.open("sample.txt");
    if(file1.is_open()){
        file1<<txt;
        cout<<"File is written"<<endl;
    }
}
void DLL_EXPORT file_read()
{
    ifstream file1;
    file1.open("sample.txt");
    cout<<"File is opened"<<" "<<"."<<endl;
    if(file1.is_open()){
    char x;
    while(file1>>x)
        cout<<x;
    file1.close();
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
