#include <iostream>
#include <string>
#include <iomanip>
#include <cfloat>

using namespace std;

// global variable/array/struct declaration
struct Vehicle {
    int id;
    string type;
    string model;
    float pricePerKm;
    int stngCap;
    string fuel;
    string driver;
    string status;
};

struct Trip {
    int id, vehicleId;
    string pick, drop;
    float distance;
    string cus;
    float fare;
};

int vCount = 10;
int tCount = 0;

const int MAX_V = 150;
const int MAX_TRIPS = 500;
const float max_price = 500;
const int max_seating = 20;

float totalSales = 0;
float highestFare = 0;
float maxDist = 0;
float minDist = FLT_MAX; // FLT_MAX is a very large number, drawn from the <cfloat> library

Vehicle vehicles[MAX_V] = {
    {1, "Compact", "Alto", 90, 4, "Diesel", "Gayan", "AVL"},
    {2, "Sedan", "Axio", 120, 4, "Petrol", "Mohamed", "AVL"},
    {3, "SUV", "Vezel", 150, 5, "Hybrid", "Nimal", "AVL"},
    {4, "Van", "KDH", 200, 12, "Diesel", "Jack", "AVL"},
    {5, "Compact", "WagonR", 100, 4, "Petrol", "Tharindu", "AVL"},
    {6, "Sedan", "Allion", 130, 4, "Petrol", "Yashod", "AVL"},
    {7, "SUV", "CR-V", 160, 5, "Petrol", "Chandana", "AVL"},
    {8, "Van", "Hiace", 210, 14, "Diesel", "John", "AVL"},
    {9, "Compact", "Swift", 95, 4, "Petrol", "Aathil", "HIR"},
    {10, "Sedan", "Premio", 140, 4, "Petrol", "Dulan", "AVL"}
};
Trip trips[MAX_TRIPS] = {};

bool login() {
    const string correctUser = "TourMate";
    const string correctPass = "TM123";
    const int maxLoginAttempts = 3;
    string user, pass;
    int loginAttempt = 1;

    std::cout << "\n--------------------- ADMIN LOGIN ---------------------\n";

    while (loginAttempt <= maxLoginAttempts) { // login attempts are not exceeded
        std::cout << "\nUsername - "; cin >> user;
        std::cout << "Password - "; cin >> pass;

        if (user == correctUser && pass == correctPass) {
            std::cout << "\nLogin successful!\n";
            return true;
        }
        else {
            std::cout << "\nLogin unsuccessful. Attempt "
                << loginAttempt << " of " << maxLoginAttempts << "!\n";
            loginAttempt++;
        }
    }

    std::cout << "Too many attempts, please try again later!\n";
    return false;
}

// function to auto generate vehicle IDs to prevent errors/duplicates
int generateVehicleID() {
    static int last_assigned_id = 10;
    return ++last_assigned_id; // using ++ before the variable increments it and then returns it
}

// VIEW AVAILABLE VEHICLE DETAILS
void displayVehicles() {
    if (vCount == 0) {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "\nNo vehicles to display!\n"; // if all vehicles deleted
        return;
    }

    // print structured tables with neat columns 
    std::cout << std::left << std::setw(5) << "ID" // left & right manipulators for proper column alignment
        << std::setw(10) << "Type"
        << std::setw(10) << "Model"
        << std::setw(10) << "Price"
        << std::setw(6) << "Seats"
        << std::setw(8) << "Fuel"
        << std::setw(12) << "Driver"
        << std::setw(6) << "Status" << std::endl;

    std::cout << std::string(70, '-') << std::endl; // print separator line

    for (int i = 0; i < vCount; i++) {
        std::cout << std::left << std::setw(5) << vehicles[i].id
            << std::setw(10) << vehicles[i].type
            << std::setw(10) << vehicles[i].model
            << std::setw(10) << vehicles[i].pricePerKm
            << std::setw(6) << vehicles[i].stngCap
            << std::setw(8) << vehicles[i].fuel
            << std::setw(12) << vehicles[i].driver
            << std::setw(6) << vehicles[i].status << std::endl;
    }
}

// function to validate vehicle IDs
int validateVehicleID(int vehicleID) {
    for (int i = 0; i < vCount; i++) {
        if (vehicles[i].id == vehicleID)
            return i; // if found, return index
    }
    return -1; // if not found, return -1
}

