//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
#include <random>
using namespace std;

//Declaring the function signature
void mergeSort(int* A, int left, int right);
void merge(int* A, int left, int mid, int right);
void DisplayArray(int* A, int size);

int main() {
	int size = 30;
	int Aray[30];

	//Generating the random integer as mentioned in the reference given
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(1, 100);

	for (int n = 0; n != 30; ++n)
		Aray[n] = distrib(gen);

	//Displaying the array before sorting the array
	cout << "Generated random array : ";
	DisplayArray(Aray, size);

	mergeSort(Aray, 0, size - 1);

	//Displaying the array after sorting the array
	cout << "Sorted elements of array : ";
	DisplayArray(Aray, size);

	// Implementation of logic to sort an already sorted array
	int sortedArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	cout << "Already sorted array before sorting:\n";
	DisplayArray(sortedArray, 10);

	//Calling the function
	mergeSort(sortedArray, 0, 9);

	cout << "Array after sorting:\n";
	DisplayArray(sortedArray, 10);

	return 0;
}

//Function to display the array
void DisplayArray(int* A, int size) {
	for (int i = 0; i < size; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}

//Implemetation of the merge pseudo code
void mergeSort(int* A, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSort(A, left, mid);
		mergeSort(A, mid + 1, right);
		merge(A, left, mid, right);
	}
}

//Implemetation of the merge sort pseudo code
void merge(int* A, int left, int mid, int right) {
	// Check if both sub-arrays are already sorted
	if (A[mid] <= A[mid + 1]) {
		return; // Skip the merge process
	}

	int n1 = mid - left + 1;
	int n2 = right - mid;
	int* L = new int[n1 + 1]; //Forming a dynamic memory allocated array
	int* R = new int[n2 + 1];
	for (int i = 0; i < n1; i++) {
		L[i] = A[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = A[mid + j + 1];
	}
	L[n1] = 2147483647; //Using the maximum size of the datatype INT used
	R[n2] = 2147483647; //Using the maximum size of the datatype INT used
	int i = 0;
	int j = 0;
	for (int k = left; k <= right; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i = i + 1;
		}
		else {
			A[k] = R[j];
			j = j + 1;
		}
	}
	delete[] L;
	delete[] R; //deleting the array from the heap
}