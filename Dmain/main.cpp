#include <iostream>
#include<windows.h>
using namespace std;

typedef VOID (*write)(char []);
typedef VOID(*read)();
int main()
{
    HINSTANCE hinst=LoadLibrary("DLL.dll");
    cout<<"Enter content"<<endl;
    char ch[100];
    cin.getline(ch,sizeof(ch));
    if(hinst!=NULL){
        write file_write=(write)GetProcAddress(hinst,"file_write");
        if(file_write!=NULL)
            file_write(ch);
        read file_read=(read)GetProcAddress(hinst,"file_read");
        if(file_read!=NULL)
            file_read();
        FreeLibrary(hinst);
    }
    return 0;
}
