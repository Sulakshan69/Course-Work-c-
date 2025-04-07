Write a program that manages a simple student grade calculator with the following requirements. Create a Student class that has: 
1.	Student name (string)
2.	Three subject marks (integers)
3.	A basic member function to calculate average

The program should: 
1.	Accept student details (name and marks) from user input
2.	Calculate and display: 
1.	Total marks
2.	Average marks
3.	Grade (A for ≥90%, B for ≥80%, C for ≥70%, D for ≥60%, F for <60%)
3.	Display a message if any mark is below 0 or above 100



#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int marks[3];

public:
    void inputDetails() {
        cout << "Enter student name: ";
        getline(cin, name);

        for (int i = 0; i < 3; i++) {
            cout << "Enter marks for subject " << (i + 1) << ": ";
            cin >> marks[i];

            if (marks[i] < 0 || marks[i] > 100) {
                cout << "Invalid marks entered! Marks should be between 0 and 100." << endl;
                exit(1);
            }
        }
    }

    int getTotalMarks() {
        return marks[0] + marks[1] + marks[2];
    }

    float getAverageMarks() {
        return getTotalMarks() / 3.0;
    }

    char getGrade() {
        float avg = getAverageMarks();
        if (avg >= 90) return 'A';
        else if (avg >= 80) return 'B';
        else if (avg >= 70) return 'C';
        else if (avg >= 60) return 'D';
        else return 'F';
    }

    void displayResult() {
        cout << "\nStudent Name: " << name << endl;
        cout << "Total Marks: " << getTotalMarks() << endl;
        cout << "Average Marks: " << getAverageMarks() << endl;
        cout << "Grade: " << getGrade() << endl;
    }
};

int main() {
    Student student;
    student.inputDetails();
    student.displayResult();
    return 0;
}


