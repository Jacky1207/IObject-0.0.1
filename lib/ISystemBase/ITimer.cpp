#include "ITimer.h"
#include "ILog.h"

#if 1
namespace IObject
{
	namespace ISystemBase
	{
		ITimer::ITimer() : 
				_timerfd(-1),
				_fun(NULL)
		{
			_timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
			if(_timerfd < 0)
			{
				LOG_WRITE(ITIMER , LOG_ERROR, "timerfd_create failed!");
			}
		}
		
		ITimer::~ITimer()
		{
			if(_timerfd > 0)
				close(_timerfd);
			
			LOG_WRITE(ITIMER , LOG_DEBUG, "~ITimer!");
		}
		
		sg_int32_t ITimer::start(sg_int32_t mesc)
		{
			AutoLock lk(_pMutex);

			int sec = mesc / 1000;
			int ns  = mesc % 1000;
			struct itimerspec newTimer;
			newTimer.it_value.tv_sec = sec;
			newTimer.it_value.tv_nsec = ns * 1000;
			newTimer.it_interval.tv_sec = 0;
			newTimer.it_interval.tv_nsec = 0;
			
			int ret = timerfd_settime(_timerfd, 0, &newTimer, NULL);
			if(ret < 0)
			{
				LOG_WRITE(ITIMER ,LOG_ERROR, "timerfd_settime failed!");
				close(_timerfd);
				return -1;
			}
			
			LOG_WRITE(ITIMER ,LOG_DEBUG, "add timer event %d", _timerfd);
			addEvent(_timerfd);
		}
		
		sg_int32_t ITimer::stop()
		{
//			AutoLock lk(_pMutex);
			LOG_WRITE(ITIMER ,LOG_DEBUG, "remove timer event %d", _timerfd);
			stopTimer();
			removeEvent(_timerfd);
		}
		
		sg_int32_t ITimer::restart()
		{
			AutoLock lk(_pMutex);
			LOG_WRITE(ITIMER ,LOG_DEBUG, "remove timer event %d",_timerfd);
			struct itimerspec newTimer;
			int ret = timerfd_gettime(_timerfd, &newTimer);
			if(ret < 0)
			{
				LOG_WRITE(ITIMER ,LOG_ERROR, "timer restart failed!");
			}
			LOG_WRITE(ITIMER ,LOG_DEBUG, "timer restart success!");
		}
		
		sg_void_t ITimer::eventHandle(const sg_int32_t fd)
		{
			AutoLock lk(_pMutex);
			LOG_WRITE(ITIMER ,LOG_DEBUG, "timeout event %d",fd);
			if(fd == _timerfd)
			{
				if(_fun != NULL)
				{
					LOG_WRITE(ITIMER ,LOG_DEBUG, "timeout fun -->");
					_fun();
				}
			}
		}
		
		sg_void_t ITimer::stopTimer()
		{
			AutoLock lk(_pMutex);
			struct itimerspec newTimer;
			newTimer.it_value.tv_sec = 0;
			newTimer.it_value.tv_nsec = 0;
			newTimer.it_interval.tv_sec = 0;
			newTimer.it_interval.tv_nsec = 0;
			
			int ret = timerfd_settime(_timerfd, 0, &newTimer, NULL);
			if(ret < 0)
			{
				LOG_WRITE(ITIMER ,LOG_ERROR, "timer stop failed!");
			}
			LOG_WRITE(ITIMER ,LOG_DEBUG, "timer stop success!");
		}
	}
}
#endif
