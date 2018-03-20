#include "ISqlTable.h"
#include "ILog.h"

namespace IObject
{
	namespace ISql
	{
		ISqlTable::ISqlTable()
		{
			_nCols = 0;
			_nRows = 0;
			_nCurrentRow = 0;
			_paszResults = 0;
		}
		ISqlTable::ISqlTable(const ISqlTable& rTable)
		{
		}
		ISqlTable::ISqlTable(char** paszResults, int nRows, int nCols)
		{
			_nCols = nCols;
			_nRows = nRows;
			_nCurrentRow = 0;
			_paszResults = paszResults;
		}
		virtual ISqlTable::~ISqlTable()
		{
		}
		ISqlTable& operator=(const ISqlTable& rTable)
		{
			_nCols = rTable._nCols;
			_nRows = rTable._nRows;
			_nCurrentRow = rTable._nCurrentRow;
			_paszResults = rTable._paszResults;	
			
			return *this;
		}

		int ISqlTable::numFields()
		{
			if(!checkResults())
				return -1;
			return _nCols;
		}

		int ISqlTable::numRows()
		{
			if(!checkResults())
				return -1;
			return _nRows;
		}

		const char* ISqlTable::fieldName(int nCol)
		{
			if(!checkResults())
				return NULL;

			if (nCol < 0 || nCol > _nCols-1)
			{
				LOG_WRITE(SQLITE, LOG_ERROR, "field col number is wrong!");
			}

			return _paszResults[nCol];
		}

		const char* ISqlTable::fieldValue(int nField)
		{
			if(!checkResults())
				return NULL;
			
			
		}
		
		const char* ISqlTable::fieldValue(const char* szField)
		{
			
		}

		int ISqlTable::getIntField(int nField, int nNullValue);
		int ISqlTable::getIntField(const char* szField, int nNullValue);

		double ISqlTable::getFloatField(int nField, double fNullValue);
		double ISqlTable::getFloatField(const char* szField, double fNullValue);

		const char* ISqlTable::getStringField(int nField, const char* szNullValue);
		const char* ISqlTable::getStringField(const char* szField, const char* szNullValue);

		bool ISqlTable::fieldIsNull(int nField);
		bool ISqlTable::fieldIsNull(const char* szField);

		void ISqlTable::setRow(int nRow);

		void ISqlTable::finalize();	
		bool ISqlTable::checkResults()
		{
			if(_paszResults == NULL)
			{
				LOG_WRITE(SQLITE, LOG_ERROR, "table field is null!");
				return false;
			}
			
			return true;
		}
	}
}

#endif