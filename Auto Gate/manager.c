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
		printf("\nchoose an option:\n"
			"1. add car to the DB\n"
			"2. search for car in the DB\n"
			"3. view all cars in the DB\n"
			"4. delete car from the DB\n"
			"5. delete all cars from the DB\n"
			"6. view logs\n"
			"7. exit manager mode\n"
			"\n");

		int choice;
		if (scanf_s(" %d", &choice) != 1) { // input validation - check if input is an integer
			printf("invalid input, please try again.\n");
			while (getchar() != '\n'); // clear input buffer
			continue;
		}

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
				"=============================\n\n");
			return;
		default:
			printf("invalid choice, please try again.\n");
			while (getchar() != '\n'); // clear input buffer
			break;
		}
	}
}

void addCarToDB() {
	char plate[9];
	char owner[31];
	getCarDetails(plate, owner);
	addCar(plate, owner);
}

void searchForCar() {
	char plate[9];
	char owner[31];
	getPlateDetails(&plate);
	if (checkLicensePlate(plate, owner)) {
		printf("car with plate %s found in the DB, owner: %s\n", plate, owner);
	}
	else
		printf("car with plate %s not found in the DB\n", plate);
}

void viewAllCars(void) {
	printf("=============================\n");
	printAllCars();
	printf("=============================\n");

}


void deleteCarFromDB(void) {
	char plate[9];
	getPlateDetails(plate);
	deleteCar(plate);
}


void deleteAllCars(void) {
	char input;
	printf("are you sure you want to delete all cars from the DB? (y/n): ");
	scanf_s(" %c", &input, 1);
	if (input == 'y' || input == 'Y') {
		printf("enter manager password to confirm: ");
		char passInput[9];
		scanf_s("%8s", passInput, 9);
		if (strcmp(passInput, "abcd1234")) {
			printf("wrong password, deletion cancelled\n");
			return;
		}
		deleteDB();

	}
	else {
		printf("deletion cancelled\n");
	}

}


void viewLogs(void) {
	printf("=============================\n");
	printLogs();
	printf("=============================\n");

}

// helping function to get car details from user
void getCarDetails(char* plate, char* owner) {
	printf("enter car plate: ");
	scanf_s("%8s", plate, 9);
	printf("enter owner name: ");
	scanf_s("%30s", owner, 31);
}

void getPlateDetails(char* plate) {
	printf("enter car plate: ");
	scanf_s("%8s", plate, 9);
}