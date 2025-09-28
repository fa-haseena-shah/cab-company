# TOURMATE CAB MANAGEMENT PROGRAM

It is a C++ menu-driven program developed to manage the main processes of TourMate Cab Service.
It allows the administrator to login, manage vehicles & sales, view company details, exit and logout.

## FEATURES

1. User Authentication
  - Secure login with username and password (3 attempts max).
  - Exit and logout.

2. Vehicle Management
  - View all available vehicles.
  - Add new vehicles (auto-generated ID).
  - Update existing vehicle details.
  - Delete vehicles.
  - Input validation for price, seating capacity and status.

3. Sales (Trip) Management
  - Log new trips (calculate fare automatically).
  - Update existing sales/trips.
  - Delete sales/trips.
  - View all trips in structured tables.
  - Generate reports (total sales, highest fare, average fare, min/max distance).

4. Company Details
  - Displays contact info, fleet size, and services offered.


## ERROR HANDLING:
  - Input validation for numeric fields.
  - Proper handling of invalid menu options.
  - Prevents duplicate IDs with auto-generation


## HOW TO RUN:
1. Open Microsoft Visual Studio.
2. Create a new C++ Console Application project.
3. Copy the code from TOURMATE-PROGRAMMING.cpp into the main source file of the project.
4. Select "Local Windows Debugger" from the dropdown at the top.
5. Run the program by clicking the green play button (OR Ctrl + F5).
6. Login details: Username: TourMate | Password: TM123


## DEPENDENCIES:
- Microsoft Visual Studio 
- Standard libraries only: iostream, iomanip, string, cfloat


## KNOWN BUGS / LIMITATIONS:
- Data is stored only in memory. Once the program exits, all vehicle updations and trip data is lost.
- Entering invalid data types (e.g., letters instead of numbers) may cause infinite loops/unusual program behavior.
