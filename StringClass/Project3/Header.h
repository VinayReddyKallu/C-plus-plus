#include<iostream>
using namespace std;
//String class 
class String {

public:
	char* _string = NULL;
	int length = 0;
	String();
	String(const char* _string1, int len);
	~String();
	String(const String& ConcatString);
	String operator+(const String& str);
	char& operator[] (int x);
	String& operator=(const String& chr);
	char& operator *();
	friend ostream& operator<< (std::ostream& out, const String& str);

}; 
//User Defined Exception Class
class CheckForValid :public exception {
public:
	const char* what() const throw()
	{
		return "Please enter the integer";
	}
};

