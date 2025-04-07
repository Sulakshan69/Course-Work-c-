#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BookManager {
    char titles[10][150];
    string filename;

public:
    void getBookTitles() {
        cout << "Enter the titles of 10 books:\n";
        cin.ignore();
        for (int i = 0; i < 10; i++) {
            cout << "Book " << i + 1 << ": ";
            cin.getline(titles[i], 150);
        }
    }

    void saveToFile() {
        cout << "Enter filename: ";
        cin >> filename;
        ofstream file(filename, ios::binary);
        file.write(reinterpret_cast<char *>(titles), sizeof(titles));
        file.close();
    }

    void searchBook() {
        char searchTitle[150];
        cout << "Enter book title to search: ";
        cin.ignore();
        cin.getline(searchTitle, 150);
        ifstream file(filename, ios::binary);
        file.read(reinterpret_cast<char *>(titles), sizeof(titles));
        file.close();
        for (int i = 0; i < 10; i++) {
            if (strcmp(titles[i], searchTitle) == 0) {
                cout << "Book found!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }
};

class Student {
public:
    int roll;
    string name;
    int marks;

    void input() {
        cout << "Enter Roll, Name, Marks: ";
        cin >> roll >> ws;
        getline(cin, name);
        cin >> marks;
        if (marks < 0 || marks > 100) throw invalid_argument("Invalid marks!");
    }

    void saveToFile(ofstream &file) {
        file << roll << '\n' << name << '\n' << marks << '\n';
    }
};

int main() {
    int choice;
    string studentFile = "students.txt";
    BookManager bm;
    do {
        cout << "\n1. Add Books\n2. Save Books\n3. Search Book\n4. Add Student Record\n5. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) bm.getBookTitles();
        else if (choice == 2) bm.saveToFile();
        else if (choice == 3) bm.searchBook();
        else if (choice == 4) {
            ofstream file(studentFile, ios::app);
            Student s;
            try { s.input(); s.saveToFile(file); }
            catch (exception &e) { cout << e.what() << "\n"; }
            file.close();
        }
    } while (choice != 5);
    return 0;
}
