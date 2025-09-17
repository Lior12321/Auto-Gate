#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Util.h"
#include "OpenCloseGate.h"
#include "DB.h"
#include "Log.h"



int main() {
    //basic initializations tests
    if (!initDB()) return 1; // if DB init fail, exit
    if (!initLog("gate.log.txt")) return 1; // if log init fail, exit

    //adding cars to the DB for the simulation
    addCar("ABC1234", "John Doe");
    addCar("XYZ5678", "Jane Smith");
	addCar("LMN8901", "Alice Johnson");


    char choice;
    while (1) { // infinity loop
        printf("\nthe system is up and running...\npress q to exit\n");
        //scanf_s(" %c", &choice, 1);
        //if (choice == 'q' || choice == 'Q')
        if (vehicleDetected()) {
            openGate();
            closeGate();
        }
        sleep(1); // wait for 3 seconds before next check to avoid overloading the CPU
    }
    return 0;
}