// ADD / UPDATE / DELETE VEHICLE DETAILS
void updateVehicles() {
    int subInput;

    do {
        std::cout << "\n--------------------- EDIT MENU ---------------------\n";
        std::cout << "1. Update Existing Vehicle\n";
        std::cout << "2. Add New Vehicle\n";
        std::cout << "3. Delete Vehicle\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice - ";
        cin >> subInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // used instead of cin.ignore() to ignore as many 
                                                            //  characters as possible to prevent potential errors

        if (subInput == 1) { // edit vehicle
            int id;

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "NOW UPDATING VEHICLE!\n";
            std::cout << std::string(50, '-') << std::endl;

            std::cout << "Enter ID of vehicle to update - ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            bool found = false;
            for (int i = 0; i < vCount; i++) {
                if (vehicles[i].id == id) {
                    string newType, newModel, newFuel, newDriver, newStatus;
                    float newPrice;
                    int newSeating;

                    cout << "Enter new type - "; getline(cin, newType);
                    cout << "Enter new model - "; getline(cin, newModel);
                    do {
                        std::cout << "Enter price per KM - ";
                        cin >> newPrice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (newPrice <= 0 || newPrice >= max_price) std::cout << "\n** INVALID INPUT: 0 < PRICE < 500 **\n";
                    } while (newPrice <= 0 || newPrice >= max_price);

                    do {
                        std::cout << "Enter seating capacity - ";
                        cin >> newSeating;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (newSeating <= 0 || newSeating >= max_seating) std::cout << "\n** INVALID INPUT: 0 < SEATING CAPACITY < 20 **\n";
                    } while (newSeating <= 0 || newSeating >= max_seating);
                    cout << "Enter new fuel type- "; getline(cin, newFuel);
                    cout << "Enter new driver name - "; getline(cin, newDriver);
                    cout << "Enter new status [AVL/HIR] - "; getline(cin, newStatus);

                    vehicles[i].type = newType;
                    vehicles[i].model = newModel;
                    vehicles[i].pricePerKm = newPrice;
                    vehicles[i].stngCap = newSeating;
                    vehicles[i].fuel = newFuel;
                    vehicles[i].driver = newDriver;
                    vehicles[i].status = newStatus;

                    found = true;
                    std::cout << std::string(50, '-') << std::endl;
                    std::cout << "Vehicle updated successfully!\n";
                    std::cout << std::string(50, '-') << std::endl;
                    break;
                }
            }
            if (!found) {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Invalid Vehicle ID entered!\n";
                std::cout << std::string(50, '-') << std::endl;
            }
        }

        else if (subInput == 2) { // add vehicle
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "NOW ADDING VEHICLE!\n";
            std::cout << std::string(50, '-') << std::endl;

            if (vCount < MAX_V) {

                string type, model, fuel, driver, status;
                float price;
                int id, stngCap;

                id = generateVehicleID();

                std::cout << "Enter vehicle type - "; getline(cin, type);
                std::cout << "Enter vehicle model - "; getline(cin, model);
                do {
                    std::cout << "Enter price per KM - ";
                    cin >> price;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (price <= 0 || price > max_price) std::cout << "\n** INVALID INPUT: 0 < PRICE < 500 **\n";
                } while (price <= 0 || price > max_price);

                do {
                    std::cout << "Enter seating capacity - ";
                    cin >> stngCap;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (stngCap <= 1 || stngCap >= max_seating) std::cout << "\n** INVALID INPUT: 0 < SEATING CAPACITY < 20 **\n";
                } while (stngCap <= 0 || stngCap >= max_seating); 

                std::cout << "Enter fuel type - "; getline(cin, fuel);
                std::cout << "Enter driver name - "; getline(cin, driver);
                std::cout << "Enter status [AVL/HIR] - "; getline(cin, status);

                vehicles[vCount].id = id;
                vehicles[vCount].type = type;
                vehicles[vCount].model = model;
                vehicles[vCount].pricePerKm = price;
                vehicles[vCount].stngCap = stngCap;
                vehicles[vCount].fuel = fuel;
                vehicles[vCount].driver = driver;
                vehicles[vCount].status = status;

                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Vehicle added successfully!\n";
                std::cout << std::string(50, '-') << std::endl;

                vCount++;
            }
            else {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Storage full!\n";
                std::cout << std::string(50, '-') << std::endl;
            }
        }

        else if (subInput == 3) { // delete vehicle
            int id;

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "NOW DELETING VEHICLE!\n";
            std::cout << std::string(50, '-') << std::endl;

            std::cout << "Enter vehicle ID to delete - ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            bool found = false;
            for (int i = 0; i < vCount; i++) {
                if (vehicles[i].id == id) {
                    found = true;
                    if (vehicles[i].status == "HIR") {
                        std::cout << "Cannot delete vehicle! It is on a hire.\n";
                        break;
                    }
                    for (int a = i; a < vCount - 1; a++) {
                        vehicles[a] = vehicles[a + 1];
                    }
                    vCount--;

                    std::cout << std::string(50, '-') << std::endl;
                    std::cout << "Vehicle deleted successfully!\n";
                    std::cout << std::string(50, '-') << std::endl;
                    break;
                }
            }

            if (!found) {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Vehicle ID not found!\n";
                std::cout << std::string(50, '-') << std::endl;
            }
        }

        else if (subInput != 4) { // invalid menu option
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Invalid menu option! Please enter 1-4.\n";
            std::cout << std::string(50, '-') << std::endl;
        }

    } while (subInput != 4); // exit edit menu
}

