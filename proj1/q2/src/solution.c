#include <stdio.h>
#include <solution.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846

void print_result(sqlite3_stmt *stmt);

/* Double function that returns the square of a number */
void my_query_function(sqlite3_context* ctx, int nargs, sqlite3_value** values){
    //keep the number in radius
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
		for(col=0; col<sqlite3_column_count(stmt)-1; col++) {
			printf("%s|", sqlite3_column_text(stmt, col));
		}
		printf("%s", sqlite3_column_text(stmt, col));
		printf("\n");
	}


}

int main(int argc, char **argv){
	sqlite3 *db; //the database
	sqlite3_stmt    *stmt_q; //the query
	int rc;
    
    char *db_name = argv[1];
    char *node_one = argv[2];
    char *node_two = argv[3];

	rc = sqlite3_open(db_name, &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}
    if (argv[4]){
        printf("input error");
        return(1);
    }
    if (!argv[2]){
        printf("input error");
        return(1);
    }
    if (!argv[3]){
        printf("input error");
        return(1);
    }


	/* can only create the function after the db connection is established */
	//sqlite3_create_function( db, "hello_newman", 1, SQLITE_UTF8, NULL, hello_newman, NULL, NULL);
	sqlite3_create_function( db, "a_single_query", 4, SQLITE_UTF8, NULL, my_query_function, NULL, NULL);

	/* the functions can now be used in regular SQL! */
	char *sql_qry = "select a_single_query(a.lat,b.lat,a.lon,b.lon) " \
			 "from node a, node b " \
			 "where a.id = ? and b.id = ? ;";

	rc = sqlite3_prepare_v2(db, sql_qry, -1, &stmt_q, 0);
    //sqlite3_exec( db, "BEGIN TRANSACTION", 0, 0, 0 ); 


	if (rc != SQLITE_OK) {  
		fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

    sqlite3_bind_int64(stmt_q, 1,strtol(node_one, (char**) NULL, 10));
    sqlite3_bind_int64(stmt_q, 2,strtol(node_two, (char**) NULL, 10));
	print_result(stmt_q);
	sqlite3_finalize(stmt_q); //always finalize a statement

	sqlite3_close(db); //always close the connection
	return 0;
}


