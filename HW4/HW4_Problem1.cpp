//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
#include <chrono> // For seeding srand with the current time
#include <fstream> //For generating the file output
#include <stdexcept>
using namespace std;

// Global variables for tracking comparisons and movements
int comps = 0, moves = 0;

// Function declarations 
void copyArray(const int source[], int destination[], int n);
bool checkSortedArray(const int arr[], int n); // Added function declaration
void resetCounters();

//Declaring algorithms function
void SelectionSort(int* A, int size);
void BubbleSort(int* A, int size);
void InsertionSort(int* A, int size);
void mergeSort(int* A, int left, int right);
void HeapSort(int* A, int size);
void QuickSort(int* A, int p, int r);

int main() {
	ofstream outf;
	outf.open("sort.txt");
	if (outf.fail())
	{
		cerr << "Error: Could not open output file\n";
		exit(1);
	}

	// Generating average case array
	srand(time(NULL));

	int BST[2000], AVG[2000], WST[2000]; // Original arrays
	int tBST[2000], tAVG[2000], tWST[2000]; // Test arrays
	int size = 2000;
	// Generating average case array
	srand(time(NULL));
	for (int i = 0; i < 2000; i++)
		AVG[i] = rand();

	// Generating best case array
	for (int i = 0; i < 2000; i++)
		BST[i] = (i + 1) * 10;

	// Generating worst case array
	for (int i = 0; i < 2000; i++)
		WST[i] = 2000 - i;

	outf << "Algorithm\tType\tIsSorted\tComparisons\tMovements" << endl;

	// Selection Sort Test
	cout << "\nSelection Sort Tests:" << endl;
	moves = comps = 0;
	copyArray(BST, tBST, 2000);
	SelectionSort(tBST, 2000);
	cout << "Best Case - Sorted: " << checkSortedArray(tBST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "SelectionSort\ttBST" << "\t" << checkSortedArray(tBST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(AVG, tAVG, 2000);
	SelectionSort(tAVG, 2000);
	cout << "Average Case - Sorted: " << checkSortedArray(tAVG, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "SelectionSort\ttAVG" << "\t" << checkSortedArray(tAVG, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(WST, tWST, 2000);
	SelectionSort(tWST, 2000);
	cout << "Worst Case - Sorted: " << checkSortedArray(tWST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "SelectionSort\ttWST" << "\t" << checkSortedArray(tWST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	// Bubble Sort Test
	cout << "\nBubble Sort Tests:" << endl;

	copyArray(BST, tBST, 2000);
	BubbleSort(tBST, 2000);
	cout << "Best Case - Sorted: " << checkSortedArray(tBST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "BubbleSort\ttBST" << "\t" << checkSortedArray(tBST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(AVG, tAVG, 2000);
	BubbleSort(tAVG, 2000);
	cout << "Average Case - Sorted: " << checkSortedArray(tAVG, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "BubbleSort\ttAVG" << "\t" << checkSortedArray(tAVG, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(WST, tWST, 2000);
	BubbleSort(tWST, 2000);
	cout << "Worst Case - Sorted: " << checkSortedArray(tWST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "BubbleSort\ttWST" << "\t" << checkSortedArray(tWST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	// Insertion Sort Test
	cout << "\nInsertion Sort Tests:" << endl;

	copyArray(BST, tBST, 2000);
	InsertionSort(tBST, 2000);
	cout << "Best Case - Sorted: " << checkSortedArray(tBST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "InsertionSort\ttBST" << "\t" << checkSortedArray(tBST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(AVG, tAVG, 2000);
	InsertionSort(tAVG, 2000);
	cout << "Average Case - Sorted: " << checkSortedArray(tAVG, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "InsertionSort\ttAVG" << "\t" << checkSortedArray(tAVG, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(WST, tWST, 2000);
	InsertionSort(tWST, 2000);
	cout << "Worst Case - Sorted: " << checkSortedArray(tWST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "InsertionSort\ttWST" << "\t" << checkSortedArray(tWST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	// Merge Sort Test
	cout << "\nMerge Sort Tests:" << endl;

	copyArray(BST, tBST, 2000);
	mergeSort(tBST, 0, size - 1);
	cout << "Best Case - Sorted: " << checkSortedArray(tBST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "MergeSort\ttBST" << "\t" << checkSortedArray(tBST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(AVG, tAVG, 2000);
	mergeSort(tAVG, 0, size - 1);
	cout << "Average Case - Sorted: " << checkSortedArray(tAVG, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "MergeSort\ttAVG" << "\t" << checkSortedArray(tAVG, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(WST, tWST, 2000);
	mergeSort(tWST, 0, size - 1);
	cout << "Worst Case - Sorted: " << checkSortedArray(tWST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "MergeSort\ttWST" << "\t" << checkSortedArray(tWST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	// Heap Sort Test
	cout << "\nHeap Sort Tests:" << endl;

	copyArray(BST, tBST, 2000);
	HeapSort(tBST, 2000);
	cout << "Best Case - Sorted: " << checkSortedArray(tBST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "HeapSort\ttBST" << "\t" << checkSortedArray(tBST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(AVG, tAVG, 2000);
	HeapSort(tAVG, 2000);
	cout << "Average Case - Sorted: " << checkSortedArray(tAVG, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "HeapSort\ttAVG" << "\t" << checkSortedArray(tAVG, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(WST, tWST, 2000);
	HeapSort(tWST, 2000);
	cout << "Worst Case - Sorted: " << checkSortedArray(tWST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "HeapSort\ttWST" << "\t" << checkSortedArray(tWST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	// Quick Sort Test
	cout << "\nQuick Sort Tests:" << endl;

	copyArray(BST, tBST, 2000);
	QuickSort(tBST, 0, size - 1);
	cout << "Best Case - Sorted: " << checkSortedArray(tBST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "QuickSort\ttBST" << "\t" << checkSortedArray(tBST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(AVG, tAVG, 2000);
	QuickSort(tAVG, 0, size - 1);
	cout << "Average Case - Sorted: " << checkSortedArray(tAVG, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "QuickSort\ttAVG" << "\t" << checkSortedArray(tAVG, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	copyArray(WST, tWST, 2000);
	QuickSort(tWST, 0, size - 1);
	cout << "Worst Case - Sorted: " << checkSortedArray(tWST, 2000) << ", Comparisons: " << comps << ", Moves: " << moves << endl;
	outf << "QuickSort\ttWST" << "\t" << checkSortedArray(tWST, 2000) << "\t" << comps << "\t" << moves << endl;
	resetCounters();

	outf.close(); // Close the file at the end of your program.
	return 0;
}

void copyArray(const int source[], int destination[], int n) {
	for (int i = 0; i < n; i++) {
		destination[i] = source[i];
	}
}

bool checkSortedArray(const int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			return false; // The array is not sorted.
		}
	}
	return true; // The array is sorted.
}

void resetCounters() {
	comps = 0;
	moves = 0;
}

// Swap function that increments move counter
void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
	moves += 3; // Considering a swap as three moves
}

// Implementation of Selection Sort
void SelectionSort(int* A, int size) {
	for (int i = 0; i < size - 1; i++) {
		// Find the index of the minimum element
		int min_index = i;
		for (int j = i + 1; j < size; j++) {
			comps++; // Increment comps for each comparison
			if (A[j] < A[min_index]) {
				min_index = j;
			}
		}

		// Swap the found minimum element with the first element
		if (min_index != i) {
			swap(A[i], A[min_index]);
		}
	}
}

//Implementation of Bubble Sort
void BubbleSort(int* A, int size) {
	for (int i = 0; i < size - 1; i++) {
		// Track if any swap happened to optimize the bubble sort
		bool swapped = false;
		for (int j = 0; j < size - i - 1; j++) {
			comps++; // Increment comps for each comparison
			if (A[j] > A[j + 1]) {

				// Swap the elements
				swap(A[j], A[j + 1]);
				swapped = true;
			}
		}
		// If no two elements were swapped by inner loop, then break
		if (!swapped) {
			break;
		}
	}
}

// Implementation of the merge function
void merge(int* A, int left, int mid, int right) {
	// Check if both sub-arrays are already sorted
	if (A[mid] <= A[mid + 1]) {
		comps++; // Increment comparison
		return; // Skip the merge process
	}

	int n1 = mid - left + 1;
	int n2 = right - mid;
	int* L = new int[n1 + 1]; // Forming a dynamic memory allocated array
	int* R = new int[n2 + 1];

	for (int i = 0; i < n1; i++) {
		L[i] = A[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = A[mid + j + 1];
	}

	L[n1] = 2147483647; // Using the maximum size of the datatype used
	R[n2] = 2147483647;

	int i = 0, j = 0;
	for (int k = left; k <= right; k++) {
		comps++; // Increment comparison for each comparison made
		if (L[i] <= R[j]) {
			A[k] = L[i++];
			moves++; // Increment movement for each assignment
		}
		else {
			A[k] = R[j++];
			moves++; // Increment movement for each assignment
		}
	}

	delete[] L; // Deleting the array from the heap
	delete[] R;
}

// Implementation of the merge sort function
void mergeSort(int* A, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSort(A, left, mid);
		mergeSort(A, mid + 1, right);
		merge(A, left, mid, right);
	}
}

// Max-Heapify algorithm
void MaxHeapify(int* A, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n) {
		comps++; // Increment comps for comparison
		if (A[left] > A[largest])
			largest = left;
	}

	if (right < n) {
		comps++; // Increment comps for comparison
		if (A[right] > A[largest])
			largest = right;
	}

	if (largest != i) {
		swap(A[i], A[largest]);
		MaxHeapify(A, n, largest);
	}
}

// Building Maxheap
void BuildMaxHeap(int* A, int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		MaxHeapify(A, n, i);
}

// HeapSort Algorithm
void HeapSort(int* A, int n) {
	BuildMaxHeap(A, n);
	for (int i = n - 1; i >= 0; i--) {
		swap(A[0], A[i]);
		MaxHeapify(A, i, 0);
	}
}

//Quick Sort algorithm starts
int Partition(int* A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		comps++; // Increment comparisons
		if (A[j] <= x) {
			i = i + 1;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);
	return i + 1;
}

void QuickSort(int* A, int p, int r) {
	if (p < r) {
		int q = Partition(A, p, r);
		QuickSort(A, p, q - 1);
		QuickSort(A, q + 1, r);
	}
}

void InsertionSort(int* A, int size) {
	for (int i = 1; i < size; i++) {
		int key = A[i];
		int j = i - 1;
		comps++; // Increment comps for the comparison of key with A[j]
		while (j >= 0 && A[j] > key) {
			A[j + 1] = A[j];
			j = j - 1;
			moves++; // Increment moves for each movement of an element
		}
		A[j + 1] = key;
	}
}
