//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
using namespace std;

// function declaration
void MinFirst(int v[], int k);

int main() {
	//Declare array
	int v[] = { 6, 2, 7, 8, 1, 5 };
	//Bring Min value to beginning
	MinFirst(v, 6);
	//Print array
	for (int i = 0; i < 6; i++) {
		cout << v[i] << ' ';
	}
	return 0;
};

void MinFirst(int v[], int k) {
	int num1 = v[0]; //initiazing new variable
	int loc = 0; //initiazing new variable for storing location
	for (int i = 1; i < k; i++) //loop to get the minimum value and index
		if (num1 > v[i]) {
			num1 = v[i];
			loc = i;
		}

	int numToreplace = 0; //initiazing new variable to store the variable before replacing
	numToreplace = v[0];
	for (int i = 0; i < k + 1; i++) { //Loop to keep shifting the elements of array to next location
		if (i == loc) { //When we get the same location of minimum value, we break the loop and eexit as the loop is sorted till then
			break;
		}
		else { //Logic to shift the element by 1 location
			int numReplaced = 0;
			numReplaced = v[i + 1];
			v[i + 1] = numToreplace;
			numToreplace = numReplaced;
		}
	}
	v[0] = num1; //Setting the first location as minimum value
}