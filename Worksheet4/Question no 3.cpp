#include <iostream>
using namespace std;

class Queue {
    int arr[100];
    int front, rear, capacity;

public:
    Queue(int size) {
        capacity = size;
        front = 0;
        rear = -1;
    }

    bool isEmpty() {
        return front > rear;
    }

    bool isFull() {
        return rear == capacity - 1;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow!" << endl;
            return;
        }
        rear++;
        arr[rear] = value;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!" << endl;
            return -1;
        }
        int val = arr[front];
        front++;
        return val;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void reverseFirstK(int k) {
        if (k > (rear - front + 1)) {
            cout << "K is greater than queue size." << endl;
            return;
        }

        int temp[100];
        for (int i = 0; i < k; i++) {
            temp[i] = arr[front + i];
        }

        for (int i = 0; i < k; i++) {
            arr[front + i] = temp[k - i - 1];
        }
    }

    void interleave() {
        int size = rear - front + 1;
        if (size % 2 != 0) {
            cout << "Queue must have even number of elements to interleave." << endl;
            return;
        }

        int half = size / 2;
        int firstHalf[50], secondHalf[50];
        for (int i = 0; i < half; i++) {
            firstHalf[i] = arr[front + i];
        }
        for (int i = 0; i < half; i++) {
            secondHalf[i] = arr[front + half + i];
        }

        int index = front;
        for (int i = 0; i < half; i++) {
            arr[index++] = firstHalf[i];
            arr[index++] = secondHalf[i];
        }
    }
};

int main() {
    int n, val, k;
    cout << "Enter number of elements (max 100): ";
    cin >> n;

    Queue q(100);

    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> val;
        q.enqueue(val);
    }

    q.display();

    cout << "Enter value of K to reverse first K elements: ";
    cin >> k;
    q.reverseFirstK(k);
    cout << "Queue after reversing first " << k << " elements:" << endl;
    q.display();

    cout << "Interleaving queue..." << endl;
    q.interleave();
    q.display();

    return 0;
}
