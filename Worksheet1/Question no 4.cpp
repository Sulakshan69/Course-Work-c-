4.Write a program that reads a number from the user and based on the user input, it says what day of the week it is, Sundays being 1 and Saturdays being 7. You system should give appropriate response for invalid input entries


#include <iostream>
using namespace std;

int main() {
    int day_num;
    cout << "Enter a number (1-7) to find the day of the week: ";

    if (cin >> day_num) {
        const char* days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

        if (day_num >= 1 && day_num <= 7) {
            cout << "It's " << days[day_num - 1] << "!" << endl;
        } else {
            cout << "Invalid input! Please enter a number between 1 and 7." << endl;
        }
 } else {
        cout << "Invalid input! Please enter a valid number between 1 and 7." << endl;
    }

    return 0;
}
