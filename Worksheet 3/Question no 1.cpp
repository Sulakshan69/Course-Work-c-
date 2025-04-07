1.	Create a Time class to store hours and minutes. Implement:
  
1.	Overload the + operator to add two Time objects
2.	Overload the > operator to compare two Time objects
3.	Handle invalid time (>24 hours or >60 minutes) by throwing a custom exception


#include <iostream>
using namespace std;

class InvalidTimeException {};

class Time {
public:
    int hours, minutes;

    Time(int h = 0, int m = 0) {
        if (h < 0 || m < 0 || h >= 24 || m >= 60) throw InvalidTimeException();
        hours = h;
        minutes = m;
    }

    Time operator+(const Time &t) {
        int totalMinutes = (hours + t.hours) * 60 + minutes + t.minutes;
        return Time(totalMinutes / 60 % 24, totalMinutes % 60);
    }

    bool operator>(const Time &t) {
        return (hours * 60 + minutes) > (t.hours * 60 + t.minutes);
    }

    void display() {
        cout << hours << "h " << minutes << "m" << endl;
    }
};

int main() {
    try {
        int h1, m1, h2, m2;

        cout << "Enter first time:\n";
        cout << "Hours: "; cin >> h1;
        cout << "Minutes: "; cin >> m1;

        cout << "Enter second time:\n";
        cout << "Hours: "; cin >> h2;
        cout << "Minutes: "; cin >> m2;

        Time t1(h1, m1), t2(h2, m2);
        Time t3 = t1 + t2;

        cout << "Sum: ";
        t3.display();
        cout << "First time is " << (t1 > t2 ? "greater" : "not greater") << " than second time" << endl;
    } catch (...) {
        cout << "Invalid time entered!" << endl;
    }

    return 0;
}

