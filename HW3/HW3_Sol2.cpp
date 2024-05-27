//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
#include <random>
using namespace std;

//Function for displaying array
void DisplayArray(int* A, int size) {
	for (int i = 0; i < size; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}

//Declaring hash function as mentioned in question
int hashFunction(int k, int m) {
	return k % m;
}


//Function for calculating logic for the Collisons
void calculateAndDisplayCollisions(int* Aindex, int tableSize, int indexSize) {
	int* collisions = new int[tableSize]();

	for (int j = 0; j < indexSize; ++j) {
		collisions[Aindex[j]] += 1;
	}

	DisplayArray(collisions, tableSize);

	int max = collisions[0]; 
	for (int i = 1; i < tableSize; i++) {
		if (collisions[i] > max) {
			max = collisions[i];
		}
	}
	cout << "Maximum collisions (subtracting 1 to account for initial occupancy): " << max - 1 << endl;

	int min = collisions[0];
	for (int i = 1; i < tableSize; i++) {
		// Assuming at least one slot will have a collision or be empty, hence only considering slots with at least one mapping (collisions[i] > 0)
		if (collisions[i] < min && collisions[i] > 0) {
			min = collisions[i];
		}
	}

	// Adjusting output based on whether we consider a slot with a single element as having collisions
	cout << "Minimum collisions (subtracting 1 to account for slots without collisions): ";
	if (min > 1) {
		cout << min - 1 << endl; // Subtract 1 only if min > 1 to adjust for actual collisions
	}
	else {
		cout << "0 (no collisions or empty slots)" << endl; // Indicate no collisions or the presence of empty slots
	}

	// Calculate the total number of collisions
	int totalCollisions = 0;
	int occupiedSlots = 0; // Count of slots that had at least one entry (including non-colliding single entries)

	for (int i = 0; i < tableSize; i++) {
		if (collisions[i] > 1) { // Only slots with more than one entry count towards collisions
			totalCollisions += (collisions[i] - 1); // Subtract 1 to count only collisions, not the first, non-colliding entry
		}
		if (collisions[i] > 0) {
			occupiedSlots++; // Count every non-empty slot
		}
	}

	double meanCollisions = static_cast<double>(totalCollisions) / tableSize; // Mean across all slots, including empty ones

	cout << "Mean number of collisions per slot (including empty slots): " << meanCollisions << endl;
	
	// Assuming totalCollisions and tableSize have already been defined and meanCollisions has been calculated

	double squaredDifferencesSum = 0.0;
	for (int i = 0; i < tableSize; i++) {
		// For variance calculation, consider the actual number of collisions (collisions[i] - 1) if counting collisions
		double difference = (collisions[i] - 1) - meanCollisions;
		squaredDifferencesSum += difference * difference;
	}

	double variance = squaredDifferencesSum / tableSize; // Variance across all slots, including empty ones

	cout << "Variance of collisions across all slots: " << variance << endl;


	delete[] collisions;
}

int main() {
	int size = 1000;
	int ADate[1000];

	//Generating random array and comnbining to form according to the dates mentioned
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distribAdd(1, 28);
	uniform_int_distribution<> distribAmm(1, 12);
	uniform_int_distribution<> distribAyy(0, 4); // Assuming two-digit years for simplicity

	for (int n = 0; n < size; ++n) {
		ADate[n] = distribAdd(gen) * 10000 + distribAmm(gen) * 100 + distribAyy(gen);
	}

	cout << "Generated random array : ";
	DisplayArray(ADate, size);

	//Forming the hash functions by passing the value to function
	int tableSize1 = 97;
	int Aindex1[1000];
	for (int n = 0; n < size; ++n) {
		Aindex1[n] = hashFunction(ADate[n], tableSize1);
	}

	int tableSize2 = 98;
	int Aindex2[1000];
	for (int n = 0; n < size; ++n) {
		Aindex2[n] = hashFunction(ADate[n], tableSize2);
	}

	int tableSize3 = 100;
	int Aindex3[1000];
	for (int n = 0; n < size; ++n) {
		Aindex3[n] = hashFunction(ADate[n], tableSize3);
	}

	// Displaying the arrays for each hash table size by passing the parameters Array, Size of m, and size of array i.e. 1000
	cout << "\nCollisions for table size " << tableSize1 << ":\n";
	calculateAndDisplayCollisions(Aindex1, tableSize1, size);

	cout << "\nCollisions for table size " << tableSize2 << ":\n";
	calculateAndDisplayCollisions(Aindex2, tableSize2, size);

	cout << "\nCollisions for table size " << tableSize3 << ":\n";
	calculateAndDisplayCollisions(Aindex3, tableSize3, size);
}

