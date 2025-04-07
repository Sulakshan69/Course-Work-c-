1.	Write a program with a class Circle having:

1.	Private member: radius (float)
2.	A constructor to initialize radius
3.	A friend function compareTwoCircles that takes two Circle objects and prints which circle has the larger area


#include <iostream>
#include <cmath>
using namespace std;

class Circle {
private:
    float radius;

public:
    Circle(float r) : radius(r) {}

    float getArea() const {
        return M_PI * radius * radius;
    }
};

void compareCircles(const Circle &c1, const Circle &c2) {
    float area1 = c1.getArea();
    float area2 = c2.getArea();

    cout << "Circle 1 Area: " << area1 << endl;
    cout << "Circle 2 Area: " << area2 << endl;

    if (area1 > area2) {
        cout << "Circle 1 has a larger area." << endl;
    } else if (area2 > area1) {
        cout << "Circle 2 has a larger area." << endl;
    } else {
        cout << "Both circles have the same area." << endl;
    }
}

int main() {
    float r1, r2;
    cout << "Enter radius of first circle: ";
    cin >> r1;
    cout << "Enter radius of second circle: ";
    cin >> r2;

    Circle circle1(r1), circle2(r2);
    compareCircles(circle1, circle2);

    return 0;
}
