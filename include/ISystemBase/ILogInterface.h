#ifndef _ILOGINTERFACE_H_
#define _ILOGINTERFACE_H_

namespace IObject
{
	namespace ISystemBase
	{
		#define MAX_LOG_LEN	1024
		class ILogInterface
		{
		public:
			virtual void writeLog(const char* log, const int len) = 0;
//			virtual ILogInterface *getInstance() = 0;
		};
	}
}

#endif