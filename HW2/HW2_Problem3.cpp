//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
using namespace std;

// function declaration
int F1(int n) {
	if (n == 0)
		return 1;
	return F1(n - 1) + F1(n - 1);
}

int F2(int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 0) {
		int result = F2(n / 2);
		return result * result;
	}
	else
		return 2 * F2(n - 1);
}

int main() {
	// Test functions with values for n between 1 and 10
	for (int n = 1; n <= 10; n++) {
		cout << "F1(" << n << "): " << F1(n) << endl;
		cout << "F2(" << n << "): " << F2(n) << endl;
		cout << endl;
	}

	//Testing function for n = 30 to see speed of the functions.
	cout << "F1(30): " << F1(30) << endl; //This runs for very long.
	cout << "F2(30): " << F2(30) << endl;

}
