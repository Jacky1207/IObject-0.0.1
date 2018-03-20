#pragma once

#include "IMutex.h"
#include "IRunable.h"
#include "ISelect.h"

#if 1
#include <sys/timerfd.h>

namespace IObject
{
	namespace ISystemBase
	{
		typedef sg_void_t(* timeoutFun)();
		class ITimer : virtual public ISelect
		{
		public:
			ITimer();
			virtual ~ITimer();
			
			sg_int32_t start();
			sg_int32_t start(sg_int32_t msec);
			sg_int32_t stop();
			sg_int32_t restart();
			
			sg_void_t eventHandle(const sg_int32_t fd);
//			virtual sg_void_t timeout() = 0;
			sg_void_t registerTimeoutFun(timeoutFun fun){_fun = fun;}
		private:
			sg_void_t stopTimer();
			
			sg_int32_t _timerfd;
			IMutex _pMutex;
			timeoutFun _fun;
		};
	}
}
#endif
