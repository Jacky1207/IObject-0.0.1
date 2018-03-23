#include "ILog.h"
#include <string>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <list>

namespace IObject
{
	namespace ISystemBase
	{
		ILog::ILog() : 
			_interface(NULL)
		{
		}

		ILog::~ILog()
		{

		}

		ILog *ILog::_pLogHandle = new ILog();
		ILog *ILog::getInstance()
		{
			printf("2-1-------------------\n");
			return _pLogHandle;
//			static ILog _log;
			printf("2---------------------\n");
//			return &_log;
		}

		IString ILog::getCurrentTime()
		{
			time_t timer = time(NULL);
			struct tm  *p = localtime(&timer);

			char buff[64] = { 0 };
			snprintf(buff,sizeof(buff)-1 , "%04d-%02d-%02d %02d.%02d.%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
			return IString(buff);
		}


		void ILog::writeLog(const IString module, int level, IString format, ...)
		{
			printf("3---------------------\n");
			if (level > getConfigLogLevel())
				return;
			
			char buff[MAX_LOG_LEN];
			memset(buff, 0, MAX_LOG_LEN);
			va_list arg;

			va_start(arg, format);
			vsprintf(buff, format.data(), arg);
			va_end(arg);

			ILogInterface * _interface;
			switch (level)
			{
			case LOG_SYSTEM:
				break;
			case LOG_ERROR:
				_interface = ILogError::getInstance();
				break;
			case LOG_WARNING:
				_interface = ILogWarn::getInstance();
				break;
			case LOG_INFO:
				break;
			case LOG_DEBUG:
				_interface = ILogDebug::getInstance();
				break;
			}

			char prin[MAX_LOG_LEN] = { 0 };
			IString time = getCurrentTime();
			snprintf(prin, sizeof(prin)-1, "[%s][%s]:%s\r\n", time.data(), module.data(), buff);

			printf("write log %s\n", prin);
			_interface->writeLog(prin, strlen(prin));
		}

	}
}