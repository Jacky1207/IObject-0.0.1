#include "IInterface.h"
#include "ILog.h"

namespace IObject
{
	namespace IControl
	{
		IInterface::m_pInterface = NULL;
		IInterface::IInterface()
		{
		}

		IInterface::~IInterface()
		{
		}

		sg_void_t IInterface::eventHandle(const sg_int32_t fd)
		{
			LOG_WRITE(ISERIAL, LOG_DEBUG, "read data come %d",fd);

			char buf[1024] = {0};
			int len = read(fd,buf,1024);
			if(len > 0)
			{
				LOG_WRITE(ISERIAL, LOG_DEBUG, "read data %s - %d",buf, len);
				_readyReadFun(fd,buf,len);
			}
		}

		sg_void_t IInterface::setSocket(const sg_int32_t fd)
		{
			m_nSocketList.append(fd);
			ISelect::addEvent(fd);
		}

		IInterface *IInterface::getInstance()
		{
			if(NULL == m_pInterface)
			{
				m_pInterface = new IInterface();
			}
			return m_pInterface;
		}
	}
}