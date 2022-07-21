#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
using namespace std;

// Enums to map user given commands and its respective functions.
enum CommandArgs {
    Create_parking_lot,
    Park,
    Slot_numbers_for_driver_of_age,
    Slot_number_for_car_with_number,
    Vehicle_registration_number_for_driver_of_age,
    Leave,
};
map<string, CommandArgs> commandMapper {
    { "Create_parking_lot", Create_parking_lot },
    { "Slot_number_for_car_with_number", Slot_number_for_car_with_number },
    { "Slot_numbers_for_driver_of_age", Slot_numbers_for_driver_of_age },
    { "Vehicle_registration_number_for_driver_of_age", Vehicle_registration_number_for_driver_of_age },
    { "Park", Park },
    { "Leave", Leave },
};

// Class Vechicle
class Vehicle {
protected:
	string registrationNumber;
        int driverAge;
        int ticketCost;
public:
	Vehicle() {}

	int getDriverAge() {
            return this->driverAge;
	}
};

class Car: public Vehicle {
    public:
        Car() {
            ticketCost = 150;
        }

	// Initialize a Car with given params
	Car(string registrationNumber, int driverAge) {
		this->registrationNumber = registrationNumber;
                this->driverAge = driverAge;
	}

	string getVehicleRegistrationNumber() {
		return this->registrationNumber;
	}

        int getParkingCost() {
            return ticketCost;
        }
};

class ParkingLot {
private:
	int totalSlots, freeSlots;
	priority_queue<int, vector<int>, greater<int> > slots; // Min Heap to allot nearest parking slot
	map<int, pair<string, int> > carAtSlot; // Map slot number with vehicle registration number and driver's age
        map<string, pair<int, int> > vehicleObjectMapper; // Map vehicle registration number with slot number and driver's age
	set<string> allParkedCars; // Map registration number with slot number

public:
        // Constructor initializes ParkingLot variables
	ParkingLot(int totalSlots) {
		this->totalSlots = totalSlots;
		this->freeSlots = totalSlots;

		for (int t=0;t<totalSlots;++t) {
                    slots.push(t+1); // Push slot into the min-heap
		}
                cout << "Created parking of " << totalSlots << " slots" << endl;
	}

        int getTotalSlots() {
            return this->totalSlots;
        }

	// Allot nearest Parking Slot
        // @returns integer (alloted slot number), -1 if no slots are available
	int parkVehicle(Car *vehicle) {
		if (slots.size() == 0) {
			cout << "Parking Lot Full." << endl;
			return -1;
		}

		string vehicleRegistrationNumber = vehicle->getVehicleRegistrationNumber();
                int driverAge = vehicle->getDriverAge();
		int allotedSlot = slots.top();

                const bool carExists = allParkedCars.find(vehicleRegistrationNumber) != allParkedCars.end();
		if (carExists) {
			cout << "Vehicle with Registration Number " << vehicleRegistrationNumber << " already parked." << endl;
			return -1;
		}

                cout << "Car with vehicle registration number " << vehicleRegistrationNumber << " has been parked at slot number " << allotedSlot << endl;
		slots.pop();
		freeSlots -= 1;

                carAtSlot[allotedSlot] = make_pair(vehicleRegistrationNumber, driverAge);
                vehicleObjectMapper[vehicleRegistrationNumber] = make_pair(allotedSlot, driverAge);
		allParkedCars.insert(vehicleRegistrationNumber);

		return allotedSlot;
	}

        // Find Vehicle at given slot number
        // @returns integer (the slot number), 0 if no vehicle exists in the lot
        int findVehicleSlotNumber(string vehicleRegistrationNumber) {
            return vehicleObjectMapper[vehicleRegistrationNumber].first;
        }

        // Find all slots by driver's age
        // @returns vector of type int
        vector<int> findSlotsByAge(int driverAge) {
            vector<int> allSlots;

            for (auto it=carAtSlot.begin();it!=carAtSlot.end();++it) {
                if (it->second.second == driverAge) {
                    allSlots.push_back(it->first);
                }
            }
            return allSlots;
        }

