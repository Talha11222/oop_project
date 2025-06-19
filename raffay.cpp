         case 5: {
                int b, p;
                cout << "Bus Index (0-" << busCount-1 << "): "; cin >> b;
                cout << "Passenger Index (0-" << passengerCount-1 << "): "; cin >> p;
                if (b < busCount && p < passengerCount)
                    buses[b].addPassenger(&passengers[p]);
                else
                    cout << "Invalid indices.\n";
                break;
            }

            case 6:
                for (int i = 0; i < busCount; i++) {
                    cout << "Bus #" << i << ":\n";
                    buses[i].display();
                }
                break;

            case 7:
                for (int i = 0; i < driverCount; i++) {
                    cout << "Driver #" << i << ": ";
                    drivers[i].display();
                }
                break;

            case 8:
                for (int i = 0; i < passengerCount; i++) {
                    cout << "Passenger #" << i << ": ";
                    passengers[i].display();
                }
                break;

            case 9:
                if (routeCount < MAX) {
                    routes[routeCount++].input();
                } else cout << "Route limit reached.\n";
                break;

            case 10:
                for (int i = 0; i < routeCount; i++) {
                    cout << "Route #" << i << ":\n";
                    routes[i].display();
                }
                break;

            case 11:
                Bus::showTotalBuses();
                break;

            case 12: {
                int i;
                cout << "Enter Bus Index (0-" << busCount-1 << "): "; cin >> i;
                if (i < busCount)
                    viewBusModel(buses[i]);
                else
                    cout << "Invalid index.\n";
                break;
            }

            case 0: {
                ofstream foutD("drivers.txt");
                for (int i = 0; i < driverCount; i++)
                    drivers[i].saveToFile(foutD);
                foutD.close();

                ofstream foutP("passengers.txt");
                for (int i = 0; i < passengerCount; i++)
                    passengers[i].saveToFile(foutP);
                foutP.close();

                ofstream foutB("buses.txt");
                for (int i = 0; i < busCount; i++)
                    buses[i].saveToFile(foutB);
                foutB.close();

                cout << "Data saved. Exiting...\n";
                break;
            }

            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 0);

    return 0;
}
