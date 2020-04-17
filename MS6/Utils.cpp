/* Citation and Sources...
Final Project Milestone 6
Module: Utils
Filename: Utils.cpp
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
#include <iostream>
#include <cstring>

using namespace std;

namespace sdds {
	//helper function
	int strcmpi(char* str1, char* str2) {
		//all letters to upper case to be able to use strcmp that is case sensitive
		int len1 = strlen(str1);
		for (int i = 0; i < len1; i++) {
			str1[i] = toupper(str1[i]); //toupper function to convert everything to upper
		}
		int len2 = strlen(str2);
		for (int i = 0; i < len2; i++) {
			str2[i] = toupper(str2[i]); //toupper function to convert everything to upper
		}

		return strcmp(str1, str2);
	}


	bool YesOrNo() {
		char answer[30];
		bool valid = false; //bool to exit the loop
		bool flag = false; // returning bool that checks if the answer was yes or no

		do {
			cin.getline(answer, '\n');
			if (strlen(answer) > 1) {
				cin.clear();
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}
			else {
				if (strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0) {
					flag = true;
					valid = true;
				}
				else if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0) {
					flag = false;
					valid = true;
				}
				else {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					cin.clear();
				}
			}


		} while (!valid);

		return flag;
	}
}