        // Find all vehicles by driver's age
        // @returns vector of type string
        vector<string> findVechiclesByDriverAge(int driverAge) {
            vector<string> allVehicles;

            for (auto it=vehicleObjectMapper.begin();it!=vehicleObjectMapper.end();++it) {
                if (it->second.second == driverAge) {
                    allVehicles.push_back(it->first);
                }
            }
            return allVehicles;
        }


	// Free a slot given, vehicle registration number
        // @returns integer (the slot number), -1 if lot is full 
	int freeSlot(int slot) {
            string vehicleRegistrationNumber = carAtSlot[slot].first;
            if (vehicleRegistrationNumber == "") {
                if (slot <= totalSlots) {
                    cout << "Slot already vacant" << endl;
                } else {
                    cout << "Slot doesn't exist" << endl;
                }
                return -1;
            }
            auto vehicle = vehicleObjectMapper[vehicleRegistrationNumber];
            cout << "Slot number " << slot << " vacated, the car with vehicle registration number \"" << vehicleRegistrationNumber << "\" left the space, the driver of the car was of age " << vehicle.second << endl;

            // Clear slot from maps, push slot into heap
            allParkedCars.erase(vehicleRegistrationNumber);
            vehicleObjectMapper.erase(vehicleObjectMapper.find(vehicleRegistrationNumber));
            carAtSlot.erase(carAtSlot.find(slot));
            slots.push(slot);
            freeSlots++;
            return slot;
	}

	// Show all free parking slots
	void showAvailableSlots() {
            auto slotsHeap = slots;
            while (!slotsHeap.empty()) {
                    cout << slotsHeap.top() << " ";
                    slotsHeap.pop();
            }
            return;
	}
};

// CommandArgs Resolver to resolve string to an enum variable for switch use-case
CommandArgs resolve(string command) {
    return commandMapper[command];
}

int main() {
        ifstream file("input.txt"); // Read from input.txt in current directory
        string line, word;
        ParkingLot *p;

        while (getline(file, line)) {
            istringstream iss(line, istringstream::in);

            // Read file line by line
            vector<string> command;
            while (iss >> word) {
                command.push_back(word);
            }

            // User-Command mapped cases
            switch (resolve(command[0])) {
                // Cases for user-commands

                case Create_parking_lot: {
                    int totalSlots = stoi(command[1]);
                    p = new ParkingLot(totalSlots);
                    break;
                }

                case Park: {
                    string registrationNumber = command[1];
                    int driverAge = stoi(command[3]);
                    Car *c = new Car(registrationNumber, driverAge);
                    p->parkVehicle(c);
                    break;
                }

                case Slot_numbers_for_driver_of_age: {
                    int driverAge = stoi(command[1]);
                    vector<int> slots = p->findSlotsByAge(driverAge);

                    for (int t=0;t<slots.size();++t) {
                        cout << slots[t];
                        if (t != slots.size() - 1) cout << ",";
                    }
                    cout << endl;
                    break;
                }

                case Slot_number_for_car_with_number: {
                    string registrationNumber = command[1];
                    int slotNumber = p->findVehicleSlotNumber(registrationNumber);

                    if (slotNumber == 0) {
                        cout << "Vehicle with given registration number not found" << endl;
                        break;
                    }
                    cout << slotNumber << endl;
                    break;
                }

                case Vehicle_registration_number_for_driver_of_age: {
                    int driverAge = stoi(command[1]);
                    vector<string> vehicles = p->findVechiclesByDriverAge(driverAge);

                    if (vehicles.size() == 0) {
                        cout << "Vehicles with given driver age not found" << endl;
                        break;
                    } else {
                        for (int t=0;t<vehicles.size();++t) {
                            cout << vehicles[t];
                            if (t != vehicles.size() - 1) cout << ", ";
                        }
                        cout << endl;
                        break;
                    }
                }

                case Leave: {
                    int slotLeaving = stoi(command[1]);
                    p->freeSlot(slotLeaving);
                    break;
                }
            }
        }
        return 1;
}