#ifndef _ILOG_H_
#define _ILOG_H_

#include "ILogInterface.h"
#include "IString.h"
#include "ILogError.h"
#include "ILogDebug.h"
#include "ILogWarn.h"

namespace IObject
{
	namespace ISystemBase
	{
	#if 1
		#define LOG_WRITE(mode,level,format,...)  ILog::getInstance()->writeLog(mode,level,"[%d](%s):" format,__LINE__,__FUNCTION__,##__VA_ARGS__)
	#else
		#define LOG_WRITE(mode,level,format,...) 
	#endif
		class ILog
		{
		public:
			ILog();
			~ILog();
			static ILog *getInstance();

			void writeLog(const IString module, int level, IString format, ...);
		private:
			ILogInterface * _interface;
			inline int getConfigLogLevel(){return LOG_DEBUG;}
			IString getCurrentTime();

			static ILog *_pLogHandle;
		};
	}
}

#endif