#include "ISqlDatabase.h"
#include "ILog.h"

namespace IObject
{
    namespace ISql
    {
        ISqlDatabase::ISqlDatabase()
        {
        }

        ISqlDatabase::~ISqlDatabase()
        {
            if(_db != NULL)
                sqlite3_close(_db);
            _db = NULL;
        }

        int ISqlDatabase::open(const char *db)
        {
            int ret = sqlite3_open(db, &_db);

            if( ret != SQLITE_OK )
            {
                LOG_WRITE(SQLITE, LOG_ERROR, "open database %s failed", db);
                return ret;
            }

            LOG_WRITE(SQLITE, LOG_INFO, "open database %s successed", db);
            return ret;
        }

        int ISqlDatabase::open(const IString &str)
        {
            int ret = sqlite3_open(str.data(), &_db);

            if( ret != SQLITE_OK )
            {
                LOG_WRITE(SQLITE, LOG_ERROR, "open database %s failed", str.data());
                return ret;
            }

            LOG_WRITE(SQLITE, LOG_INFO, "open database %s successed", str.data());
            return ret;
        }
        //close db
        int ISqlDatabase::close()
        {
            int ret = sqlite3_close(_db);
            if (SQLITE_OK == ret)
            {
                _db = 0;
                LOG_WRITE(SQLITE, LOG_INFO, "close database successed", str.data());
            }
            return ret;
        }
        //exec cmd
        int ISqlDatabase::exec(const IString &str)
        {
            char* szError=0;

            int nRet = sqlite3_exec(_db, str.data(), SqlResultFun, 0, &szError);
            if(nRet != SQLITE_OK)
            {
                LOG_WRITE(SQLITE, LOG_ERROR, "exec %s failed", str.data());
            }
            return nRet;
        }

        int ISqlDatabase::exec(const char *cmd)
        {
            char* szError=0;

            int nRet = sqlite3_exec(_db, cmd, SqlResultFun, 0, &szError);
            if(nRet != SQLITE_OK)
            {
                LOG_WRITE(SQLITE, LOG_ERROR, "exec %s failed", str.data());
            }

            return nRet;
        }
    }
}
