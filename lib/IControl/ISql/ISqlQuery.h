#ifndef _ISQLQUERY_H_
#define _ISQLQUERY_H_

#include "IString.h"
#include "ISqlRecord.h"
#include "ISqlDatabase.h"

namespace IObject
{
    namespace ISql
    {
        class ISqlQuery
        {
        public:
           ISqlQuery(const ISqlDatabase *db);
           ~ISqlQuery();

           bool isValid() const;
           bool isActive() const;
           bool isNull() const;
           bool isNull(const IString &name) const;
           int at() const;
           IString lastQuery() const;
           int numRowsAffected() const;
           bool isSelect() const;
           int size() const;
           bool isForwardOnly() const;
           ISqlRecord record() const;

           void exec(const IString *query);
           void exec(const char *query);

           bool seek(int i, bool relative = false);
           bool next();
           bool previous();
           bool first();
           bool last();

           void clear();

           // prepared query support
           bool exec();
           bool prepare(const IString& query);
           IString executedQuery() const;
           void finish();
           bool nextResult();
        private:
           IVector<ISqlRecord > _queryResult;
           ISqlDatabase *_db;
           int _queryIndex;

           static ISqlQuery *_pSqlQuery;
           static int queryResultFun(void*  data, int  argc, char** argv, char** azColName);
        };
    }
}

#endif
