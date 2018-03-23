#include "ILogError.h"

namespace IObject
{
	namespace ISystemBase
	{
		ILogError::ILogError()
		{
		}
		ILogError::~ILogError()
		{
		}

			//write to file or 
		void ILogError::writeLog(const char* log, const int len)
		{
			_module.outputLog(log, len, LOG_ERROR);
		}

		ILogInterface *ILogError::getInstance()
		{
			static ILogError _instance;
			return &_instance;
		}
	}
}
