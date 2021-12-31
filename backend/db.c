#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

//Compile with: gcc -o db db.c -I/usr/include/postgresql -lpq -std=c99

void do_exit(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
    
    exit(1);
}


int main() {
    
    PGconn *conn = PQconnectdb("dbname=defaultdb user=doadmin password=HvJSAGgg096Ixq5D host=db-postgresql-delta12542-do-user-6976795-0.b.db.ondigitalocean.com port=25060 sslmode=require");
    PGresult *res = PQexec(conn, "select json_agg(t) FROM (SELECT * from notes) t");    
    printf("%s", PQgetvalue(res, 0, 0));
    PQclear(res);
    PQfinish(conn);
    return 0;
}

