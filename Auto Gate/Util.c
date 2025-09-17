#include "Util.h"

// global variable to track gate state
extern bool isGateOpen;

void sleep(int seconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + seconds * CLOCKS_PER_SEC);
}

const char* getCurrentTime(void) {
    static char buffer[20];
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", tm_info);
    return buffer;
}

bool takingInput(const char* validInputs) {
    char input = getInputChar();

    if (strchr(validInputs, input)) {
        if (input == 'q' || input == 'Q') {
            if (isGateOpen) {
                printf("Invalid input. Please enter y or n: ");
                return takingInput(validInputs);
            }
            // Handle quit input
            printf("Exiting the program...\n");
            sleep(1);
            closeLog();
            closeDB();
            exit(0);
        }
        return (input == 'y' || input == 'Y'); // return true for 'y' and false for 'n'
    }
    printf("Invalid input. Please enter y or n: ");
    return takingInput(validInputs);
}

char getInputChar() {
    char input;
    if (scanf_s(" %c", &input) != 1) 
        return '\0';

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    return input;
}