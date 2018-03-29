#include "ILogDebug.h"

namespace IObject
{
	namespace ISystemBase
	{
		ILogInterface *ILogDebug::_pDebug = NULL;
		ILogDebug::ILogDebug()
		{
			printf("IDEBUG new\n");
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
			printf("ILogDebug---\n");
//			static ILogDebug _instance;
			if(_pDebug == NULL)
			{
				_pDebug = new ILogDebug();
			}
			printf("ILogDebug***\n");
			return _pDebug;
//			return &_instance;
		}
	}
}
