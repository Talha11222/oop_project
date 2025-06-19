
#include <iostream>
#include <fstream>
using namespace std;

// ======= FORWARD DECLARATION =======
class Bus;

// ======= BASE ABSTRACT CLASS =======
class Person {
protected:
    int id;
    char name[50];
public:
    virtual void input() = 0;
    virtual void display() const = 0;
    virtual void saveToFile(ofstream& fout) const = 0;
    int getID() const { return id; }
};

// ======= DRIVER CLASS =======
class Driver : public Person {
    char license[20];
public:
    void input() override {
        cout << "Enter Driver ID: "; cin >> id;
        cout << "Enter Name: "; cin.ignore(); cin.getline(name, 50);
        cout << "Enter License No.: "; cin.getline(license, 20);
    }
    void display() const override {
        cout << "Driver ID: " << id << ", Name: " << name << ", License: " << license << endl;
    }
    void saveToFile(ofstream& fout) const override {
        fout << id << "," << name << "," << license << endl;
    }
};

// ======= PASSENGER CLASS =======
class Passenger : public Person {
    char destination[30];
public:
    void input() override {
        cout << "Enter Passenger ID: "; cin >> id;
        cout << "Enter Name: "; cin.ignore(); cin.getline(name, 50);
        cout << "Enter Destination: "; cin.getline(destination, 30);
    }
    void display() const override {
        cout << "Passenger ID: " << id << ", Name: " << name << ", Destination: " << destination << endl;
    }
    void saveToFile(ofstream& fout) const override {
        fout << id << "," << name << "," << destination << endl;
    }
};

// ======= BUS CLASS =======
class Bus {
private:
    int busID;
    char model[30];
    static int totalBuses;
    const int maxCapacity;
    Driver* driver;
    Passenger* passengers[10];
    int passengerCount;

public:
    Bus() : maxCapacity(50), passengerCount(0) {
        driver = nullptr;
        for (int i = 0; i < 10; i++) passengers[i] = nullptr;
        totalBuses++;
    }

    ~Bus() {
        totalBuses--;
    }

    void input() {
        cout << "Enter Bus ID: "; cin >> busID;
        cout << "Enter Model: "; cin.ignore(); cin.getline(model, 30);
    }

    void assignDriver(Driver* d) {
        driver = d;
    }

    void addPassenger(Passenger* p) {
        if (passengerCount < 10) {
            passengers[passengerCount++] = p;
        } else {
            cout << "Passenger limit reached for this bus.\n";
        }
    }

    void display() const {
        cout << "Bus ID: " << busID << ", Model: " << model
             << ", Max Capacity: " << maxCapacity << endl;
        if (driver) {
            cout << "Assigned Driver: ";
            driver->display();
        } else {
            
