	Create a program with these overloaded functions named findMax:

1.	One that finds maximum between two integers
2.	One that finds maximum between two floating-point numbers
3.	One that finds maximum among three integers
4.	One that finds maximum between an integer and a float	


#include <iostream>
using namespace std;

class MaxFinder {
public:
    // Finds max between two integers
    int findMax(int a, int b) {
        return (a > b) ? a : b;
    }

    // Finds max between two floats
    float findMax(float a, float b) {
        return (a > b) ? a : b;
    }

    // Finds max among three integers
    int findMax(int a, int b, int c) {
        return (a > b && a > c) ? a : (b > c ? b : c);
    }

    // Finds max between an integer and a float
    float findMax(int a, float b) {
        return (a > b) ? a : b;
    }
};

int main() {
    MaxFinder maxFinder;
    int choice;

    cout << "Choose an option to find the maximum:" << endl;
    cout << "1. Between two integers" << endl;
    cout << "2. Between two floating-point numbers" << endl;
    cout << "3. Among three integers" << endl;
    cout << "4. Between an integer and a float" << endl;
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    if (choice == 1) {
        int a, b;
        cout << "Enter two integers: ";
        cin >> a >> b;
        cout << "Maximum: " << maxFinder.findMax(a, b) << endl;
    } else if (choice == 2) {
        float a, b;
        cout << "Enter two floating-point numbers: ";
        cin >> a >> b;
        cout << "Maximum: " << maxFinder.findMax(a, b) << endl;
    } else if (choice == 3) {
        int a, b, c;
        cout << "Enter three integers: ";
        cin >> a >> b >> c;
        cout << "Maximum: " << maxFinder.findMax(a, b, c) << endl;
    } else if (choice == 4) {
        int a;
        float b;
        cout << "Enter an integer and a floating-point number: ";
        cin >> a >> b;
        cout << "Maximum: " << maxFinder.findMax(a, b) << endl;
    } else {
        cout << "Invalid choice! Please restart the program and select a valid option." << endl;
    }

    return 0;
}