// function to calculate trip fares
float calculateFare(float distance, float pricePerKm) {
    return distance * pricePerKm;
}

// function to make sales report
void computeReports() {
    totalSales = 0;
    highestFare = 0;
    maxDist = 0;
    minDist = FLT_MAX; // very large initial value

    for (int i = 0; i < tCount; i++) {
        // total sales
        totalSales += trips[i].fare;

        // highest fare
        if (trips[i].fare > highestFare)
            highestFare = trips[i].fare;

        // max distance
        if (trips[i].distance > maxDist)
            maxDist = trips[i].distance;

        // min distance
        if (trips[i].distance < minDist)
            minDist = trips[i].distance;
    }

    // handling for when no trips exist
    if (tCount == 0) {
        minDist = 0;
        maxDist = 0;
    }
}

// Sales: the exchange of money for service. TourMate service is providing trips.
// Therefore, managing sales is assumed to be managing TRIP details.

// MANAGE SALES DETAILS
void logSale() {
    if (tCount >= MAX_TRIPS) { // check if there is space in array
        std::cout << std::string(50, '-') << "\n";
        std::cout << "Cannot insert, storage is full!\n";
        return;
    }

    std::cout << std::string(50, '-') << "\n";
    std::cout << "NOW LOGGING SALE!\n";
    std::cout << std::string(50, '-') << "\n";

    int vehicleID;
    string pick, drop, cus;
    float distance, fare;

    std::cout << "Enter Vehicle ID - ";
    cin >> vehicleID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // validate vehicle ID
    int i = validateVehicleID(vehicleID);
    if (i == -1) {
        std::cout << "Invalid vehicle ID!\n";
        return;
    }

    // check availability
    if (vehicles[i].status == "HIR") {
        std::cout << "\nVehicle is already on a hire!\n";
        return;
    }

    // input trip records
    std::cout << "Enter pick-up point - ";
    getline(cin, pick);

    std::cout << "Enter drop-off point - ";
    getline(cin, drop);

    // check if distance is appropriate
    do {
        std::cout << "Enter distance in Km - ";
        cin >> distance;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (distance <= 0) std::cout << "Distance must be positive!\n";
    } while (distance <= 0);

    std::cout << "Enter customer name - ";
    getline(cin, cus);

    fare = calculateFare(distance, vehicles[i].pricePerKm);

    // auto generate trip ID : this method removes garbage data from old code executions 
    if (tCount == 0) { 
        trips[tCount].id = 1; 
    } 
    else { 
        trips[tCount].id = trips[tCount - 1].id + 1; 
    }

    // add trip to array
    trips[tCount].vehicleId = vehicleID;
    trips[tCount].pick = pick;
    trips[tCount].drop = drop;
    trips[tCount].cus = cus;
    trips[tCount].distance = distance;
    trips[tCount].fare = fare;

    // update vehicle status
    vehicles[i].status = "HIR";

    tCount++;

    std::cout << std::string(87, '-') << "\n";
    std::cout << "\nFare - LKR " << fare << "\n";
    std::cout << "Trip " << trips[tCount - 1].id << " logged successfully!\n";
}

