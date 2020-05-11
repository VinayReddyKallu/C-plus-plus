// Program to perform Addition,Subtraction,Multiplication of two integers
#include<iostream>
using namespace std;
// Class containg methods to perform Addition,Subtraction,Multiplication of integers
class Operations {
public:
	int FirstNumber, SecondNumber;

	Operations(int _FirstNumber, int _SecondNumber) {
		FirstNumber = _FirstNumber;
		SecondNumber = _SecondNumber;
	}
	void additionOfTwoIntegers() { //method to perform addition of two integers
		cout << "The Addition of the given two integers " << FirstNumber << " and " << SecondNumber << " is: " << " " << FirstNumber + SecondNumber << "\n";

	}

	void subtractionOfTwoIntegers() { //method to perform subtraction  of two integers
		cout << "The Subtraction  of the given two integers " << FirstNumber << " and " << SecondNumber << " is: " << " " << FirstNumber - SecondNumber << "\n";

	}

	void multiplicationOfTwoIntegers() { //method to perform Multiplication  of two integers
		cout << "The Multiplication  of the given two integers " << FirstNumber << " and " << SecondNumber << " is: " << " " << FirstNumber * SecondNumber << "\n";

	}


};
int main() {
	int FirstNumber, SecondNumber;
	cout << "Enter two space seperated integers:" << "\n";
	cin >> FirstNumber >> SecondNumber;// Taking user input of Two integers
	Operations op(FirstNumber,SecondNumber);
	op.additionOfTwoIntegers();//Calling addition of two Integers Method
	op.subtractionOfTwoIntegers();//Calling subtraction of two Integers Method
	op.multiplicationOfTwoIntegers();//Calling multiplication of two Integers Method
	return 0;
}