/* Citation and Sources...
Final Project Milestone 6
Module: Menu
Filename: Menu.h
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
#ifndef _SDDS_MENU_H
#define _SDDS_MENU_H
#include<iostream>

namespace sdds {
	const int MAX_NO_OF_ITEMS = 10; //max number of items per menu

	class MenuItem {
		friend class Menu;
		char* item_name;

		//Constructors and destructors
		MenuItem(); //default constructor
		MenuItem(const char*); //constructor to set item name if the input is valid 
		~MenuItem(); //destructor


		void setItem(const char*); //if the input is valid, set the name of the item
		void setEmpty(); //empty state
		bool isEmpty() const; //returns true if menu item is null
		std::ostream& display(std::ostream& os = std::cout) const; //displays the item name


		//prohibiting copying and assigning
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator = (const MenuItem&) = delete;
	};

	class Menu {
		char* menu_title;
		MenuItem* items[MAX_NO_OF_ITEMS];
		int menuSize;
		int indentation;

	public:
		void setInd(const int ind);
		//Constructors and destructors
		Menu(); //default constructor
		Menu(const char*, const int ind = 0); //menu constructor passing a char and the indentation. If no ind, ind =0
		Menu(const Menu&); //copy constructor
		~Menu(); //Menu destructor
		
		//operators
		Menu& operator = (const Menu& copy); //copy assingment operator passing a menu reference
		Menu& operator = (const char* str); //assignment operator passing a string
		operator bool() const; //returns true if it is not empty
		operator int() const; 
		Menu& operator << (const char*); //uses the add function to add items in the menu 
		
		
		void setEmpty();
		bool isEmpty() const;
		std::ostream& display(std::ostream& os = std::cout) const; //display the menu title and items
		void add(const char*); //adds items in the menu
		int run(std::istream& is = std::cin, std::ostream& os = std::cout) const; //display the options and accepts the user input
	};

	void indent(int ind, std::ostream& os = std::cout); //indentation
	
}

#endif