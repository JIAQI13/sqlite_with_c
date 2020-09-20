#include <stdio.h>
#include <solution.h>
#include <sqlite3.h>
#include <string.h>
#include <math.h> 
#include <stdlib.h>
#include <time.h>
void print_result(sqlite3_stmt *stmt,char *l){
        int rc;
        while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int col;
            for(col=0; col<sqlite3_column_count(stmt)-1; col++) {
                printf("%s|", sqlite3_column_text(stmt, col));
            }
            printf("%s", sqlite3_column_text(stmt, col));
            printf("    %s    ",l);
        }
}

int main(int argc, char **argv) {
    sqlite3 *db; //the database
    sqlite3_stmt    *stmt_q; //the query
    int rc;
    int retval;
    char *db_name = argv[1];
    char *k = argv[2];
    char *l = argv[3];

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
    char *sql_qry = "select max(x),max(y) from nodeC"; 
    rc = sqlite3_prepare_v2(db, sql_qry, -1, &stmt_q, 0);
    if (rc != SQLITE_OK) {  
        fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    //get the value from the query
    int maxx,maxy;
    int count=0;
    while(1){
        retval = sqlite3_step(stmt_q);
        if(retval == SQLITE_ROW)
        {
            maxx =(int)sqlite3_column_int(stmt_q, count);
            maxy =(int)sqlite3_column_int(stmt_q, count+1);
            count=count+1;
            //printf("%d\n",maxx);
            //printf("%d\n",maxy);
        }else{
            sqlite3_finalize(stmt_q); //always finalize a statement
            break;
        }
    }
    int height,width,x1,x2,y1,y2;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    //get the value to perform the calculation
    for(int i=0;i<atoi(k);i=i+1){
        height=rand()%10*atoi(l);
        width=rand()%10*atoi(l);
        x1=rand()%maxx;
        y1=rand()%maxy;
        x2=x1+width;
        y2=y1+height;

    char *sql_qry_new = "SELECT COUNT(*) FROM areaMBR a WHERE ?<a.minX<? AND ?<a.maxX<? AND ?<a.minY<? AND ?<a.maxY<?";
    rc = sqlite3_prepare_v2(db, sql_qry_new, -1, &stmt_q, 0);
    if (rc != SQLITE_OK) {  
        fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_int64(stmt_q,1,x1);
    sqlite3_bind_int64(stmt_q,2,x2);
    sqlite3_bind_int64(stmt_q,3,x1);
    sqlite3_bind_int64(stmt_q,4,x2);
    sqlite3_bind_int64(stmt_q,5,y1);
    sqlite3_bind_int64(stmt_q,6,y2);
    sqlite3_bind_int64(stmt_q,7,y1);
    sqlite3_bind_int64(stmt_q,8,y2);
    //printf("%s",sqlite3_expanded_sql(stmt_q));
    print_result(stmt_q,l);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n",cpu_time_used);
    sqlite3_finalize(stmt_q); //always finalize a statement
    }
    end = clock();
    char *eptr;
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n",cpu_time_used/strtod(k,&eptr));
    sqlite3_close(db); //always close the connection
    return 0;
}
