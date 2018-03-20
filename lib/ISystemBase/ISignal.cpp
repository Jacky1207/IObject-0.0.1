#include "ISignal.h"

namespace IObject
{
	namespace ISystemBase
	{
		ISignal::ISignal()
		{
		}
		
		ISignal::~ISignal()
		{
		}
		
		/*event type  1-29*/
		void ISignal::init(int type)
		{
			_signalType = EVENT(type);
			if(signal(_signalType, _signalFun)== SIG_ERR)
				printf("signal touch error error");
		}
		
		/*user space signal*/
		void ISignal::attachUserSignal()
		{
			
		}
			
		/*kernal space signal*/
		void ISignal::attachKernelSignal(int fd_dev)
		{
			int ret,oflags;
			fcntl(fd_dev, F_SETOWN, getpid());
			//设置信号的类型，SIGIO不需要设置，系统默认就是发送SIGIO，其他类型需要设置
			fcntl(fd_dev, F_SETSIG, _signalType);
			oflags = fcntl(fd_dev, F_GETFL);
			ret = fcntl(fd_dev, F_SETFL, oflags | FASYNC);
		}
	}
	
}