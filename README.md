### Parking Lot
#### Implemented in C++

Functionalities:

1. Create Parking Lot.
2. Allot nearest parking slot (considering registration number and driver's age).
3. Get Slot numbers, given driver's age.
4. Slot Number for car with given registration number.
5. Vehicle Registration for given slot number.
6. Leave Parking Lot.

Commands:

1. **Create_Parking_lot** [Creates a Parking Lot]
2. **Park <vehicle_registration_no> driver_age <age_of_driver>** [Allots the nearest slot to the vehicle]
3. **Slot_numbers_for_driver_of_age <age_of_driver>** [Gets all slot numbers with given driver's age]
4. **Vehicle_registration_number_for_driver_of_age <age_of_driver>** [Get all vehicles with given driver's age]
5. **Slot_number_for_car_with_number <vehicle_registration_no>** [Get slot number for given vehicle registration number]
6. **Leave <slot_number>** [Remove vehicle from the slot and makes it available]

## Test Cases:

### Input 1:
```
Create_parking_lot 1
Park KA-01-HH-1234 driver_age 21
Park PB-01-HH-1234 driver_age 21
Slot_numbers_for_driver_of_age 21
Park PB-01-TG-2341 driver_age 40
Slot_number_for_car_with_number PB-01-HH-1234
Leave 1
Park HR-29-TG-3098 driver_age 39
Vehicle_registration_number_for_driver_of_age 21
```
### Output 1:
```
Created parking of 1 slots
Car with vehicle registration number KA-01-HH-1234 has been parked at slot number 1
Parking Lot Full.
1
Parking Lot Full.
Vehicle with given registration number not found
Slot number 1 vacated, the car with vehicle registration number "KA-01-HH-1234" left the space, the driver of the car was of age 21
Car with vehicle registration number HR-29-TG-3098 has been parked at slot number 1
Vehicles with given driver age not found
```
### Input 2
```
Create_parking_lot 2
Park KA-01-HH-1234 driver_age 21
Park PB-01-HH-1234 driver_age 21
Slot_numbers_for_driver_of_age 21
Park PB-01-TG-2341 driver_age 40
Slot_number_for_car_with_number PB-01-HH-1234
Leave 5
Park HR-29-TG-3098 driver_age 39
Leave 1
Vehicle_registration_number_for_driver_of_age 21
```
### Output 2
```
Created parking of 2 slots
Car with vehicle registration number KA-01-HH-1234 has been parked at slot number 1
Car with vehicle registration number PB-01-HH-1234 has been parked at slot number 2
1,2
Parking Lot Full.
2
Slot doesn't exist
Parking Lot Full.
Slot number 1 vacated, the car with vehicle registration number "KA-01-HH-1234" left the space, the driver of the car was of age 21
PB-01-HH-1234
```
[**Repl.it**](https://replit.com/@ManoSriram1/ParkingLot#main.cpp)