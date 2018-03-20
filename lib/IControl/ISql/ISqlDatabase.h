#ifndef _ISQLDATABASE_H_
#define _ISQLDATABASE_H_

#include "IString.h"
#include "sqlite3.h"


namespace IObject
{
    namespace ISql
    {
        using namespace IObject::ISystemBase;
        //callback fun for result of exec
        typedef int (*callback)
        (
            void*  data,    	/* Data provided in the 4th argument of sqlite3_exec() */
            int    argc,      	/* The number of columns in row */
            char** argv,   		/* An array of strings representing fields in the row */
            char** azColName    /* An array of strings representing column names */
        );
        class ISqlDatabase
        {
        public:
            ISqlDatabase();
            virtual ~ISqlDatabase();

            //open db
            int open(const IString &str);
            int open(const char *db);
            //close db
            int close();
            //exec cmd
            int exec(const IString &str);
            int exec(const char *cmd);
            //get table
            int getTable(const char *strSql);

            void registerCallback(callback fun){SqlResultFun = fun;}
            void unregisterCallback(){SqlResultFun = nullptr;}
        private:
            //callback
            callback SqlResultFun;
            sqlite3 *	 _db;
        };
    }
}

#endif
