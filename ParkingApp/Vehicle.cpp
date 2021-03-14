/* Citation and Sources...
Final Project Milestone 6
Module: Vehicle
Filename: Vehicle.cpp
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

#include "Vehicle.h"
#include <iostream>
#include<string.h>
#include <cstring>
#include <iomanip>

using namespace std;

namespace sdds {
	//constructors
	Vehicle::Vehicle() {
		licensePlate = nullptr;
		makeModel = nullptr;
		parkingSpot = 0;
	}

	Vehicle::Vehicle(const char* plate, const char* model) {
		if (plate != nullptr && plate[0] != '\0' && strlen(plate) <= MAX_PLATE && model != nullptr && model[0] != '\0' && strlen(model) > 1) { //model should have more than one char?
			//set values
			//setting plate
			int platelen = strlen(plate) + 1;
			licensePlate = new char[platelen];
			strcpy(licensePlate, plate);
			
			//setting model
			int modelLen = strlen(model) + 1;
			makeModel = new char[modelLen];
			strncpy(makeModel, model, modelLen);
			parkingSpot = 0;

		}

		else {
			//don't call setEmpty() due to conditional jump on initialized values
			licensePlate = nullptr;
			makeModel = nullptr;
			parkingSpot = 0;
		} 
	}

	Vehicle::~Vehicle() {
		delete[] licensePlate;
		licensePlate = nullptr;


		delete[] makeModel;
		makeModel = nullptr;

	}

	//Empty functions
	void Vehicle::setEmpty() {	
		if (licensePlate != nullptr) delete[] licensePlate;

		licensePlate = nullptr;

		if(makeModel != nullptr) delete[] makeModel;
		
		makeModel = nullptr;

		parkingSpot = 0;
	}

	bool Vehicle::isEmpty() const {
		return licensePlate == nullptr && makeModel == nullptr && parkingSpot == 0;
	}

	//getter functions
	char* Vehicle::getLicensePlate() const {
		return licensePlate;
	}

	char* Vehicle::getMakeModel() const {
		return makeModel;
	}

	//setter makeModel
	void Vehicle::setMakeModel(char* model) {
		if (model != nullptr || model[0] != '\0') {
			delete[] makeModel;
			makeModel = nullptr;
			int modelLen = strlen(model) + 1;	
			makeModel = new char[modelLen];
			strncpy(makeModel, model, modelLen);
		}
		else {
			setEmpty();
		}
	}


	//get parking spot number
	int Vehicle::getParkingSpot() const {
		return parkingSpot;
	}

	//set parking spot
	void Vehicle::setParkingSpot(const int spot) {
		if (spot >= 0) parkingSpot = spot;

		else setEmpty();
	}

	//case insensitive comparing to a string
	bool Vehicle::operator==(const char* plate) const{
		char str1[MAX_PLATE + 1] = { '\0' };
		strcpy(str1, getLicensePlate());
		char str2 [MAX_PLATE + 1] = { '\0' };
		strcpy(str2, plate);
		return strcmpi(str1, str2) == 0;


		//return (toupper(*licensePlate) == toupper(*plate));

	}

	//case insensitive comparing to another object
	bool Vehicle::operator==(const Vehicle& v) const {
		char str1[MAX_PLATE + 1] = { '\0' };
		strcpy(str1, getLicensePlate());
		char str2[MAX_PLATE + 1] = { '\0' };
		strcpy(str2, v.getLicensePlate());
		return strcmpi(str1, str2) == 0;

		//return (toupper(*getLicensePlate()) == toupper(*v.getLicensePlate()));
	}

	std::istream& Vehicle::read(std::istream& is) {
		//vehilce with csv true
		if (this->isCsv()) {

			parkingSpot = 0;

			//reading the  parking spot
			is >> parkingSpot; //read integer for spot number
			is.ignore(); //ignore a comma

			//reading license plate
			char tempPlate[MAX_PLATE + 1]; //temp license plate
			is.getline(tempPlate, MAX_PLATE + 1, ','); //Read 8 chars or until find a comma
			int len = strlen(tempPlate);
			for (int i = 0; i < len; i++) {
				tempPlate[i] = toupper(tempPlate[i]); //toupper function to convert everything to upper
			}
			if (licensePlate != nullptr) {
				delete[] licensePlate;
				licensePlate = nullptr;
			}
			licensePlate = new char[strlen(tempPlate) + 1];
			strcpy(licensePlate, tempPlate); //setting the license plate

			//reading the make model
			char tempModel[61];
			is.getline(tempModel, 61, ',');
			setMakeModel(tempModel);
		} //end of csv true if

		else {
			parkingSpot = 0;
			//getting license plate
			cout << "Enter Licence Plate Number: ";
			char plate[30] = { '\0' };
			bool flag = false;
			do {
				is.getline(plate, '\n');
				if (strlen(plate) > MAX_PLATE || plate == nullptr || plate[0] == '\0') {
					cout << "Invalid Licence Plate, try again: ";
					//is.ignore(1000, '\n');
					is.clear();
				}
				else {
					int len = strlen(plate);
					for (int i = 0; i < len; i++) {
						plate[i] = toupper(plate[i]); //toupper function to convert everything to upper
					}
					flag = true;
				}

			} while (!flag);
			
			//getting the makemodel
			cout << "Enter Make and Model: ";
			char model[61];
			flag = false;
			
			do {
				is.getline(model, 61);
				if (strlen(model) > 61 || strlen(model) <= 1)  {
					is.clear();
					//is.ignore(1000, '\n');
					cout << "Invalid Make and model, try again: ";
				}
				else {
					flag = true;
				}

			} while (!flag);

			if (model[0] != '\0' && plate[0] != '\0' && strlen(model) <= 61 && strlen(model) > 1 && strlen(plate) > 1 && strlen(plate) <= MAX_PLATE) {
				if (licensePlate != nullptr) {
					delete[] licensePlate;
					licensePlate = nullptr;
				}
				licensePlate = new char[strlen(plate) + 1];
				strcpy(licensePlate, plate);
				is.clear();
				flag = true;

				if (makeModel != nullptr) {
					delete[] makeModel;
					makeModel = nullptr;
				}
				setMakeModel(model);
			}

		} //end of else not csv file

		if (!is) {
			this->setEmpty();
		}


		return is;
	}

	std::ostream& Vehicle::write(std::ostream& os) const {
		if (isEmpty()) {
			os << "Invalid Vehicle Object" << endl;
		}

		else {
			if (isCsv()) {
				os << parkingSpot << ',' << licensePlate << ',' << makeModel << ',';
			}
			else {
				//printing the park spot
				os << "Parking Spot Number: ";
				parkingSpot == 0 ? os << "N/A" : os << parkingSpot;
				os << endl;

				//printing license plate
				os << "Licence Plate: " << licensePlate;
				os << endl;

				//printing make model
				os << "Make and Model: " << makeModel << endl; 


			}
		} //end of else(!isCSV)


		return os;
	}
}


