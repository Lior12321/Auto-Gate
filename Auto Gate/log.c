#include "Log.h"
#define LOG_CHUNK 6


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
static size_t lastPrintedLine = 0; // remember the last printed line
static size_t totalLines = 0;

// Print logs in chunks of LOG_CHUNK lines
void printLogs(void) {


    if (!logFile) return;
    fclose(logFile);
    logFile = NULL;

    FILE* file = NULL;
    fopen_s(&file, "gate_log.txt", "r");
    if (!file) return;

	// count total lines in the file
    size_t totalLines = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) totalLines++;
    rewind(file);

	printf("Total log lines: %zu\n", totalLines); // printing size_t variable = %zu

    size_t lastPrintedLine = totalLines;

    char choice[4];
    while (lastPrintedLine > 0) {
        size_t start = lastPrintedLine > LOG_CHUNK ? lastPrintedLine - LOG_CHUNK : 0;

		// read and print lines from start to lastPrintedLine
        rewind(file);
        size_t currentLine = 0;
        while (fgets(buffer, sizeof(buffer), file)) {
            if (currentLine >= start && currentLine < lastPrintedLine)
                printf("%s", buffer);
            currentLine++;
        }
        lastPrintedLine = start;
        if (lastPrintedLine == 0) break;

        printf("\nPrint more logs? (y/n): ");
        scanf_s(" %c", &choice, 1);
        if (choice[0] != 'y' && choice[0] != 'Y') break;
		printf("\n");
    }
    fclose(file);

    // open the log file again in append mode
    fopen_s(&logFile, "gate_log.txt", "a");
}

// Close the log file
void closeLog(void) {
    if (logFile) fclose(logFile);
    logFile = NULL;
}
