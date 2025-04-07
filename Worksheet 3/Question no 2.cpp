1.	Create a base class Vehicle and two derived classes Car and Bike:

1.	Vehicle has registration number and color
2.	Car adds number of seats
3.	Bike adds engine capacity
4.	Each class should have its own method to write its details to a file
5.	Include proper inheritance and method overriding




#include <iostream>
#include <fstream>
using namespace std;

class Vehicle {
protected:
    string regNumber, color;

public:
    Vehicle(string reg, string col) : regNumber(reg), color(col) {}

    virtual void writeToFile(ofstream &file) {
        file << "Vehicle Reg: " << regNumber << ", Color: " << color << endl;
    }
};

class Car : public Vehicle {
    int seats;

public:
    Car(string reg, string col, int s) : Vehicle(reg, col), seats(s) {}

    void writeToFile(ofstream &file) override {
        file << "Car Reg: " << regNumber << ", Color: " << color << ", Seats: " << seats << endl;
    }
};

class Bike : public Vehicle {
    int engineCapacity;

public:
    Bike(string reg, string col, int cap) : Vehicle(reg, col), engineCapacity(cap) {}

    void writeToFile(ofstream &file) override {
        file << "Bike Reg: " << regNumber << ", Color: " << color << ", Engine Capacity: " << engineCapacity << "cc" << endl;
    }
};

int main() {
    string reg, color;
    int seats, capacity;

    ofstream file("vehicles.txt");

    cout << "Enter Car details:\n";
    cout << "Registration Number: "; cin >> reg;
    cout << "Color: "; cin >> color;
    cout << "Number of Seats: "; cin >> seats;
    Car car(reg, color, seats);
    car.writeToFile(file);

    cout << "\nEnter Bike details:\n";
    cout << "Registration Number: "; cin >> reg;
    cout << "Color: "; cin >> color;
    cout << "Engine Capacity (cc): "; cin >> capacity;
    Bike bike(reg, color, capacity);
    bike.writeToFile(file);

    file.close();
    cout << "\nDetails saved to 'vehicles.txt'." << endl;
    return 0;
}

