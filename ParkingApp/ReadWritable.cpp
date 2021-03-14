/* Citation and Sources...
Final Project Milestone 6
Module: ReadWritable
Filename: ReadWritable.cpp
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
#include "ReadWritable.h"
#include <iostream>
#include <cstring>
#include <iomanip>


using namespace std;

namespace sdds {
	ReadWritable::ReadWritable() {
		Csv = false;
	}


	bool ReadWritable::isCsv() const {
		return Csv;
	}

	void ReadWritable::setCsv(bool value) {
		Csv = value;
	}

	std::ostream& operator << (std::ostream& os, ReadWritable& obj) {
		//call the write function of the derived object
		obj.write(os);
		return os;
	}

	std::istream& operator >> (std::istream& is, ReadWritable& obj) {
		//call the read function of the derived object
		obj.read(is);
		return is;
	}
}