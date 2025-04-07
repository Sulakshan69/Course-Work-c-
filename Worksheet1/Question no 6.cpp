1. Write a program that manages a cinema ticket booking system. The program should display a 5x5 seating arrangement where: 
1.	Available seats are marked with 'O'
2.	Booked seats are marked with 'X'
    
Program should: 
1.	Display the current seating arrangement
2.	Ask user for row and column number (1-5) for booking
3.	Mark that seat as booked ('X')
4.	Show updated seating after each booking
5.	Display error if user selects already booked seat
6.	Display error if user enters invalid row/column numbers


#include <iostream>
using namespace std;

class CinemaBookingSystem {
private:
    char seats[5][5];

public:
    CinemaBookingSystem() {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                seats[i][j] = 'O';
            }
        }
    }

    void display() {
        cout << "\nCurrent Seating Arrangement:\n";
        cout << "  1 2 3 4 5\n";
        for (int i = 0; i < 5; ++i) {
            cout << i + 1 << " ";
            for (int j = 0; j < 5; ++j) {
                cout << seats[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bookSeat() {
        int row, col;

        cout << "\nEnter row number (1-5): ";
        cin >> row;
        cout << "Enter column number (1-5): ";
        cin >> col;

        if (row < 1 || row > 5 || col < 1 || col > 5) {
            cout << "Invalid seat number! Please enter values between 1 and 5.\n";
            return;
        }

        row -= 1;
        col -= 1;

        if (seats[row][col] == 'X') {
            cout << "\nError: This seat is already booked.\n";
        } else {
            seats[row][col] = 'X';
            cout << "\nSeat booked successfully!\n";
        }
    }
};

int main() {
    CinemaBookingSystem system;
    char choice;

    do {
        system.display();

        cout << "\n-------- Menu --------\n";
        cout << "X - Book a Seat\n";
        cout << "Y - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 'X' || choice == 'x') {
            system.bookSeat();
        } else if (choice == 'Y' || choice == 'y') {
            cout << "Exiting the system. Goodbye!\n";
        } else {
            cout << "Invalid choice! Please enter 'X' to book or 'Y' to exit.\n";
        }

    } while (choice != 'Y' && choice != 'y');

    return 0;
}
