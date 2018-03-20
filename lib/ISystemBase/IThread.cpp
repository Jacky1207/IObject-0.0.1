#include "IThread.h"
#include "ILog.h"

namespace IObject
{
	namespace ISystemBase
	{
		IThread::IThread() :
				_runable(NULL)
		{
			
		}

		IThread::~IThread()
		{
			LOG_WRITE(ITHREAD ,LOG_DEBUG, "IThread thread exit+++++");
			
//			exit();
			_runable = NULL;
			LOG_WRITE(ITHREAD ,LOG_DEBUG, "ISelect thread exit-----");
		}

		sg_void_t* IThread::_start_route(void *p)
		{
			IThread *impl = (IThread *)p;
			
			impl->_runable->run();
			
			LOG_WRITE(ITHREAD ,LOG_DEBUG, "thread finish++++++++");
			pthread_exit( NULL);
		}

		sg_void_t IThread::start(IRunable *p)
		{
			_runable = p;
			int ret = pthread_create(&_pthread_t,NULL,_start_route,(void*)this);
			if(ret != 0)
			{
				perror("fail to create thread!\n");
			}
			//detach thread into unjoinable state
			pthread_detach( _pthread_t);
		}

		sg_void_t IThread::exit()
		{
			if(_pthread_t <= 0)
				return;
				
			pthread_exit( NULL);
			_pthread_t = 0;
		}

		sg_void_t IThread::msleep(sg_int32_t milliseconds)
		{
			usleep(milliseconds *1000);
		}
	}
}
