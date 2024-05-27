//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
using namespace std;

// function declaration
void swapP(int* numRef1, int* numRef2);
void swapR(int& numRef1, int& numRef2);

//Main function
int main() {
	int a{ 3 };
	int b{ 4 };
	cout << "Before swapping values for a : " << a << " and b : " << b << endl;
	swapR(a, b); //calling the function which would swap values using Pass-by-Reference concept
	cout << "After swapping, the values for a : " << a << " and b : " << b << endl;

	//New part - using Pass-by-Pointer concept
	int x{ 10 };
	int y{ 20 };
	cout << "Before swapping values for x : " << x << " and y : " << y << endl;
	swapP(&x, &y); //We pass the address by mentioning &a
	cout << "After swapping, the values for x : " << x << " and y : " << y << endl;
};

//Function for Pass-by-Reference
void swapR(int& numRef1, int& numRef2) { //dereferencing the addresses passed
	int temp = numRef1; //Declaring new variable placing the value in first address to temporary
	numRef1 = numRef2;
	numRef2 = temp; //The values at the address are changed.
};

//Function for Pass-by-Pointer
void swapP(int* numRef1, int* numRef2) {
	int temp = *numRef1; //Declaring new variable 
	*numRef1 = *numRef2; //Changing the values 
	*numRef2 = temp; 
}
