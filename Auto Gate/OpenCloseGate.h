#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "sqlite3.h"
#include "DB.h"
#include "Log.h"
#include "Util.h"
#include "manager.h"


extern bool isGateOpen;

bool vehicleDetected();
bool vehicalPassing();
void openGate();
void closeGate();