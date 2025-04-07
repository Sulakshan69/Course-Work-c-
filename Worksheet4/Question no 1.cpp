1.	STL Container Practice: Write a program using STL containers that:

1.	Uses vector<string> to store names
2.	Uses map<string, int> to store age against each name
3.	Implements functions to: 
1.	Add new name-age pair
2.	Find all people above certain age
3.	Sort and display names alphabetically

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class People {
    vector<string> names;
    map<string, int> ages;

public:
    void add(const string& name, int age) {
        names.push_back(name);
        ages[name] = age;
    }

    void showAboveAge(int ageLimit) {
        cout << endl << "People older than " << ageLimit << ":" << endl;
        bool found = false;
        for (string name : names) {
            if (ages[name] > ageLimit) {
                cout << name << " (" << ages[name] << ")" << endl;
                found = true;
            }
        }
        if (!found) cout << "No one found." << endl;
    }

    void showSorted() {
        sort(names.begin(), names.end());
        cout << endl << "Sorted Names:" << endl;
        for (string name : names) {
            cout << name << " (" << ages[name] << ")" << endl;
        }
    }
};

int main() {
    People p;
    int count;
    cout << "How many people do you want to add? ";
    cin >> count;
    cin.ignore();

    for (int i = 1; i <= count; ++i) {
        string name;
        int age;
        cout << endl << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cin.ignore();
        p.add(name, age);
    }

    int ageLimit;
    cout << endl << "Enter age limit: ";
    cin >> ageLimit;

    p.showAboveAge(ageLimit);
    p.showSorted();

    return 0;
}
