#include<iostream>
#include<string.h>
using namespace std;
//The template class definition for smart pointer
template<class T>
class SMART_PTR 
{
    private:
        T *m_smart;
public:
     SMART_PTR(T *pVal=0) throw()  //Constructor 
    {
        if(pVal)
            m_smart = pVal; 
        else
            m_smart = NULL;
    }
    ~SMART_PTR() //Destructor
    {
        if(m_smart)
        {
            delete m_smart;
        }
    }
    T *get() const throw() // Get function 
    {
        return m_smart;
    }
   
   
   T *operator->() const throw()
    {
        //cout<<"->"<<endl;
        return m_smart;
    }
    
};
// The Class Definition 
class MyClass
{
private:
    SMART_PTR<char>str;
public:
    MyClass(const char* s)
    {
        str=SMART_PTR<char>(new char[255]); 
        strcpy(str.get(),s);
        //cout<<"Memory allocated"<<endl;
    }
    //Function to display the string
    void display()
    {
        //strcpy(str,"Hello World!");
        cout<<str.get()<<endl;
    }

};
int main()
{
    try
    {
        SMART_PTR<MyClass> b(new MyClass("Hello World!"));
        b->display();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
    
}
