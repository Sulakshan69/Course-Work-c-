#include <iostream>
using namespace std;

int main() {
    int numbers[100];
    int size;


    cout << " How many numbers do you want to enter (max 100)? ";
    cin >> size;


    if (size > 100 || size <= 0) {
        cout << "Please enter a number between 1 and 100" << endl;
        return 1;
    }

    cout << "Enter " << size << " numbers:" << endl;
    for(int i = 0; i < size; i++) {
        cin >> numbers[i];
    }


    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(numbers[j] > numbers[j + 1]) {

                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }


    cout << "Sorted numbers: ";
    for(int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}
