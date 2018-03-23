#ifndef _ILOGWARN_H_
#define _ILOGWARN_H_

#include "ILogInterface.h"
#include "ILogModule.h"

namespace IObject
{
	namespace ISystemBase
	{
		class ILogWarn : public ILogInterface
		{
		public:
			ILogWarn();
			virtual ~ILogWarn();

			//write to file or 
			void writeLog(const char* log, const int len);
			static ILogInterface *getInstance();
		private:
			ILogModule _module;
		};
	}
}

#endif