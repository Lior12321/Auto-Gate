#pragma once
#include <time.h> // for sleep
#include <stdio.h> // for printf
#include "log.h"
#include "DB.h"


void sleep(int seconds);
const char* getCurrentTime(void);
bool takingInput(const char* validInputs);
char getInputChar();