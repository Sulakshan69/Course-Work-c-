1. Create a program that takes a positive integer as input and determines whether it's a "bouncy number". A bouncy number is one where the digits neither consistently increase nor consistently decrease when read from left to right. For example:
•	123 is NOT bouncy (digits consistently increase)
•	321 is NOT bouncy (digits consistently decrease)
•	120 is bouncy (neither consistently increasing nor decreasing)


#include <iostream>
using namespace std;

class BouncyNumber {
private:
    int number;

public:
    BouncyNumber(int num) : number(num) {}

    bool isBouncy() {
        bool increasing = false, decreasing = false;
        int lastDigit = number % 10;
        int numCopy = number / 10;

        while (numCopy > 0) {
            int currentDigit = numCopy % 10;
            if (currentDigit < lastDigit) increasing = true;
            if (currentDigit > lastDigit) decreasing = true;

            if (increasing && decreasing) return true;

            lastDigit = currentDigit;
            numCopy /= 10;
        }
        return false;
    }
};

int main() {
    int num;
    cout << "Enter a positive integer: ";
    cin >> num;

    if (num < 0) {
        cout << "Please enter a positive integer!\n";
        return 1;
    }

    BouncyNumber bouncy(num);
    if (bouncy.isBouncy()) {
        cout << num << " is a Bouncy Number." << endl;
    } else {
        cout << num << " is NOT a Bouncy Number." << endl;
    }

    return 0;
}
