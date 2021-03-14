/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Vehicle.h
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
#ifndef _SDDS_Vehicle_H
#define _SDDS_Vehicle_H
#include "Utils.h"
#include "ReadWritable.h"
#include<iostream>

namespace sdds {
	const int MAX_PLATE = 8;
	class Vehicle : public ReadWritable {
		char* licensePlate; //1 to 8 characters. Obs: should it be dynamic?
		char* makeModel; //cannot be null or empty
		int parkingSpot; //0 is not parked.

	public:
		//constructors
		Vehicle(); //safe empty state
		Vehicle(const char* plate, const char* model); //if invalid values are entered, set to empty. ParkingSpot always set to zero

		//prohibiting copy
		Vehicle(const Vehicle&) = delete;
		Vehicle& operator = (const Vehicle&) = delete;

		//destructor
		~Vehicle();

	protected: //protected member operators
		//setter and getter empty functions 
		void setEmpty(); //set to empty state
		bool isEmpty() const; //return true if the vehicle is empty
		
		//getter functions
		char* getLicensePlate() const; //returns licensePlate
		char* getMakeModel() const; //returns MakeModel

		//setter function
		void setMakeModel(char* model); //set a new value to the vehicle model

	public: //public member operators
		int getParkingSpot() const; //return the parking spot number
		void setParkingSpot(const int spot); //set the parking spot number


		std::istream& read(std::istream& is = std::cin); //check if the file is csv, if so read it properly. Read up to 60 char or the final comma to makeModel. If not, ask for the user to input information

		std::ostream& write(std::ostream& os = std::cout) const; //print in comma style or menu style


		bool operator == ( const char *) const; //compare license plates. Tip: use strcmpi from string.h
		bool operator == (const Vehicle& v) const; //compare license plates, not case sensitive
	};


}


#endif