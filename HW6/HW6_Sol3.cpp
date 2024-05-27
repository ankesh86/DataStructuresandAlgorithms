//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;

double Price(int L, int rodSize); //function to calculate price
double max(double a, double b); //Calculate maximum value between two
int DynamicCutRodAux(double price[], int n, double r[], steady_clock::time_point start_time, bool &timed_out); //
int DynamicCutRod(double price[], int n, steady_clock::time_point start_time, bool &timed_out); //Applying rod-cul algorithm
int RecursiveCutRod(double price[], int n, steady_clock::time_point start_time, bool &timed_out); //Applying recursive approach to rod cut method

int main() {
	int rodSizes[] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 }; //Initiating all the Rod Sizes
	int numSizes = sizeof(rodSizes) / sizeof(rodSizes[0]);

	cout << "Rod Size	Recursive Time	Recursive Max Revenue	Dynamic Time Dynamic	Max Revenue" << endl; //Header of Output

	//Looping to calculate all output for each Rod Size
	for (int j = 0; j < numSizes; j++) {
		int rodSize = rodSizes[j];
		double *price = new double[rodSize + 1];

		for (int i = 1; i <= rodSize; i++) {
			price[i] = Price(i, rodSize); // Corrected to pass both parameters
		}

		// Initializing timed_out to false before each approach
		bool timed_out = false;

		// Dynamic programming approach
		auto start_time = steady_clock::now();
		int DynamicResult = DynamicCutRod(price, rodSize, start_time, timed_out);
		auto durationDynamic = duration_cast<microseconds>(steady_clock::now() - start_time);
		if (timed_out) {
			cout << "No Solution(Timeout)" << rodSize << endl;
		}

		// Reseting timed_out for recursive approach
		timed_out = false;
		start_time = steady_clock::now();

		// Recursive approach
		int recursiveResult = RecursiveCutRod(price, rodSize, start_time, timed_out);
		auto durationRecursive = duration_cast<microseconds>(steady_clock::now() - start_time);
		if (timed_out) {
			cout << "No Solution(Timeout)" << rodSize << endl;
		}

		// Printing output
		cout << rodSize << "	" << durationRecursive.count() << "	" << recursiveResult << "	" << durationDynamic.count() << "	" << DynamicResult << endl;

		//Delocating the array
		delete[] price;
	}

	return 0;
}


// Function to calculate the price based on the formula given
double Price(int L, int rodSize) {
	if (L == 1) return 2.0;
	if (L < rodSize) return floor(L * 2.5);
	return (L * 2.5) - 1;
}

// Custom max function to find the maximum of two values
double max(double a, double b) {
	return (a > b) ? a : b;
}

// Function for the memoized approach with time checking
int DynamicCutRodAux(double price[], int n, double r[], steady_clock::time_point start_time, bool &timed_out) {
	if (duration_cast<seconds>(steady_clock::now() - start_time).count() >= 120) {
		timed_out = true;
		return -1; // This will act as an indicator that we've hit the timeout
	}

	if (r[n] >= 0) return r[n];
	double q;
	if (n == 0)
		q = 0;
	else {
		q = -1;
		for (int i = 1; i <= n; i++) {
			if (timed_out) break; // If timed out, exit the loop
			double result = DynamicCutRodAux(price, n - i, r, start_time, timed_out);
			if (!timed_out) q = max(q, price[i] + result);
		}
	}
	r[n] = q;
	return q;
}

// Memoized rod cutting function with time checking
int DynamicCutRod(double price[], int n, steady_clock::time_point start_time, bool &timed_out) {
	double *r = new double[n + 1];
	for (int i = 0; i <= n; i++) r[i] = -1;

	int result = DynamicCutRodAux(price, n, r, start_time, timed_out);

	delete[] r;
	return result;
}

// Recursive rod cutting function with time checking
int RecursiveCutRod(double price[], int n, steady_clock::time_point start_time, bool &timed_out) {
	if (duration_cast<seconds>(steady_clock::now() - start_time).count() >= 120) {
		timed_out = true;
		return -1; // This will act as an indicator that we've hit the timeout
	}

	if (n == 0) return 0;
	double q = -1;
	for (int i = 1; i <= n; i++) {
		if (timed_out) break; // If timed out, exit the loop
		double result = RecursiveCutRod(price, n - i, start_time, timed_out);
		if (!timed_out) q = max(q, price[i] + result);
	}
	return q;
}