void updateSales() {
    int tripID;
    int newVehicleID;
    string newPick, newDrop, newCus;
    float newDistance;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "NOW UPDATING SALE / TRIP!\n";
    std::cout << std::string(50, '-') << std::endl;

    std::cout << "Enter ID of trip to update - ";
    cin >> tripID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for (int i = 0; i < tCount; i++) {
        if (trips[i].id == tripID) {
            found = true;

            int o = validateVehicleID(trips[i].vehicleId); // store old vehicle index
            vehicles[o].status = "AVL";  // old vehicle is changed to 'available' status

            std::cout << "Enter new vehicle ID - "; cin >> newVehicleID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int v = validateVehicleID(newVehicleID);

            if (v == -1) {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Invalid vehicle ID! Update cancelled!\n";
                return;
            }

            // check if new vehicle is available
            if (vehicles[v].status == "HIR") {
                std::cout << "Selected vehicle is currently on hire! Update cancelled.\n";
                return;
            }

            // input new trip details
            std::cout << "Enter new pick up point - ";
            getline(cin, newPick);

            std::cout << "Enter new drop off point - ";
            getline(cin, newDrop);

            do {
                std::cout << "Enter new distance in KM - ";
                cin >> newDistance;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (newDistance <= 0) std::cout << "Distance must be positive!\n";
            } while (newDistance <= 0);

            std::cout << "Enter new customer name - ";
            getline(cin, newCus);

            // update trip
            trips[i].vehicleId = newVehicleID;
            trips[i].pick = newPick;
            trips[i].drop = newDrop;
            trips[i].distance = newDistance;
            trips[i].cus = newCus;
            trips[i].fare = newDistance * vehicles[v].pricePerKm;

            // update vehicles' status
            vehicles[v].status = "HIR";  // new vehicle is changed to 'hired'
           

            std::cout << "\nRecalculated Fare - LKR " << trips[i].fare;
            std::cout << "\nTrip updated successfully!\n";
            return;
        }
    }

    if (!found) {
        std::cout << "Trip ID invalid!\n";
    }
}

void deleteSales() {
    if (tCount == 0) {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "\nNo trips to delete!\n";
        return;
    }

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "NOW DELETING SALE / TRIP!\n";
    std::cout << std::string(50, '-') << std::endl;

    int id;
    std::cout << "\nEnter Trip ID to delete - ";
    std::cin >> id;

    bool found = false;
    for (int i = 0; i < tCount; i++) {
        if (trips[i].id == id) {
            found = true;

            // change status of vehicle
            for (int v = 0; v < vCount; v++) {
                if (vehicles[v].id == trips[i].vehicleId) {
                    vehicles[v].status = "AVL";
                    break;
                }
            }

            // shift trips left
            for (int j = i; j < tCount - 1; j++) {
                trips[j] = trips[j + 1];
            }

            tCount--;


            std::cout << "\nTrip " << id << " deleted successfully!\n";
            break;
        }
    }

    if (!found) {
        std::cout << "\nTrip ID not found!\n";
    }
}

void showSales() {
    if (tCount == 0) {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "\nNo trips logged!";
        return;
    }

    // structured table
    std::cout << "======================================= ALL TRIPS ======================================\n";
    std::cout << std::left
        << std::setw(5) << "ID"
        << std::setw(10) << "VehicleID"
        << std::setw(15) << "Pick Up"
        << std::setw(15) << "Drop Off"
        << std::setw(10) << "Distance"
        << std::setw(30) << "Customer"
        << std::setw(10) << "Fare (LKR)"
        << std::endl;

    std::cout << std::string(87, '-') << std::endl;

    for (int i = 0; i < tCount; i++) {
        std::cout << std::left
            << std::setw(5) << trips[i].id
            << std::setw(10) << trips[i].vehicleId
            << std::setw(15) << trips[i].pick
            << std::setw(15) << trips[i].drop
            << std::setw(10) << trips[i].distance
            << std::setw(30) << trips[i].cus
            << std::setw(10) << trips[i].fare
            << std::endl;
    }
}

void salesReport() {
    computeReports(); // compute all details from existing trips

    if (tCount < 5) {
        std::cout << "\nReport unavailable! Log at least 5 trips.\n";
        return;
    }

    std::cout << std::string(82, '-') << std::endl;
    std::cout << "Total Sales - LKR " << totalSales << std::endl;
    std::cout << std::string(82, '-') << std::endl;

    std::cout << "Highest Fare Earned - LKR " << highestFare << std::endl;
    std::cout << std::string(82, '-') << std::endl;

    float avgFare = totalSales / tCount;

    std::cout << "Average Trip Fare - LKR " << avgFare << std::endl;
    std::cout << std::string(82, '-') << std::endl;

    std::cout << "Maximum Distance Travelled - " << maxDist << " KM" << std::endl;
    std::cout << std::string(82, '-') << std::endl;

    std::cout << "Minimum Distance Travelled - " << minDist << " KM" << std::endl;
    std::cout << std::string(82, '-') << std::endl;
}

