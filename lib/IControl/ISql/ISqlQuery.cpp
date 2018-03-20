#include "ISqlQuery.h"

namespace IObject
{
    namespace ISql
    {
        ISqlQuery *ISqlQuery::_pSqlQuery = NULL;
    	ISqlQuery::ISqlQuery(const ISqlDatabase *db)
    	{
            _db = db;
    	}
    	ISqlQuery::~ISqlQuery()
    	{
            _db->unregisterCallback();
            _db = nullptr;
            ISqlQuery::_pSqlQuery = NULL;
            
            if(_queryResult.size() > 0)
            {
            	_queryResult.clear();
            }
    	}
    
    	bool ISqlQuery::isValid() const
    	{
    	}
    	bool ISqlQuery::isActive() const
    	{
    	}

        /*
         *  check if result is empty
         */
        bool ISqlQuery::isNull() const
    	{
            return !_queryResult.size();
    	}

    	bool ISqlQuery::isNull(const IString &name) const
    	{
    	}
    	int ISqlQuery::at() const
    	{
    	}
    	IString ISqlQuery::lastQuery() const
    	{
    	}

        bool ISqlQuery::isSelect() const
    	{
    	}
    	int ISqlQuery::size() const
    	{
            return _queryResult.size();
    	}
    	bool ISqlQuery::isForwardOnly() const
    	{
    	}

    	ISqlRecord ISqlQuery::record() const
    	{
    	}
    
    	void ISqlQuery::setForwardOnly(bool forward)
    	{
    	}

        void ISqlQuery::exec(const IString& query)
    	{
            _pSqlQuery = this;
            _db->registerCallback(ISqlQuery::queryResultFun);
            _db->exec(query);
    	}
        void ISqlQuery::exec(const char *query)
        {
            _pSqlQuery = this;
            _db->registerCallback(ISqlQuery::queryResultFun);
            _db->exec(query);
        }
    
    	bool ISqlQuery::seek(int i, bool relative = false)
    	{
    	}

    	bool ISqlQuery::next()
    	{
    	}

    	bool ISqlQuery::previous()
    	{
    	}

    	bool ISqlQuery::first()
    	{
    	}

    	bool ISqlQuery::last()
    	{
    	}
    
    	void ISqlQuery::clear()
    	{
    	}
    
    	bool ISqlQuery::nextResult()
    	{
            if(_queryIndex < size())
            {
                return true;
            }
            else
                return false;
    	}
    	//query result callback
    	int ISqlQuery::queryResultFun(void*  data, int  argc, char** argv, char** azColName)
    	{
            ISqlRecord record(argc, char **argv);
            _queryResult.append(record);
    	}
    }
}
