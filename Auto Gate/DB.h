#ifndef DB_H //if we dosen't create already the DB
#define DB_H //create it (in the copilation stage)

#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool initDB(void);                       // open/create the DB
bool checkLicensePlate(const char* plate, char* ownerName); // if the plate exist return true
void addCar(const char* plate, const char* ownerName);      // add car to the DB
void closeDB(void);                      // close the DB

#endif
