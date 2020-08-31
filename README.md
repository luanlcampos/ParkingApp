# OOP244 - Parking Application

## Overview
A fully functional valet application that accepts cars and motorcycles.  
If the client is driving a car, the application will ask the user if they want to have it washed. However, if the client is driving a motorcycle, the application will ask if the client is using a sidecar.

## Park and Return
This application will park the vehicle in the first spot it finds available. When the vehicle is returned, that spot will be available again.  
When the park is already full, the application will not allow the user to park the vehicle.  

## Listing all the parked vehicles
This function was implemented to show the user all vehicles that are parked displaying the following information:
- Vehicle Type
- Parking Spot Number
- Licence Plate
- Make and Model
- Additional Option (Carwash or Sidecar)  
  
## Storing Information
The application is developed to read and store information from CSV files. There are two options inside the application: 
- Exit program
  - This option will save the information and quit the program
- Close Parking
  - This option will remove all vehicles from the parking and exit the program. Tipically used at the end of the day
  
The CSV file follows the format below:  
**Vehicle Type (C/M), Parking Spot Number (0-MAX), Licence Plate, Make and Model, Additional Option (0/1)**  
