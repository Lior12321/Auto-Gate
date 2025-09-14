#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stdio.h>
#include "Util.h"

bool initLog(const char* filename);
void writeLog(const char* plate, bool allowed);
void closeLog(void);

#endif
