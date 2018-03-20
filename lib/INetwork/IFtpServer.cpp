#include "IFtpServer.h"
#include "ILog.h"

namespace IObject
{
	namespace INetwork
	{
		IFtpServer *_pFtpServerHandle = NULL;
	
		IFtpServer* IFtpServer::getInstance()
		{
			if(_pFtpServerHandle == NULL)
				_pFtpServerHandle = new IFtpServer();
		
			return _pFtpServerHandle;
		}
		
		IFtpServer::IFtpServer() : 
			_pTcpServer(NULL),
			_pFtpControl(NULL)
		{
		}

		IFtpServer::~IFtpServer()
		{
			if(_pTcpServer != NULL)
			{
				//_pTcpServer->
			}
		}

	}
}

