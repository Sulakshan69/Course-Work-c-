2.	 Write a C++ program to implement a number guessing game with different difficulty levels.
Easy difficulty ranges from 1-8, medium from 1-30, hard from 1-50.Then,generate a random number to check if the guess is correct based on the user's selection. 




#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    int maxNum, num, guess;
    char difficulty;

    cout << "Choose difficulty (E - Easy, M - Medium, H - Hard): ";
    cin >> difficulty;

    if (difficulty == 'E' || difficulty == 'e') {
        maxNum = 8;
    } else if (difficulty == 'M' || difficulty == 'm') {
        maxNum = 30;
    } else if (difficulty == 'H' || difficulty == 'h') {
        maxNum = 50;
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    num = rand() % maxNum + 1;

    do {
        cout << "Guess a number between 1 and " << maxNum << ": ";
        cin >> guess;

        if (guess > num) {
            cout << "Please try again." << endl;
        } else if (guess < num) {
            cout << "Please try again." << endl;
        } else {
            cout << "Congratulations You guessed the correct number." << endl;
        }
    } while (guess != num);

    return 0;
}
