/* Citation and Sources...
Final Project Milestone 6
Module: Parking
Filename: Parking.cpp
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
#include "Parking.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream> //for files
#include <iomanip>


using namespace std;

namespace sdds {
	Parking::Parking() {
		file_name = nullptr;
		parking_menu = nullptr;
		vehicle_menu = nullptr;
		parking_spots = 0;
		spots_parked = 0;
		for (int i = 0; i < MAX_PARKING; i++) {
			spot[i] = nullptr;
		}
	}

	Parking::Parking(const char* file, int nOfSpots) {
		if (file == nullptr || file[0] == '\0' || nOfSpots < 10 || nOfSpots > MAX_PARKING) {
			cout << "Error in data file" << endl;
			file_name = nullptr;
			parking_menu = nullptr;
			vehicle_menu = nullptr;
			parking_spots = 0;
			spots_parked = 0;
			for (int i = 0; i < MAX_PARKING; i++) {
				spot[i] = nullptr;
			}
			
		}
		else {
			int size = strlen(file) + 1;
			file_name = new char[size];
			strcpy(file_name, file);
			//setting the number of spots
			parking_spots = nOfSpots;
			//setting the vehicle pointers to null
			for (int i = 0; i < MAX_PARKING; i++) {
				spot[i] = nullptr;
			}
			//setting the spots parked
			spots_parked = 0;
			//call the load data file function
			if (loadDataFile()) {
				//setting parking menu tiltle and menu items
				parking_menu = "Parking Menu, select an action:";
				parking_menu << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Close Parking (End of day)" << "Exit Program";

				//setting vehicle menu title and menu items
				vehicle_menu = "Select type of the vehicle:";
				vehicle_menu.setInd(1);
				vehicle_menu << "Car" << "Motorcycle" << "Cancel";

				
			}
			else {
				cout << "Error in data file" << endl;
				file_name = nullptr;
				parking_menu = nullptr;
				vehicle_menu = nullptr;
				parking_spots = 0;
				spots_parked = 0;
				for (int i = 0; i < MAX_PARKING; i++) {
					spot[i] = nullptr;
				}
			}
		}

	}

	Parking::~Parking() {
		//call the save data file
		saveDataFile();
		delete[] file_name;
		//delete all the parking members
		for (int i = 0; i < spots_parked; i++)
			if (spot[i] != nullptr)
				delete spot[i];
		parking_menu.~Menu();
		vehicle_menu.~Menu();
	}

	bool Parking::isEmpty() const {
		return (file_name == nullptr ? true : false);
	}

	void Parking::parkingStatus(std::ostream& os) const {
		os << "****** Seneca Valet Parking ******" << endl;
		os << "*****  Available spots: ";
		//4 spaces, left justified, print number of avaiable parking spots
		os << setfill(' ') << setw(4) << left <<(parking_spots - spots_parked) ;
		os << " *****" << endl;
	}

	void Parking::parkVehicle(std::ostream& os, std::istream& is) {
		//this function will park the vehicle depeding on user input

		if ((parking_spots - spots_parked) == 0) { //checking if parking is full
			os << "Parking is full" << endl;
		}

		else {
			int choice;
			Vehicle* V = nullptr;
			choice = vehicle_menu.run();
			int index = 0;
			switch (choice) {
			case 1: { //if user selects a car
				delete V;
				V = nullptr;
				V = new Car;
				V->setCsv(false);
				V->read();
				bool valid = true;
				
				//checking for plates in the parking
				for (int i = 0; valid && i < parking_spots; i++) {
					if (spot[i] != nullptr) {
						//if it finds the same license plate in the parking, it exits with this msg
						if (*V == *spot[i]) {
							os << endl << "Can not park; license plate already in the system!" << endl;
							os << *V << endl;
							delete V;
							V = nullptr;
							valid = false;
						}
					}

				}
				//if the license plate is not parked it parks the car in the right spot
				if (valid) {

					for (int i = 0; i < parking_spots; i++) {
						if (spot[i] == nullptr) {
							index = i;
							break;
						}
					}
					spot[index] = V;
					spot[index]->setParkingSpot(index + 1);
					spots_parked++;
					os << endl <<"Parking Ticket" << endl;
					os << *spot[index] << endl;
				}
				break;
			}
		
			case 2: { //user selects motorcycle
				//os << "Parking Motorcycle" << endl;
				delete V;
				V = nullptr;
				V = new Motorcycle;
				V->setCsv(false);
				V->read();
				bool valid = true;
				//checking for plates in the parking
				for (int i = 0; valid && i < parking_spots; i++) {
					if (spot[i] != nullptr) {
						//if it finds the same license plate in the parking, it exits with this msg
						if (*V == *spot[i]) {
							os << endl << "Can not park; license plate already in the system!" << endl;
							os << *V << endl;
							delete V;
							V = nullptr;
							valid = false;
						}
					}

				}

				//if the license plate is not parked it parks the car in the right spot
				if (valid) {
					for (int i = 0; i < parking_spots; i++) {
						if (spot[i] == nullptr) {
							index = i;
							break;
						}
					}
					spot[index] = V;
					spot[index]->setParkingSpot(index + 1);
					spots_parked++;
					os << endl << "Parking Ticket" << endl;
					os << *spot[index] << endl;
				}
				break;

			}

			case 3: //if user selects to cancel 
				os << "Parking cancelled" << endl;
				break;
			}

		}
	}

	void Parking::returnVehicle(std::ostream& os) {
		os << "Return Vehicle" << endl;
		os << "Enter Licence Plate Number: ";
		char plate[30] = { '\0' };
		bool flag = false;
		do {
			cin.getline(plate, '\n');
			if (strlen(plate) > MAX_PLATE && plate != nullptr && plate[0] != '\0') {
				cout << "Invalid Licence Plate, try again: ";
				//is.ignore(1000, '\n');
				cin.clear();
			}

			else {
				//search for the plate in the parking
				bool find = false;
				for (int i = 0; !find && i < parking_spots; i++) {
					if (spot[i] != nullptr) {
						//if it's found, remove the vehicle and set the index to nullptr
						if (*spot[i] == plate) {
							spots_parked--;
							spot[i]->setCsv(false);
							os << endl << "Returning: " << endl;
							os << *spot[i] << endl;
							delete spot[i];
							spot[i] = nullptr;
							flag = true;
							find = true;
							break;
						}
						else{ 
							find = false;
						}

					}
				}
				if (!find) {
					int testLen = strlen(plate);
					for (int i = 0; i < testLen; i++) {
						plate[i] = toupper(plate[i]);
					}
					os << endl << "License plate " << plate << " Not found" << endl << endl;
					flag = true;
				}
			}

		} while (!flag);
	}

	void Parking::listParkedVehicles(std::ostream& os) const {
		os << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < parking_spots; i++) {
			//prints parked vechiles
			if (spot[i] != nullptr) {
				spot[i]->setCsv(false);
				os << *spot[i];
				os << "-------------------------------" << endl;
			}
		}

	}

	bool Parking::closePark(std::ostream& os) {
		bool flag = true;

		//if parking is not empty, displays a confirmation message to the user and closes the parking printing all the removed vehicles
		if (spot == nullptr) {
			os << "Closing Parking" << endl;
		}
		else {
			os << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			os << "Are you sure? (Y)es/(N)o: ";
			if (!YesOrNo()) {
				os << "Aborted!" << endl;
				flag = false;
			}
			else {
				os << "Closing Parking" << endl;

				for (int i = 0; i < parking_spots; i++) {
					if (spot[i] != nullptr) {
						spot[i]->setCsv(false);
						os << endl << "Towing request" << endl;
						os << "*********************" << endl;
						os << *spot[i];
						delete spot[i];
						spot[i] = nullptr;
					}
				}

				//set empty the file
				ofstream f;
				f.open(file_name, ios_base::trunc);
				f.close();
				//remove(file_name);



				flag = true;
			}
			
		}

		return flag;
	}

	bool Parking::exitPark(std::ostream& os, std::istream& is) {
		os << "This will terminate the program!" << endl;
		os << "Are you sure? (Y)es/(N)o: ";
		bool flag = YesOrNo(); // returning bool that checks if the answer was yes or no
		
		cout << "Exiting program!" << endl;
		return flag;
	}

	bool Parking::loadDataFile(std::ostream& os) {
		bool flag = false; 

		if (!isEmpty()) {
		
			ifstream f; //file object
			f.open(file_name); //open the file

			if (!f.is_open()) {
				f.close();
				flag = true; //empty state, first time running the app
			}

			else {
			
				int nOfVehicles = 0;
				char vehicleType;
				//checking for the vehicle
				while (f.good()) { //read until end of file

					Vehicle* V = nullptr;
					//reads the first char that determines if it is a car or motorcycle
					while (f >> vehicleType) {
						//ignore a comma
						f.ignore();
						//create a new car or motorcycle depending on the input
						if (vehicleType == 'M') {
							V = new Motorcycle;
						}

						else if (vehicleType == 'C') {
							V = new Car;
						}
						V->setCsv(true);
						V->read(f);
						nOfVehicles++;
						if (f.good()) { 
							int index = V->getParkingSpot(); 
							spot[index - 1] = V;
							spots_parked++;
						}
						//if not, delete the vehice
						else {
							delete V;
						}

					}
				}
				f.close();
				
				if (nOfVehicles <= parking_spots) {
					flag = true;
				}
				
			}
		}

		return flag;
	}

	bool Parking::saveDataFile(std::ostream& os) {
		bool flag = false;
		//open a file and save all the data from the parking inside in a csv mode
		ofstream f;
		f.open(file_name);
		if (f.is_open()) {
			
			for (int i = 0; i < parking_spots; i++) {
				if (spot[i] != nullptr) {
					spot[i]->setCsv(true);
					spot[i]->write(f);
				}
			}
			flag = true;
			f.close();
		}
		else 
			f.close();

		return flag;
	}

	int Parking::run(std::ostream& os) {
		int flag = 0;
		if (!isEmpty()) {
			bool exit = false;
			do {
				parkingStatus();
				int choice;
				choice = parking_menu.run();

				if (choice == 1) {
					parkVehicle();
				}

				if (choice == 2) {
					returnVehicle();
				}

				if (choice == 3) {
					listParkedVehicles();
				}

				if (choice == 4) {
					if (closePark()) exit = true;
				}

				if (choice == 5) {
					if (exitPark()) exit = true;
				}


			} while (!exit);
		}
		else flag = 1;

		return flag;
	}

} //end of sdds