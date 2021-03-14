/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Motorcycle.cpp
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
#include "Motorcycle.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace sdds {
	Motorcycle::Motorcycle() : Vehicle() {
		sidecar = false;
	}

	Motorcycle::Motorcycle(const char* plate, const char* model) : Vehicle(plate, model) {
		sidecar = false;
	}

	std::istream& Motorcycle::read(std::istream& is) {
		if (isCsv()) {
			//first call the vehicle read and then read the bool flag for the car wash
			Vehicle::read(is);

			//reading the car wash flag
			is >> sidecar;
			is.ignore(1000, '\n');

		}
		//if it's not in csv
		else {
			//first call the vehicle read and then ask the user it they want the car washed while parking
			cout << endl << "Motorcycle information entry" << endl;
			Vehicle::read();
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			bool flag = YesOrNo();
			if (flag) { sidecar = true; }
			else { sidecar = false; }

		}

		return is;
	}

	std::ostream& Motorcycle::write(std::ostream& os) const{
		if (Vehicle::isEmpty()) {
			os << "Invalid Motorcycle Object" << endl;
		}

		else {
			if (isCsv()) {
				os << "M,";
				Vehicle::write(os);
				os << sidecar << endl;
			}
			else {
				os << "Vehicle type: Motorcycle" << endl;
				Vehicle::write(os);
				if(sidecar) os << "With Sidecar" << endl;
				//os << endl;
			}
		}

		return os;
	
	}
}