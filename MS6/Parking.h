/* Citation and Sources...
Final Project Milestone 6
Module: Parking
Filename: Parking.h
Version 1.0
Author Luan Lima Campos
Revision History
-----------------------------------------------------------
Date Reason
2020/?/? Preliminary release
2020/?/? Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
Student: Luan Lima Campos
Student ID: 119386191
Username: llima-campos
*/

#ifndef _SDDS_PARKING_H
#define _SDDS_PARKING_H

#include "Menu.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Utils.h"

namespace sdds {

	const int MAX_PARKING = 100; //max number of parking spots

	class Parking {
		char* file_name;
		Menu parking_menu;
		Menu vehicle_menu;
		int parking_spots; //always less than MAX_PARKING
		int spots_parked;// tracks the number of spots parked 
		Vehicle* spot[MAX_PARKING]; //acts like a parking spot

		
			
		//private member functions
		bool isEmpty()const;
		void parkingStatus(std::ostream& os = std::cout) const; //print avaiable spots in the parking
		void parkVehicle(std::ostream& os = std::cout, std::istream& is = std::cin); //parks the vehicle
		void returnVehicle(std::ostream& os = std::cout); //returns a vehicle and free the index
		void listParkedVehicles(std::ostream& os = std::cout) const; //list all parked vehicles
		bool closePark(std::ostream& os = std::cout); //delete all the data and close the application
		bool exitPark(std::ostream& os = std::cout, std::istream& is = std::cin); //finish the application without deleting the data
		bool loadDataFile(std::ostream& os = std::cout); //load data from the file
		bool saveDataFile(std::ostream& os = std::cout); //save data in the file

	public:
		//constructors
		Parking(); //empty safe state
		Parking(const char* file, int nOfSpots); //initializes a parking
		~Parking();

		//prohibiting copying and assignment copy operator
		Parking(const Parking&) = delete;
		Parking& operator = (const Parking&) = delete;

		//member functions
		int run(std::ostream& os = std::cout); //run the menu and get the user option
	};

	
}

#endif