#include<iostream>
using namespace std;
#include<thread>
#include<mutex>
mutex m;
class MyThread{
public:
	 void display()
    {
		 for (int i = 0; i < 100; i++)
		 {
			 m.lock();
			 cout << "I am Thread and my ID is:" << this_thread::get_id() << "\n";
			 m.unlock();
		 }
			
    }

};
int main()
{
	MyThread m1, m2;
	thread t1(&MyThread::display, &m1);
	thread t2(&MyThread::display, &m2);
	t1.join();
	t2.join();
	cout << "Successful" << "\n";
	return 0;
}