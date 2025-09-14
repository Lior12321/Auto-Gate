#pragma once

#include <stdio.h>
#include "Util.h"
#include "OpenCloseGate.h"
#include "DB.h"
#include "Log.h"

void managerMode(char);
void cleanup(void);
void addCar(void);
bool vehicleDetected(void);
bool processVehicle(void);
