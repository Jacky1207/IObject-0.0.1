#include "ILogWarn.h"

namespace IObject
{
	namespace ISystemBase
	{
		ILogWarn::ILogWarn()
		{
		}
		ILogWarn::~ILogWarn()
		{
		}

			//write to file or 
		void ILogWarn::writeLog(const char* log, const int len)
		{
			_module.outputLog(log, len, LOG_WARNING);
		}

		ILogInterface *ILogWarn::getInstance()
		{
			static ILogWarn _instance;
			return &_instance;
		}
	}
}
