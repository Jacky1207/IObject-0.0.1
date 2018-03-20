#ifndef _ISQLTABLE_H_
#define _ISQLTABLE_H_

/**************************************************************
 *						ISqlTable
 *
 *
 *	rows:			�����ݵ�����(��Ҫ����1�� ����������)
 *	column��		�����ݵ�����
 *	char** paszResults.	������ݴ��ڶ�ά�����У������ܳ����� (rows+1)*column
 *	
 *
 *
 *
 *************************************************************/

namespace IObject
{
	namespace ISql
	{
		class ISqlTable
		{
		public:
			ISqlTable();
			ISqlTable(const ISqlTable& rTable);
			ISqlTable(char** paszResults, int nRows, int nCols);
			virtual ~ISqlTable();
			ISqlTable& operator=(const ISqlTable& rTable);

			int numFields();

			int numRows();

			const char* fieldName(int nCol);

			const char* fieldValue(int nField);
			const char* fieldValue(const char* szField);

			int getIntField(int nField, int nNullValue=0);
			int getIntField(const char* szField, int nNullValue=0);

			double getFloatField(int nField, double fNullValue=0.0);
			double getFloatField(const char* szField, double fNullValue=0.0);

			const char* getStringField(int nField, const char* szNullValue="");
			const char* getStringField(const char* szField, const char* szNullValue="");

			bool fieldIsNull(int nField);
			bool fieldIsNull(const char* szField);

			void setRow(int nRow);

			void finalize();
		private:
			bool checkResults();

			int _nCols;
			int _nRows;
			int _nCurrentRow;
			char** _paszResults;
		};
		
	}
}

#endif