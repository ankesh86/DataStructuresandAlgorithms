//Name - Ankesh Kumar
//NU ID - 002208893

//Declaring standard library
#include <iostream>
using namespace std;

//Declaring struct for student
struct Stud {
	char LastName[50];
	int Age;
	int Grade;
};

// function declaration
void getRecord(Stud* students, int size);
void getMedian(Stud* students, int size);
void getAverage(Stud* students, int size);
void calculateAndDisplay(Stud* students, int size);


int main() { // Main function
	int size;

	cout << "What is the size of the class: "; //Asking size of class
	cin >> size;

	Stud* students = new Stud[size]; //Dynamic memory allocation

	getRecord(students, size); //Fetching the Record from user
	getMedian(students, size); //Get median
	getAverage(students, size); // Get average
	calculateAndDisplay(students, size); // Print top 2 grade and lower 2 grade and their LastName

	delete[] students; //Deleting allocated array

	return 0;
};

// Function to get student records
void getRecord(Stud* students, int size) {
	cout << "Enter student details:\n";
	for (int i = 0; i < size; i++) {
		cout << "Student " << i + 1 << ":\n";
		cout << "LastName: "; //Entering LastName
		cin >> students[i].LastName;
		cout << "Age (between 16 and 40): "; //Entering Age
		cin >> students[i].Age;
		cout << "Grade (between 0 and 100): "; //Entering Grade
		cin >> students[i].Grade;
	}
}

//To sort the data of Age
void insertionSortAges(Stud* students, int size) {
	for (int i = 1; i < size; i++) {
		Stud key = students[i];
		int j = i - 1;

		// Move elements of students[0..i-1] that are greater than key.Age to one position ahead of their current position
		while (j >= 0 && students[j].Age > key.Age) {
			students[j + 1] = students[j];
			j = j - 1;
		}
		students[j + 1] = key;
	}
}

void getMedian(Stud* students, int size) {
	// Use insertion sort to sort the array of Age
	insertionSortAges(students, size);

	// Calculating the median
	double AgeMedian;
	int midsize = size / 2;

	// If the size is odd, taking the middle value
	if (size % 2 != 0) {
		AgeMedian = students[midsize].Age;
	}
	else {
		// If the size is even, we take average of the two middle values
		AgeMedian = (students[midsize - 1].Age + students[midsize].Age) / 2.0;
	}

	cout << "Median of ages: " << AgeMedian << endl; //Print median value
}

//Function to calculate Average of Grade
void getAverage(Stud* students, int size) {
	int totalGrades = 0;
	for (int i = 0; i < size; i++) { //Loop to sum all the grades
		totalGrades += students[i].Grade;
	}
	double averageGrade = static_cast<double>(totalGrades) / size; //Divide the Sum of grade by the size of student to get average
	cout << "Average of grades: " << averageGrade << endl;
}

// Function to perform required calculations
void calculateAndDisplay(Stud* students, int size) {

	// Find and display the top two students with the highest grades
	int highestGrade1 = -1, highestGrade2 = -1; //Set the minimum grade student can achieve
	int a1 = 0, a2 = 0;
	for (int i = 0; i < size; i++) {
		if (students[i].Grade > highestGrade1) { //Loop to find the index of top 2 grades
			highestGrade2 = highestGrade1;
			a2 = a1;

			highestGrade1 = students[i].Grade;
			a1 = i;
		}
		else if (students[i].Grade > highestGrade2) {
			highestGrade2 = students[i].Grade;
			a2 = i;
		}
	}
	cout << "Top two students with highest grades: \n"; //Printing the grades 
	cout << "Student Last Name is " << students[a1].LastName << " and Grade is " << students[a1].Grade << endl;
	cout << "Student Last Name is " << students[a2].LastName << " and Grade is " << students[a2].Grade << endl;

	// Find and display the two students with the lowest grades
	int lowestGrade1 = 101, lowestGrade2 = 101; //Set the maximum grade student can achieve
	int index1 = 0;
	int index2 = 0;

	for (int i = 0; i < size; i++) {
		if (students[i].Grade < lowestGrade1) { //Loop to find the index of lower 2 grades
			lowestGrade2 = lowestGrade1;
			index2 = index1;

			lowestGrade1 = students[i].Grade;
			index1 = i;
		}
		else if (students[i].Grade < lowestGrade2) {
			lowestGrade2 = students[i].Grade;
			index2 = i;
		}
	}
	cout << "Two students with lowest grades:\n"; //Printing the grades 
	cout << "Student Last Name is " << students[index1].LastName << " and Grade is " << students[index1].Grade << endl;
	cout << "Student Last Name is " << students[index2].LastName << " and Grade is " << students[index2].Grade << endl;
}