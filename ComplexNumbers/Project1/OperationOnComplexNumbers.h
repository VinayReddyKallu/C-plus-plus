// program to perform addition,Subtraction,multiplication on complex numbers
#include<iostream>
using namespace std;
//class Complex containing methods to perform operations on the complex numbers
class Complex {
private:
	int real;
	int imaginary;
public:
	Complex() {// default constructor
	}
	Complex(int tempreal, int tempimaginary) {// Paremeterized constructor

		real = tempreal;
		imaginary = tempimaginary;
	}
	Complex operator+(Complex const& SecondComplexNumber) {// overloading of the addition operator
		Complex AdditionResult;
		AdditionResult.real =real + SecondComplexNumber.real;
		AdditionResult.imaginary =imaginary + SecondComplexNumber.imaginary;
		return AdditionResult;


	}
	Complex operator-(Complex const& SecondComplexNumber) {// overloading of the Subtraction operator
		Complex SubtractionResult;
		SubtractionResult.real = (real - SecondComplexNumber.real);
		SubtractionResult.imaginary = (imaginary - SecondComplexNumber.imaginary);
		return SubtractionResult;


	}
	Complex operator*(Complex const& SecondComplexNumber) {// overloading of the "*" operator
		Complex MultiplicationResult;
		MultiplicationResult.real = (real * SecondComplexNumber.real)-(imaginary*SecondComplexNumber.imaginary);
		MultiplicationResult.imaginary = (real* SecondComplexNumber.imaginary)+(imaginary*SecondComplexNumber.real);
		return MultiplicationResult;


	}
	void printForAddition() {// Method printing the Addition result
		if(imaginary<0)
			cout<< "The Addition Result of the given Complex Numbers is: " << real << " - " << abs(imaginary)<<"i"<< "\n";
		else
		cout << "The Addition Result of the given Complex Numbers is: " << real << " + " << imaginary<<"i"<< "\n";
	}
	void printForSubtraction() {// Method printing the Subtraction result
		if (imaginary < 0)
			cout << "The Subtraction Result of the given Complex Numbers is: " << real << " - " << abs(imaginary)<<"i"<< "\n";
		else
		cout << "The Subtraction Result of the given Complex Numbers is: " << real << " + " << imaginary<<"i"<< "\n";
	}
	void printForMultiplication() {// Method printing the Multiplication result
		if (imaginary < 0)
			cout << "The Multipication Result of the given Complex Numbers is: " << real << " - " << abs(imaginary)<<"i"<< "\n";
		else
		cout << "The Multipication Result of the given Complex Numbers is: " << real << " + " << imaginary<<"i"<< "\n";
	}


};
int main() {
	int real, imaginary;
	cout << "Enter real part and imaginary part of the First complex number" << "\n";
	cin >> real >> imaginary;
	Complex FirstNumber(real, imaginary);
	cout << "Enter real part and imaginary part of the Second complex number" << "\n";
	cin >> real >> imaginary;
	Complex SecondNumber(real, imaginary);
	Complex ResultForAddition = FirstNumber + SecondNumber;//calling method for addition
	ResultForAddition.printForAddition();
	Complex ResultForSubtraction = FirstNumber - SecondNumber;//calling method for subtraction
	ResultForSubtraction.printForSubtraction();
	Complex ResultForMultiplication = FirstNumber * SecondNumber;// calling method for multiplication
	ResultForMultiplication.printForMultiplication();
	

}
