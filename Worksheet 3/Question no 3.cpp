#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class InvalidMarksException {};

class Student {
public:
    int roll;
    string name;
    float marks;

    Student(int r, string n, float m) {
        if (m < 0 || m > 100) throw InvalidMarksException();
        roll = r;
        name = n;
        marks = m;
    }

    void writeToFile(ofstream &file) {
        file << roll << " " << name << " " << marks << endl;
    }

    static void readFromFile() {
        ifstream file("students.txt");
        int r;
        string n;
        float m;
        cout << "Student Records:\n";
        while (file >> r >> n >> m)
            cout << "Roll: " << r << ", Name: " << n << ", Marks: " << m << endl;
        file.close();
    }
};

int main() {
    vector<Student> students;
    int roll;
    string name;
    float marks;

    cout << "Enter new student record:\n";
    cout << "Roll Number: "; cin >> roll;
    cout << "Name: "; cin >> name;
    cout << "Marks: "; cin >> marks;

    try {
        students.push_back(Student(roll, name, marks));
        ofstream file("students.txt", ios::app);
        students.back().writeToFile(file);
        file.close();
        cout << "Record added successfully.\n";
    } catch (...) {
        cout << "Invalid marks entered! Marks must be between 0 and 100.\n";
    }

    Student::readFromFile();
    return 0;
}

