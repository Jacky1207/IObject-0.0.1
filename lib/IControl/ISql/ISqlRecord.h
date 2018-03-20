#ifndef _ISQLQUERY_H_
#define _ISQLQUERY_H_

/****************************************************************
 *
 *							ISqlRecord
 *	this class is a record in database. 
 *	
 *
 *
 *
 *
 ****************************************************************/
 
#include "IString.h"
#include "IVector.h"

namespace IObject
{
    namespace ISql
    {
        class ISqlRecord
        {
        public:
            ISqlRecord();
            ISqlRecord(const int num, const char** record);
            ~ISqlRecord();

            void addRecord(const int num, const char** record);
            const int getRecordSize(){return _recordSize;}
            const IString &getRecordValue(const int index);
        private:
            IVector<IString > _record;
            int _recordSize;
        };
    }
}

#endif
