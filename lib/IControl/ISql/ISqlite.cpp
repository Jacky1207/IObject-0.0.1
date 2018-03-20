#include "ISqlite.h"
#include "ILog.h"

namespace IObject
{
	namespace ISql
	{
		ISqlite::ISqlite() : 
			_db(NULL)
		{
			
		}
		
		ISqlite::~ISqlite()
		{
			if(_db != NULL)
				sqlite3_close(_db);
			_db = NULL;
		}
		
		int ISqlite::open(const IString &str)
		{
			int ret = sqlite3_open(str.data(), &_db);

			if( rc != SQLITE_OK )
			{
				LOG_WRITE(SQLITE, LOG_ERROR, "open database %s failed", str.data());
				return ret;
			}
			
			LOG_WRITE(SQLITE, LOG_INFO, "open database %s successed", str.data());
			return ret;
		}
		//close db
		int ISqlite::close()
		{
			if (sqlite3_close(_db) == SQLITE_OK)
			{
				_db = 0;
				LOG_WRITE(SQLITE, LOG_INFO, "close database successed", str.data());
			}
		}
		//exec cmd
		int ISqlite::exec(const IString &str)
		{
			char* szError=0;

			int nRet = sqlite3_exec(_db, str.data(), SqlResultFun, 0, &szError);
			if(nRet != SQLITE_OK)
			{
				LOG_WRITE(SQLITE, LOG_ERROR, "exec %s failed", str.data());
			}
		}
		
		int ISqlite::getTable(const char* strSql)
		{
			char* szError=0;
			char** paszResults=0;
			int nRet;
			int nRows(0);
			int nCols(0);

			nRet = sqlite3_get_table(_db, strSql, &paszResults, &nRows, &nCols, &szError);

			if (nRet == SQLITE_OK)
			{
				for(int i=0;i < nCols; i++)
					for(int j=0;j < nRows; j++)
						printf("table [%d][%d] = %s\n", i, j, paszResults[i][j]);
			}
			else
			{
				LOG_WRITE(SQLITE, LOG_ERROR, "get table failed: %s", szError);
			}
		}
	}
}