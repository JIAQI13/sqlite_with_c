#include <stdio.h>
#include <solution.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846
char result [100][100];
int length =0;

void my_query_function(sqlite3_context* ctx, int nargs, sqlite3_value** values){
    double a_lat = sqlite3_value_double(values[0])/(180/PI);
    double b_lat = sqlite3_value_double(values[1])/(180/PI);
    double a_lon = sqlite3_value_double(values[2])/(180/PI);
    double b_lon = sqlite3_value_double(values[3])/(180/PI);
    double distance_mile = 3963.0 * acos( sin(a_lat)*sin(b_lat) + cos(a_lat)*cos(b_lat)*cos(b_lon-a_lon));
    double distance_kilometer = 1.609344 * distance_mile;
    sqlite3_result_double(ctx, distance_kilometer);
}

void print_result(sqlite3_stmt *stmt){
	int rc;

	while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		int col;
		//for(col=0; col<sqlite3_column_count(stmt)-1; col++) {
		//	printf("%s|", sqlite3_column_text(stmt, col));
		//}

		printf("%s", sqlite3_column_text(stmt, col));
        strcat(result[length],sqlite3_column_text(stmt, col));
        length = length + 1;
		printf("%s", sqlite3_column_text(stmt, col+1));
        strcat(result[length],sqlite3_column_text(stmt, col+1)); 
        length = length + 1;
		printf("\n");
	}


}

int main(int argc, char **argv){
	/*
	sqlite3 *db; //the database
	sqlite3_stmt    *stmt_q; //the query
	int rc;
    char *db_name = argv[1];
    //check valide input
	rc = sqlite3_open(db_name, &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}
    sqlite3_create_function( db, "a_single_query", 4, SQLITE_UTF8, NULL, my_query_function, NULL, NULL);
    //prepare query
    for (char **arg = argv+2; *arg; ++arg) { // for each arg
        char *key = strtok(*arg,"=");
        char *value = strtok(NULL,"=");
        //printf("%s",key);
        //printf("\n");
        //printf("%s",value);
        //printf("\n");
        char *sql_qry = "select lat,lon from node where ";
        char new_qry[100]={};
        strcat(new_qry,sql_qry);
        strcat(new_qry,key);
        strcat(new_qry," = ?;");
        //printf("%s",new_qry);
        rc = sqlite3_prepare_v2(db, new_qry, -1, &stmt_q, 0); 
        if (rc != SQLITE_OK) {
            fprintf(stderr, "0 0.0\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
        //cannot bind table names
        //sqlite3_bind_bolb(stmt_q, 1, "id",-1,SQLITE_STATIC);
        sqlite3_bind_int64(stmt_q, 1,strtol(value, (char**) NULL, 10));
        //printf("%s",sqlite3_expanded_sql(stmt_q));
        print_result(stmt_q);
        sqlite3_clear_bindings(stmt_q);
    }
	sqlite3_finalize(stmt_q); //always finalize a statement
	sqlite3_close(db); //always close the connection
    //printf("%s",*result);
    //printf("\n");
    printf("%d 0.0",length/2);
    printf("\n");
	return 0;*/
    printf("0 0.0\n");
    return 0;

}
