/* Citation and Sources...
Final Project Milestone 6
Module: Menu
Filename: Menu.cpp
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

#include "Menu.h"
#include <iostream>
#include <cstring>
#include <iomanip>


using namespace std;

namespace sdds {
	/*------------------------------------------------------------------
						 MenuItem Functions Definition
	------------------------------------------------------------------*/
	void MenuItem::setEmpty() {
		delete[] item_name;
		item_name = nullptr;
	}
	bool MenuItem::isEmpty() const{
		bool flag = false;
		if (item_name == nullptr) {
			flag = true;
		}
		return flag;
	}

	MenuItem::MenuItem() {
		setEmpty();
	}

	MenuItem::MenuItem(const char* name) {
		setItem(name);
	}
	
	void MenuItem::setItem(const char* item) {
		if (item != nullptr) {
			int size = strlen(item) + 1;
			item_name = new char[size];
			strncpy(item_name, item, size);
		}
		else {
			setEmpty();
		}
	}

	MenuItem::~MenuItem() {
		delete[] item_name;
		item_name = nullptr;
	}

	std::ostream& MenuItem::display(std::ostream& os) const{
		if (!isEmpty()) {
			os << item_name << endl;
		}
		
		return os;
	}
	/*------------------------------------------------------------------
	                     Menu Functions Definition
	------------------------------------------------------------------*/

	
	bool Menu::isEmpty() const {
		bool flag = false;
		if (menu_title == nullptr) {
			flag = true;
		}

		return flag;
	}
	Menu::Menu() {
		menu_title = nullptr;
		items[0] = nullptr;
		menuSize = 0;
		indentation = 0;
	}

	Menu::Menu(const char* title, const int ind) {
		//setting the menu to nullptr
		menu_title = nullptr;
		items[0] = nullptr;
		menuSize = 0;
		indentation = ind;
		//if the input is correct, set the title
		if (title != nullptr) {
			operator=(title); 
		}
		//if the input is not valid, the menu is already in a empty space
	}

	Menu::Menu(const Menu& menu) {
		//setting the menu to nullptr
		menu_title = nullptr;
		items[0] = nullptr;
		menuSize = 0;
		indentation = menu.indentation;
		//if the input is correct, set the title
		if (menu) {
			operator=(menu);
		}
		//if the input is not valid, the menu is already in a empty space
	}

	Menu::~Menu() {
		setEmpty();
	}

	void Menu::setEmpty() {
		if (menu_title != nullptr) {
			delete[] menu_title;
			menu_title = nullptr;
			for (int i = 0; i < menuSize; i++) {
				delete items[i];
			}

			menuSize = 0;
		}

	}

	Menu& Menu::operator=(const Menu& copy) {
		if (this != &copy) {
			setEmpty(); //clear the menu
			if (!copy.isEmpty()) {
				operator=(copy.menu_title);
				for (int i = 0; i < copy.menuSize; i++) {
					add(copy.items[i]->item_name);
				}
			}
			//shallow copy
			indentation = copy.indentation;
		}
			
		return *this;
	}

	Menu::operator bool() const{
		return (!isEmpty()) ? true : false;
	}

	std::ostream& Menu::display(std::ostream& os) const{
		
		if (Menu::isEmpty()) {
			os << "Invalid Menu!" << endl;
		}

		else {

			indent(indentation);

			os << menu_title << endl;

			if (menuSize > 0) {
				for (int i = 0; i < menuSize; i++) {
					indent(indentation);
					os << i + 1 << "- ";
					items[i]->display();
				}

				indent(indentation);
				os << "> ";

			}
			else {
				os << "No Items to display!" << endl;
			}
		}

		return os;
	}

	Menu& Menu::operator = (const char* str) {
		if (str != nullptr) {
			delete[]menu_title;
			menu_title = new char[strlen(str) + 1];
			strcpy(menu_title, str);
		}
		else {
			setEmpty();
		}
		return *this;
	}

	void Menu::add(const char* item) {
		if (!isEmpty() && menuSize <= MAX_NO_OF_ITEMS) {
			if (item != nullptr) {
				items[menuSize] = new MenuItem(item);
				menuSize++;
				items[menuSize] = nullptr;
			}
			else {
				setEmpty();
			}
		}
	}

	Menu& Menu::operator << (const char* item) {
		add(item);
		return *this;
	}

	int Menu::run(std::istream& is, std::ostream& os) const {
		int selection = 0;
		bool isValid = false;
		display();
		if (menuSize == 0) {
			selection = 0;
		}
		else if (!isEmpty() && menuSize > 0) {
			do {
				int tmp;
				is >> tmp;
				is.ignore(1000, '\n');
				if (!is) {
					os << "Invalid Integer, try again: ";
					is.clear();
					is.ignore(1000, '\n');
				}
				else if (tmp <= 0 || tmp > menuSize) {
					is.clear();
					os << "Invalid selection, try again: ";
				}
				else {
					selection = tmp;
					isValid = true;
				}
			} while (!isValid);
		}
		return selection;
	}

	Menu::operator int() const {
		return run();
	}
	void indent(int ind, std::ostream& os) {
		for (int j = 0; j < ind; j++) {
			os << setfill(' ') << setw(4) << ' ';
		}
	}

	void Menu::setInd(const int ind) {
		indentation = ind;
	}
}


