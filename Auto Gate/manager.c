#include "manager.h"


void managerMode() {
	printf("\n=============================\n\n"
		"welcome to manager mode.\n"
		"please enter manager password: ");
	char input[9];
	char password[8] = "abcd1234";
	scanf_s("%8s", input, 9);
	if (!strcmp(input, password)) {
		printf("wrong password, exiting manager mode.\n"
			"\n=============================\n\n");
		return;
	}
	printf("access granted, welcome manager.\n");
	while (true) {
		printf("choose an option:\n"
			"1. add car to the DB\n"
			"2. search for car in the DB\n"
			"3. view all cars in the DB\n"
			"4. delete car from the DB\n"
			"5. delete all cars from the DB\n"
			"6. view logs\n"
			"7. exit manager mode\n");

		int choice;
		if (scanf_s(" %d", &choice) != 1)
			return '\0';

		switch (choice) {
		case 1:
			addCarToDB();
			break;
		case 2:
			searchForCar();
			break;
		case 3:
			viewAllCars();
			break;
		case 4:
			deleteCarFromDB();
			break;
		case 5:
			deleteAllCars();
			break;
		case 6:
			viewLogs();
			break;
		case 7:
			printf("exiting manager mode.\n"
				"\n=============================\n\n");
			return;
		}
	}
}

void addCarToDB() {
	char plate[8];
	char owner[30];
	getCarDetails(&plate, &owner);
	addCar(plate, owner);
}

void searchForCar() {
	char plate[8];
	char owner[30];
	getCarDetails(&plate, &owner);
	if (checkLicensePlate(plate, owner)) {
		printf("car with plate %s found in the DB, owner: %s\n", plate, owner);
	}
	else {
		printf("car with plate %s not found in the DB\n", plate);

	}
}

void viewAllCars(void) {

}


void deleteCarFromDB(void) {

}


void deleteAllCars(void) {

}


void viewLogs(void) {

}

// helping function to get car details from user
void getCarDetails(char* plate, char* owner) {
	printf("enter car plate: ");
	scanf_s("%8s", plate, 9);
	printf("enter owner name: ");
	scanf_s("%30s", owner, 31);
}