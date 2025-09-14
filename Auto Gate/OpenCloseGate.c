#include "OpenCloseGate.h"

bool isGateOpen = false;
char validInputs[] = { 'y', 'Y', 'n', 'N' , 'q', 'Q' };


bool vehicleDetected(){
    //currently just a simulation with user input
    printf("Is there a vehicle in front of the gate? (y/n): ");
	return takingInput(validInputs);


    // TODO: here would be the actual sensor reading logic
    //return false;
}

bool vehicalPassing() {
    //currently just a simulation with user input
    char input;
    printf("Is the vehicle passed completely? (y/n): ");
    return !takingInput(validInputs);
	scanf_s(" %c", &input, 1);
    return !(input == 'y' || input == 'Y'); // return flase if vehicle is still passing

    //TODO: add check if the vehicle has passed completly and only then close the gate
    //return false;
}

void openGate() {
    char licensePlate[8];
    char DBlicensePlate[8];
    printf("Enter license plate: ");
    scanf_s("%8s", licensePlate, (unsigned)sizeof(licensePlate));
    if (!strcmp(licensePlate, "manager")){
		//enter manager mode
		managerMode();
		return;
	}
    char ownerName[30];
    if (checkLicensePlate(licensePlate,ownerName)) {
        printf("License plate %s recognized, Hello %s \n", licensePlate, ownerName);
        printf("Gate is opening!\n");
        isGateOpen = true;
        writeLog(licensePlate, isGateOpen);
        sleep(1); // keep the gate open for 10 seconds
    }
    else {
        printf("sorry, you are not allowed to enter!\n");
        isGateOpen = false;
        writeLog(licensePlate, isGateOpen);
        sleep(1); // wait for 1 second before next check
    }

    //TODO: add conncection to DB and take the name of the vehicle owner according to the license plate and print hello + name
}

void closeGate() {
    if (!isGateOpen) return; // if gate is not open, do nothing
    while (vehicalPassing()) {
        printf("Vehicle is passing, wait...\n");
        sleep(3);
    }
    printf("Gate is closing!\n");
    isGateOpen = false;
}
