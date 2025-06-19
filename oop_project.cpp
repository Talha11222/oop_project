
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
               cout << "No driver assigned.\n";
        }
        cout << "Passengers (" << passengerCount << "):\n";
        for (int i = 0; i < passengerCount; i++) {
            if (passengers[i])
                passengers[i]->display();
        }
    }

    void saveToFile(ofstream& fout) const {
        fout << busID << "," << model << "," << passengerCount << endl;
        for (int i = 0; i < passengerCount; i++) {
            if (passengers[i]) {
                fout << "\t";
                passengers[i]->saveToFile(fout);
            }
        }
    }

    static void showTotalBuses() {
        cout << "Total Buses in System: " << totalBuses << endl;
    }

    friend void viewBusModel(const Bus& b);
};

int Bus::totalBuses = 0;

void viewBusModel(const Bus& b) {
    cout << "[Friend] Accessing Bus Model: " << b.model << endl;
}

// ======= ROUTE CLASS =======
class Route {
private:
    int routeID;
    Bus bus;
public:
    void input() {
        cout << "Enter Route ID: "; cin >> routeID;
        cout << "Enter Bus Info for Route:\n";
        bus.input();
    }
    void display() const {
        cout << "Route ID: " << routeID << endl;
        bus.display();
    }
};

int main() {
    const int MAX = 5;
    Bus buses[MAX];
    Driver drivers[MAX];
    Passenger passengers[MAX];
    Route routes[MAX];
    int busCount = 0, driverCount = 0, passengerCount = 0, routeCount = 0;

    int choice;
    do {
        cout << "\n==== SMART BUS MANAGEMENT SYSTEM ====\n";
        cout << "1. Add Bus\n2. Add Driver\n3. Add Passenger\n";
        cout << "4. Assign Driver to Bus\n5. Add Passenger to Bus\n";
        cout << "6. Show Buses\n7. Show Drivers\n8. Show Passengers\n";
        cout << "9. Add Route\n10. Show Routes\n";
        cout << "11. Show Total Buses\n12. View Bus Model (Friend)\n";
        cout << "0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (busCount < MAX) {
                    buses[busCount++].input();
                } else cout << "Bus limit reached.\n";
                break;

            case 2:
                if (driverCount < MAX) {
                    drivers[driverCount++].input();
                } else cout << "Driver limit reached.\n";
                break;

            case 3:
                if (passengerCount < MAX) {
                    passengers[passengerCount++].input();
                } else cout << "Passenger limit reached.\n";
                break;

            case 4: {
                int b, d;    
 cout << "Bus Index (0-" << busCount-1 << "): "; cin >> b;
                cout << "Driver Index (0-" << driverCount-1 << "): "; cin >> d;
                if (b < busCount && d < driverCount)
                    buses[b].assignDriver(&drivers[d]);
                else
                    cout << "Invalid indices.\n";
                break;
            }

            case 5: {
                int b, p;
