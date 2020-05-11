//Implementing the  string class with the help of char*
#include<iostream>
#include "Header.h"
#include<typeinfo>
using namespace std;
const int MAX_SIZE = 256;// Macro to define the max size
int flag = 1;
String::String()// Default constructor
{
	_string = NULL;
}
String::String(const char* _string1, int len)//parameterized constructor
{
	length = len;
	_string = new char[length + 1];
	int i = 0;
	while (_string1[i] != '\0')
	{
		_string[i] = _string1[i];
		i++;
	}
	_string[i] = '\0';

}
String::~String()//Destructor 
{
	
	if (this->_string != NULL)
	{
		delete[]_string;
		_string = NULL;

	}


}

String::String(const String& ConcatString)//copy constructor
{
	_string = new char[ConcatString.length + 1];
	length = ConcatString.length;
	int i = 0;
	while (ConcatString._string[i] != '\0')
	{
		_string[i] = ConcatString._string[i];

		i++;
	}
	_string[i] = '\0';
}

String String:: operator+(const String& str) {// overloading + operator 
	char* res = new char[this->length + str.length + 2];
	int i = 0, j = 0;
	while (_string[i] != '\0')
	{
		res[j] = _string[i];
		i++;
		j++;
	}
	i = 0;
	while (str._string[i] != '\0')
	{
		res[j] = str._string[i];
		i++;
		j++;
	}
	res[j] = '\0';
	String Obj(res, strlen(res));
	return Obj;
}
char& String:: operator[] (int x)//overloading [] operator
{
	
	//cout << typeid(strlen(_string)).name() << '\n';
	if (x >=int((strlen(_string))))
	{
		
		flag = 0;
		throw out_of_range(" please enter the integer within  range ");
	}
	else if (x < 0) {
		CheckForValid a;
		throw a;
	}
	else 
		return this->_string[x];
	
}

String& String::operator=(const String& chr)//overoading = operator
{
	if (this->_string != NULL)
	{
		delete[] _string;
		_string = NULL;

	}
	_string = new char[3];
	length = chr.length;
	int i = 0;
	while (chr._string[i] != '\0')
	{
		//cout << "c" << chr._string[i] << " ";
		_string[i] = chr._string[i];
		i++;
	}
	_string[i] = '\0';
	//cout << "this" << _string << "\n";
	return *this;
}
char& String::operator *() { // overloading * operator
	return *(_string);
}

ostream& operator<< (std::ostream& out, const String& String)//overloading << operator
{
	
	out << String._string << "\n";
	return out; 
}

//Function to find the length of the char *

int FindLength(const char* c)
{
	int i = 0,len=0;
	while (c[i] != '\0')
	{
		len++;
		i++;
	}
		
	return len;
}

int main() {
	char* _string, * _StringToConcat
		, * _searchchar, * _defstring;
	int index, checkToContinue;
	
	try {
		_string = new char[MAX_SIZE];
		_StringToConcat = new char[MAX_SIZE];
		_searchchar = new char[MAX_SIZE];
		_defstring = new char[MAX_SIZE];
		while (1) {
			flag = 1;
			cout << "Enter 1 to continue or 0 to exit" << "\n";
			cin >> checkToContinue;
			if (checkToContinue == 0)
				break;
			cout << "Enter the String you want to perfom operation" << "\n";
			cin >> _string;
			String string(_string,FindLength(_string));
			cout << "Enter the string you want to concat to the string " << _string << "\n";
			cin >> _StringToConcat;
			String StringToConcat(_StringToConcat, FindLength(_StringToConcat));
			//cout << s1._string << "\n";
			String ConcatString = string + StringToConcat;//calling + operator
			cout << "The Resultant Concatenated String is:" << ConcatString._string << "\n";
			cout << "Enter the string you want to dereference" << "\n";
			cin >> _defstring;
			String DefString(_defstring,FindLength(_defstring));
			char defchar = *DefString;// calling * opeartor
			cout << "The character deferenced is:" << defchar << "\n";
			String CopyString;
			 CopyString= StringToConcat;//Copying Object
			cout << "The copy object is:" << CopyString<< "\n";//Overloading the << operator
			cout << "Enter the String to retrieve any character at that  particular Index " << "\n";
			cin >> _searchchar;
			String Search(_searchchar,FindLength(_searchchar));//creating object to perform [] opeartion
			cout << "Enter the index to retrive the character at that index of the string: " << Search._string << "\n";
			cin >> index;
			//cout << Search._string;
			char ch = Search[index];
			if (flag == 1)
			{
				cout << "The character present at the given index  is:  " << ch << "\n";
			}
			
			
		}
	}
	catch (CheckForValid &t)
	{
		cout << t.what() << "\n";
	}
	
	catch (exception &e)
	{
		cout << e.what() << "\n";
	}

	return 0;


}