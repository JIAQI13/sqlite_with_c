//jiaqi liu 1514854
//source : http://zetcode.com/db/sqlitec/
//
#include <sqlite3.h>
#include <stdio.h>

int main(void) {
    
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("edmonton.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    char *sql = "CREATE TABLE node ( id INTEGER, lat FLOAT, lon FLOAT, PRIMARY KEY (id) );" 
                "CREATE TABLE nodetag ( id INTEGER, k TEXT, v TEXT, CONSTRAINT Nodetagid FOREIGN KEY (id) REFERENCES node(id) );" 
                "CREATE TABLE way ( id INTEGER PRIMARY KEY, closed BOOLEAN );" 
                "CREATE TABLE waypoint ( wayid INTEGER, ordinal INTEGER, nodeid INTEGER, CONSTRAINT Wayid FOREIGN KEY (wayid) REFERENCES way(id), CONSTRAINT Nodeid FOREIGN KEY (nodeid) REFERENCES Node(id));" 
                "CREATE TABLE waytag ( id INTEGER, k TEXT, v TEXT,  CONSTRAINT Waytagid FOREIGN KEY (id) REFERENCES way(id) );"
                "CREATE TRIGGER check_ordinal BEFORE INSERT ON Waypoint WHEN  NEW.ordinal< 0 OR NEW.ordinal > (SELECT COUNT(nodeid) FROM Waypoint WHERE wayid = NEW.wayid) BEGIN SELECT RAISE (ABORT,'ERROR: ordinal number wrong!'); END;";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    
    return 0;
}
