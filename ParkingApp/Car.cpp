/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Car.cpp
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

#define _CRT_SECURE_NO_WARNINGS

#include "Car.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace sdds {
	Car::Car() : Vehicle() {
		carWash = false;
	}

	Car::Car(const char* plate, const char* model) : Vehicle(plate, model) {

	}

	std::istream& Car::read(std::istream& is) {
		if (isCsv()) {
			//first call the vehicle read and then read the bool flag for the car wash
			Vehicle::read(is);

			//reading the car wash flag
			is >> carWash;
			is.ignore(1000, '\n');

		}
		//if it's not in csv
		else {
			//first call the vehicle read and then ask the user it they want the car washed while parking
			cout << endl << "Car information entry" << endl;
			Vehicle::read();
			cout << "Carwash while parked? (Y)es/(N)o: ";
			bool flag = YesOrNo();
			if (flag) { carWash = true; }
			else { carWash = false; }

		}

		return is;
	}

	std::ostream& Car::write(std::ostream& os) const {
		if (Vehicle::isEmpty()) {
			os << "Invalid Car Object" << endl;
		}

		else {
			if (isCsv()) {
				os << "C,";
				Vehicle::write(os);
				os << carWash << endl;
			}
			else {
				os << "Vehicle type: Car" << endl;
				Vehicle::write(os);
				//os << endl;
				carWash ? os << "With Carwash" : os << "Without Carwash";
				os << endl;
			}
		}

		return os;
	}
}