void salesMenu() {
    int salesInput;
    const int exit = 6;

    do {
        std::cout << "\n--------------------- MANAGE SALES ---------------------\n";
        std::cout << "\n(1) Log sale (trip)\n" << "(2) Edit Sales\n" << "(3) Delete Sales\n" << "(4) View Sales\n" << "(5) View Reports\n" << "(6) Back to Main Menu\n" << "\nChoice - ";
        std::cin >> salesInput;

        if (salesInput < 1 || salesInput > 6) {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Invalid menu option! Please enter 1-6 only!\n";
            continue;
        }

        switch (salesInput) {
        case 1:
            logSale();
            break;
        case 2:
            updateSales();
            break;
        case 3:
            deleteSales();
            break;
        case 4:
            showSales();
            break;
        case 5:
            salesReport();
            break;
        case 6:
            break;
        }
    } while (salesInput != exit);
}

// VIEW COMPANY DETAILS
void companyDetails() {
    string contactNumber = "+94 773 846 0247";
    string email = "contact@tourmate.com";
    string website = "tourmate.com";
    string officeHours = "OFFICE OPEN FROM 9AM - 8PM";
    string serviceAvailability = "SERVICES AVAILABLE 24/7";

    // arrays for vehicles/services
    string vehicleRange[] = { "Basic", "Semi-Luxury", "Luxury" };
    string services[] = { "Short Rides", "Advanced Bookings", "Day Trips", "Airport Transfers" };

    std::cout << "\n------------------- TOURMATE DETAILS -------------------\n";
    std::cout << "\n" << contactNumber << " | " << email << " | " << website << "\n";
    std::cout << "* Fleet Size - " << vCount << " | Total Trips Completed - " << tCount << "\n";
    std::cout << "\n" << officeHours << " | " << serviceAvailability << " \n";

    std::cout << "\n------------ Range of Vehicles ------------\n";
    std::cout << "* " << vehicleRange[0] << "\n"
        << "* " << vehicleRange[1] << "\n"
        << "* " << vehicleRange[2] << "\n";

    std::cout << "\n------------ Services Offered ------------\n";
    std::cout << "* " << services[0] << "\n"
        << "* " << services[1] << "\n"
        << "* " << services[2] << "\n"
        << "* " << services[3] << "\n";
}

bool logout() {
    char logOut;
    std::cout << "Do you wish to log out? (Y/N) - "; cin >> logOut;

    if (logOut == 'Y' || logOut == 'y') {
        std::cout << "Logging out...\n";
        std::cout << "\n--END--\n";
        return true; // logout
    }
    else if (logOut == 'N' || logOut == 'n') {
        return false; //  back to main menu
    }
    else {
        std::cout << "Invalid choice!! Staying logged in!\n";
        return false;
    }
}

void menu() {
    int menuInput;
    do {
        std::cout << "\n======================  MAIN MENU ======================\n"
            << "1. View vehicle details\n"
            << "2. Edit vehicle details\n"
            << "3. Manage sales details\n"
            << "4. View company details\n"
            << "5. Exit\n"
            << "Choice - "; cin >> menuInput;

        switch (menuInput) {
        case 1: // VIEW VEHICLES
            std::cout << "\nNOW VIEWING VEHICLE DETAILS...\n";
            displayVehicles();
            break;
        case 2: // EDIT VEHICLES
            updateVehicles();
            break;
        case 3: // SALES DETAILS
            salesMenu();
            break;
        case 4: // COMPANY DETAILS
            companyDetails();
            break;
        case 5: // LOGOUT
            if (logout()) {
                return;
            }
            break;
        default:
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Invalid option entered. Please enter 1-5 only!\n";
        }
    } while (true); // loop until logout returns true
}

int main() {
    std::cout << "----------------- WELCOME TO TOURMATE!! -----------------\n";
    if (login()) {
        menu();
    }
    else {
        std::cout << "Login failed. Exiting program.\n";
    }
    return 0;
}