2.	Stack Problem: Implement a stack using arrays (not STL) that:
    
1.	Has basic push and pop operations
2.	Has a function to find middle element
3.	Has a function to reverse only bottom half of stack
4.	Maintain stack size of 10


#include <iostream>
using namespace std;

class Stack {
private:
    int arr[10];
    int top;

public:
    Stack() {
        top = -1;
    }

    void push(int value) {
        if (top == 9) {
            cout << "Stack is full!" << endl;
            return;
        }
        arr[++top] = value;
    }

    void pop() {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Popped: " << arr[top--] << endl;
    }

    void findMiddle() {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return;
        }
        int middleIndex = top / 2;
        cout << "Middle Element: " << arr[middleIndex] << endl;
    }

    void reverseBottomHalf() {
        if (top <= 0) return;
        int mid = (top + 1) / 2;
        for (int i = 0; i < mid / 2; ++i) {
            swap(arr[i], arr[mid - 1 - i]);
        }
        cout << "Bottom half reversed." << endl;
    }

    void display() {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Stack elements (top to bottom): ";
        for (int i = top; i >= 0; --i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack s;
    int choice, value;

    while (true) {
        cout << "\n1. Push\n2. Pop\n3. Find Middle\n4. Reverse Bottom Half\n5. Display\n6. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> value;
                s.push(value);
                break;
            case 2:
                s.pop();
                break;
            case 3:
                s.findMiddle();
                break;
            case 4:
                s.reverseBottomHalf();
                break;
            case 5:
                s.display();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}

