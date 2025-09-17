#ifndef DB_H //if we dosen't create already the DB
#define DB_H //create it (in the copilation stage)

#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool initDB();												// open/create the DB
bool isTableEmpty(sqlite3*, const char*);
bool checkLicensePlate(const char* plate, char* ownerName); // if the plate exist return true
void addCar(const char* plate, const char* ownerName);      // add car to the DB
void printAllCars();										// print all cars in the DB
void deleteCar(const char* plate);							// delete car from the DB
void deleteDB();											// delete all cars from the DB
void closeDB();												// close the DB

#endif
