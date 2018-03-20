#ifndef _ISQLITE_H_
#define _ISQLITE_H_

/*************************************************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 ************************************************************************/

#include "sqlit3.h"
#include "IString.h"

namespace IObject
{
	namespace ISql
	{
		//callback fun for result of exec
		typedef int (*callback)
		(
			void*  data,    	/* Data provided in the 4th argument of sqlite3_exec() */
			int    argc,      	/* The number of columns in row */
			char** argv,   		/* An array of strings representing fields in the row */
			char** azColName    /* An array of strings representing column names */
		);
		
		class ISqlite
		{
		public:
			ISqlite();
			~ISqlite();
			
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
		private:
			//callback
			static callback SqlResultFun;
			sqlite3 *	 _db;
		};
	}
}

#endif