#include "ILogDebug.h"

namespace IObject
{
	namespace ISystemBase
	{
		ILogDebug::ILogDebug()
		{
		}

		ILogDebug::~ILogDebug()
		{
		}

			//write to file or 
		void ILogDebug::writeLog(const char* log, const int len)
		{
			_module.outputLog(log, len, LOG_DEBUG);
		}

		ILogInterface *ILogDebug::getInstance()
		{
			static ILogDebug _instance;
			return &_instance;
		}
	}
}
