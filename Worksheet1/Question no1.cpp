#include <iostream>
using namespace std;

int main() {
    double temp;
    char choice;

    cout << "Enter temperature value: ";
    if (!(cin >> temp)) {
        cout << "Invalid input! Please enter a numeric value." << endl;
        return 1;
    }

    cout << "Convert to (C)elsius or (F)ahrenheit? Enter C or F: ";
    cin >> choice;

    if (choice == 'C' || choice == 'c') {
        double celsius = (temp - 32) * 5 / 9;
        cout << "Temperature in Celsius: " << celsius << " C" << endl;
    } else if (choice == 'F' || choice == 'f') {
        double fahrenheit = (temp * 9 / 5) + 32;
        cout << "Temperature in Fahrenheit: " << fahrenheit << " F" << endl;
    }
    return 0;
}

