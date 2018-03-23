#ifndef _ILOGFILE_H_
#define _ILOGFILE_H_

#include "ILogModule.h"
#include "IRunable.h"
#include "IThread.h"
#include "IMutex.h"
#include "IList.h"
#include "IString.h"

namespace IObject
{
	namespace ISystemBase
	{
		class ILogFile : public ILogModule,  public IRunable
		{
		public:
			ILogFile();
			virtual ~ILogFile();

			virtual void run();
			virtual void outputLogInfo(const char* log, const int len, const LOG_LEVEL type);
		private:
			IString getLogFromList();
			void resetFileHandle();
			void getCurrentLogHandle();
			IString getCurrentTime();
			long getFileSize(const IString fileName);
			void writeLogImpl(const char* strLog, int len);
		private:
			IList<IString > _strLogList;
			FILE *	_pFile;
			bool	isActive;
			IMutex	_pLock;
			IThread _pThread;

			IString m_strFileName;
			IString m_strPath;
		};
	}
}

#endif