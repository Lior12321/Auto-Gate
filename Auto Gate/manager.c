#include "manager.h"


void managerMode(char manager[8]) {
	printf("welcome to manager mode.\n please enter manager password: ");
	char input[8];
	char password[8] = "abcd1234";
	scanf_s("%8s", input, (unsigned)sizeof(input));
	if (strcmp(input, password) != 0) {
		printf("wrong password, exiting manager mode.\n");
		return false;
	}
	printf("access granted, welcome manager.\n");
	while (true) {
		printf("choose an option:\n"
			"1. add car to the DB\n"
			"2. search car in the DB by its plate\n"
			"3. search car in the DB by its owner name\n"
			"4. view all cars in the DB\n"
			"5. delete car from the DB"
			"6. delete all cars from the DB\n"
			"7. view logs"
			"8. exit manager mode\n");
	}
	int choice;
	if (scanf_s(" %d", &choice) != 1)
		return '\0';

	switch (choice) {
	case 1:
		addCar();
		break;
	case 2:
		//searchCarByPlate();
		break;
	case 3:
		//searchCarByOwner();
		break;
	case 4:
		//viewAllCars();
		break;
	case 5:
		//deleteCar();
		break;
	case 6:
		//deleteAllCars();
		break;
	case 7:
		//viewLogs();
		break;
	case 8:
		printf("exiting manager mode.\n");
		return true;
		break;
	}
}

void addCar(void) {

}

void cleanupDB(void) {

}



bool vehicleDetected(void) {

}

bool processVehicle(void) {

}
