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

// close the DB 
void closeDB(void) {
    if (db) sqlite3_close(db);
}
