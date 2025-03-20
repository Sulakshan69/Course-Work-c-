1.Write a program that takes a temperature value from the user. It should then allow the user to choose between Celsius (C) and Fahrenheit (F) for conversion. After the user selection, it should then convert the entered temperature to the chosen scale and display the result.
Use appropriate data types for temperature and handle error like non-numeric input. 
Use the following formula for conversion:
F = (C x 9/5) + 32
C = (F - 32) x 5/9


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
