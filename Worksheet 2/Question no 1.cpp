


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


