//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
using namespace std;

// Declaring Temp_Array globally
int* Temp_Array;

// FibonacciD function with dynamic programming
int FibonacciD(int n) {
    // for Base cases we have 1 as output.
    if (n <= 1)
        return n;

    if (Temp_Array[n] != -1)
        return Temp_Array[n];

    // Recursively calling the function
    Temp_Array[n] = FibonacciD(n - 1) + FibonacciD(n - 2);
    return Temp_Array[n]; //Updating data in the global array for memorization
}

// FibonacciR function using recursion
int FibonacciR(int n) {
    if (n <= 1)
        return n;

    return FibonacciR(n - 1) + FibonacciR(n - 2);
}

int main() {
    int n; //The user inputs this number to calculate its Fibonacci sequence
    cout << "n = ";
    cin >> n;

    Temp_Array = new int[n + 1]; // Allocating memory for Temp_Array

    // initializing all elements in array Temp_Array to an invalid Fibonacci value
    for (int i = 0; i <= n; i++)  
        Temp_Array[i] = -1;

    // Find Fibonacci sequence n using the Dynamic programming function
    cout << " FibonacciD(n) = " << FibonacciD(n);
    // Find Fibonacci sequence n using the recursive only function
    cout << "\n FibonacciR(n) = " << FibonacciR(n);

    // Deallocate memory for Temp_Array
    delete[] Temp_Array;

    return 0;
}
