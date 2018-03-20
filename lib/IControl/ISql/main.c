#include <stdio.h>
#include <stdlib.h>

#if 0
#include "sqlite3.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   printf("callback \n");
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("equipped.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT * from skill";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
#else

#include "IMap.h"
#include "IString.h"
int main()
{
	IMap<int , IString> map;

	for(int i=0; i<10; i++)
	{
		map.append(i, "this is a test");
	}

	map.setValue(4, "this is a setValue");
	map.insert(2, "this is a insert");

	for(int i=0; i<map.size(); i++)
	{
		printf("%d = %s \n", map[i].key(), map[i].value());
	}
}

#endif