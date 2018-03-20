#include "IUdpServer.h"

namespace IObject
{
	namespace INetwork
	{	
		IUdpServer::IUdpServer() : 
			_pSocket(NULL),
			isActive(true)
		{
			_pSocket = new IUdpSocket();
		}
		
		IUdpServer::~IUdpServer()
		{
			isActive = false;
			if(_pSocket != NULL)
			{
				delete _pSocket;
				_pSocket = NULL;
			}
			
			LOG_WRITE(NETWORK ,LOG_INFO, "~IUdpServer");
		}
		
		sg_void_t IUdpServer::startUdpServer(const sg_int32_t port)
		{
			_pSocket->startUdpServer("", port);
			_pThread.start(this);
		}
	
		sg_int32_t IUdpServer::sendMsg(const sg_string_t destIp,const sg_int32_t destPort, const sg_char_t* buff, const sg_int32_t leng)
		{
			return _pSocket->sendUdpMsg(destIp, destPort, buff, leng);
		}

		sg_void_t IUdpServer::run()
		{
			LOG_WRITE(NETWORK ,LOG_DEBUG, "udp thread start!");
			while(isActive)
			{
				char buff[1024] = {0};
				sg_string_t remoteIp;
				sg_int32_t  remodtPort;
				int len = _pSocket->recvUdpMsg(remoteIp, remodtPort, buff, sizeof(buff));
				if(len > 0)
				{
					LOG_WRITE(NETWORK ,LOG_DEBUG, "recv udp msg from ip:%s port:%d",remoteIp.c_str(),remodtPort);
					readyRead(remoteIp, remodtPort, buff, len);
				}
			}
		}
	}
}
