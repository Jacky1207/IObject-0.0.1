#pragma once

#include "ITcpServer.h"
#include "IFtpControl.h"

namespace IObject
{
	namespace INetwork
	{
	#define FTP_CMD_PORT	21
	#define FTP_DATA_PORT	20
	
		class IFtpServer
		{
		public:
			IFtpServer();
			virtual ~IFtpServer();

			static IFtpServer *getInstance();
		private:
			ITcpServer  *_pTcpServer;
			IFtpControl *_pFtpControl;
		};
	}
}