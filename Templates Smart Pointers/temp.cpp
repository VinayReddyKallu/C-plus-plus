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
     SMART_PTR(T *pVal =0) throw()  //Constructor 
    {
        if(pVal)
            m_smart = pVal;
        else
            m_smart = NULL;
    }
    ~SMART_PTR() //Destructor
    {
       
            delete m_smart;
        
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
public:
    MyClass()
    {
        cout<<"Memory allocated"<<endl;
    }
    ~MyClass()
    {
        cout<<"Memory deallocated"<<endl;
    }
    //Function to display the string
    void display()
    {
        //strcpy(str,"Hello World!");
        cout<<"Hello World!"<<endl;
    }

};
int main()
{
    try
    {
        SMART_PTR<MyClass> b(new MyClass());
        b->display();
        SMART_PTR<MyClass>b1=b;
        b1->display();
        

        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
    
}
