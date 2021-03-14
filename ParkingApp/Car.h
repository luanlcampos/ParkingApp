/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Car.h
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

#ifndef _SDDS_CAR_H
#define _SDDS_CAR_H

#include "Vehicle.h"

namespace  sdds {
	class Car : public Vehicle {
		bool carWash; //flag to set if car will be washed while parking

	public:
		Car(); // safe empty state
		Car(const char* plate, const char* model); //use vehicle constructor

		//prohibitting copy
		Car(const Car&) = delete;
		Car& operator=(const Car&) = delete;


		//overloading read and write functions to adapt the output for cars
		std::istream& read(std::istream& is = std::cin); //check if the file is csv, if so read it properly. Read up to 60 char or the final comma to makeModel. If not, ask for the user to input information

		std::ostream& write(std::ostream& os = std::cout) const; //print in comma style or menu style
	};
}


#endif