#pragma once

#include <stdio.h>
#include "Util.h"
#include "OpenCloseGate.h"
#include "DB.h"
#include "Log.h"

void managerMode();
void addCarToDB();
void searchForCar();
void viewAllCars(void);
void deleteCarFromDB(void);
void deleteAllCars(void);
void viewLogs(void);
void getCarDetails(char*, char*);