/* Citation and Sources...
Final Project Milestone 6
Module: ReadWritable
Filename: ReadWritable.h
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

#ifndef _SDDS_ReadWritable_H
#define _SDDS_ReadWritable_H
#include<iostream>

namespace sdds {
	class ReadWritable {
		bool Csv; //comma separated flag

	public:
		//constructor
		ReadWritable();
		//empty virtual destructor
		virtual ~ReadWritable() = default;

		bool isCsv() const; //return the comma separated flag value
		void setCsv(bool value); //setting the comma separated flag value

		//pure void function to be used by derived classes
		virtual std::ostream& write(std::ostream& os = std::cout) const = 0;
		virtual std::istream& read(std::istream& is = std::cin) = 0;
	};
	//Helper functions
	//overloading the << operator
	std::ostream& operator<<(std::ostream& os, ReadWritable&);
	//overloading the >> operator
	std::istream& operator >> (std::istream& is, ReadWritable&);
}


#endif