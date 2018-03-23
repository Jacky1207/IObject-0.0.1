#include "ILogDebug.h"

		}

		ILogDebug::~ILogDebug()
		}

			//write to file or 
		void ILogDebug::writeLog(const char* log, const int len)
		ILogInterface *ILogDebug::getInstance()
		{
			static ILogDebug _instance;
			return &_instance;
		}
	}
}
