/* ------------------------------------------------------
Final Project Milestone 6
Module: ReadWritable
Filename: ParkingAppTester.cpp
Version 0.9
Author	Fardad Soleimanloo
Revision History
-----------------------------------------------------------
Date      Reason
2020/4/5  Preliminary release
-----------------------------------------------------------*/
//getting memory leak
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <fstream>
#include <iostream>
#include <ctype.h>
#include "Parking.h"
using namespace std;
using namespace sdds;

void runParking() {
   Parking P("ParkingData.csv", 11);
   P.run();
}

void pause() {
    cout << "<------------------------" << endl << "Press Enter to continue...";
    cin.ignore(1000, '\n');
}

void ShowDatafile() {
   char ch;
   ifstream file("ParkingData.csv");
   cout << endl << "Content of ParkingData.csv after the program exits" << endl;
   cout << "-----------------------------------------------------------" << endl;
   while (file.get(ch)) {
      cout <<char(tolower(ch));
   }
   cout <<  "-----------------------------------------------------------" << endl;
   cout << "To restore the data back to the original values " << endl;
   cout << "Copy \"ParkingData.csv.bak\" over \"ParkingData.csv\"" << endl;
}
//int main() {
//   runParking();
//   ShowDatafile();
//   _CrtDumpMemoryLeaks();
//   return 0;
//}

int main() {
    cout << "Pass 1: ------->" << endl;
    runParking();
    ShowDatafile();
    pause();
    cout << "Pass 2: ------->" << endl;
    runParking();
    ShowDatafile();
    pause();
    cout << "Pass 3: ------->" << endl;
    runParking();
    ShowDatafile();
    _CrtDumpMemoryLeaks();
    return 0;
}

