#ifndef _ILOGERROR_H_
#define _ILOGERROR_H_

#include "ILogInterface.h"
#include "ILogModule.h"

namespace IObject
{
	namespace ISystemBase
	{
		class ILogError : public ILogInterface
		{
		public:
			ILogError();
			virtual ~ILogError();

			//write to file or 
			void writeLog(const char* log, const int len);
			static ILogInterface *getInstance();
		private:
			ILogModule _module;
		};
	}
}

#endif