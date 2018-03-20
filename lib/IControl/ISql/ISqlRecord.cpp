#include "ISqlRecord.h"

namespace IObject
{
    namespace ISql
    {
        ISqlRecord::ISqlRecord()
        {
            _recordSize = 0;
        }

        ISqlRecord::ISqlRecord(const int num, const char** record) :
            _queryIndex(0)
        {
            addRecord(num, record);
        }

        ISqlRecord::~ISqlRecord()
        {
            if(_recordSize != 0)
                _record.clear();
        }

        void ISqlRecord::addRecord(const int num, const char** record)
        {
            _recordSize = num;
            for(int i=0; i<_recordSize; i++)
            {
                IString str = IString(record[i]);
                _record.append(str);
            }
        }

        IString &ISqlRecord::getRecordValue(int index)
        {
            return _record[index];
        }
    }
}
