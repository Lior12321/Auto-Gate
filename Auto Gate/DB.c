#include "DB.h"


//static pointer to the DB
static sqlite3* db = NULL; 

// try to open/create the DB. than create cars table (plate, owner)
// return true if all the process succeed
bool initDB(void) {
    char* errMsg = NULL;
    if (sqlite3_open("gate.db", &db)) {
        printf("Can't open DB: %s\n", sqlite3_errmsg(db));
        return false;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS Cars("
        "Plate TEXT PRIMARY KEY,"
        "Owner TEXT NOT NULL);";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool checkLicensePlate(const char* plate, char* ownerName) {
    sqlite3_stmt* stmt;
    const char* query = "SELECT Owner FROM Cars WHERE Plate = ?;";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, 0) != SQLITE_OK)
        return false;
    sqlite3_bind_text(stmt, 1, plate, -1, SQLITE_STATIC);

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* owner = (const char*)sqlite3_column_text(stmt, 0);
        strncpy_s(ownerName, sizeof(ownerName), owner, _TRUNCATE); // return the owner name
        found = true;
    }
    sqlite3_finalize(stmt);
    return found;
}

void addCar(const char* plate, const char* ownerName) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT OR IGNORE INTO Cars (Plate, Owner) VALUES ('%s', '%s');", plate, ownerName);
    char* errMsg = NULL;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    printf("Car with plate %s and owner %s added to the database.\n", plate, ownerName);
}

void printAllCars() {
	const char* query = "SELECT Plate, Owner FROM Cars;";
	sqlite3_stmt* stmt;

	if (isTableEmpty(db, "Cars")) {
		printf("No cars in the database.\n");
		return;
	}

	//prepare the query
	if (sqlite3_prepare_v2(db, query, -1, &stmt, 0) != SQLITE_OK) {
		printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
		return;
	}

	printf("Cars in the database:\n");
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		const char* plate = (const char*)sqlite3_column_text(stmt, 0);
		const char* owner = (const char*)sqlite3_column_text(stmt, 1);
		printf("Plate: %s, Owner: %s\n", plate, owner);
	}
	sqlite3_finalize(stmt);
}

void deleteCar(const char* plate) {
    const char* query = "SELECT Plate, Owner FROM Cars;";
    sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, query, -1, &stmt, 0) != SQLITE_OK) {
		printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
		return;
	}
	char ownerName[31];

	if (!checkLicensePlate(plate, ownerName)) {
		printf("Car with plate %s not found in the database.\n", plate);
		sqlite3_finalize(stmt);
		return;
	}
	char sql[256];
	snprintf(sql, sizeof(sql), "DELETE FROM Cars WHERE Plate = '%s';", plate);
	char* errMsg = NULL;
	if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
		printf("SQL error: %s\n", errMsg);
		sqlite3_free(errMsg);
	}
	else
		printf("%s car's with plate %s deleted from the database.\n", ownerName, plate);
}

void deleteDB() {
	char* errMsg = NULL;
	int rc = sqlite3_exec(db, "DELETE FROM Cars;", 0, 0, &errMsg);
	int deletedRows = sqlite3_changes(db);

	if (rc != SQLITE_OK) {
		printf("Failed to delete cars: %s\n", errMsg);
		sqlite3_free(errMsg);
	}
	else {
		printf("All cars deleted from the DB. %d row(s) deleted from the database\n", deletedRows);
	}
}

// close the DB 
void closeDB(void) {
    if (db) sqlite3_close(db);
}


bool isTableEmpty(sqlite3* db, const char* tableName) {
	char sql[256];
	snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM %s;", tableName);
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
		//printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
		return true; // assume empty on error
	}

	bool isEmpty = true;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		int count = sqlite3_column_int(stmt, 0);
		isEmpty = (count == 0);
	}
	sqlite3_finalize(stmt);
	return isEmpty;
}