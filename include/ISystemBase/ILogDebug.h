#ifndef _ILOGDEBUG_H_
#define _ILOGDEBUG_H_

#include "ILogInterface.h"
#include "ILogModule.h"

namespace IObject
{
	namespace ISystemBase
	{
		class ILogDebug : public ILogInterface
		{
		public:
			ILogDebug();
			virtual ~ILogDebug();

			//write to file or 
			void writeLog(const char* log, const int len);
			static ILogInterface *getInstance();
		private:
			ILogModule _module;
			static ILogDebug *_pDebug;
		};
	}
}

#endif