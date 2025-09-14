#include "Log.h"

static FILE* logFile = NULL;

// Initialize the log file
bool initLog(const char* filename) {
    fopen_s(&logFile, "gate_log.txt", "a");
    return (logFile != NULL);
}

// Write a log entry
void writeLog(const char* plate, bool allowed) {
    if (!logFile) return;
    // i want to add to the log time and date of the event
    fprintf(logFile, "[%s] ", getCurrentTime());
    fprintf(logFile, "Plate: %s, Status: %s\n", plate, allowed ? "Allowed" : "Denied");
    fflush(logFile);
}

// Close the log file
void closeLog(void) {
    if (logFile) fclose(logFile);
    logFile = NULL;
}
