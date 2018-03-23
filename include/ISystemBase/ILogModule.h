#ifndef _ILOGMODULE_H_
#define _ILOGMODULE_H_

#include "IList.h"
#include "typedef.h"
namespace IObject
{
	namespace ISystemBase
	{
		class ILogModule
		{
		public:
			ILogModule();
			virtual ~ILogModule();

			void outputLog(const char* log, const int len, const LOG_LEVEL type);
			virtual void outputLogInfo(const char* log, const int len, const LOG_LEVEL type){;}
		private:
			IList<ILogModule *> _pLogModule;
		};
	}
}

#endif