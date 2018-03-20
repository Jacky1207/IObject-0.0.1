#pragma once

#include "ISocket.h"
#include "IString.h"

namespace IObject
{
	namespace INetwork
	{
		using namespace ISystemBase;
		typedef struct {
			std::string	remote_ip;		//remote ip
			sg_int32_t 	remote_port;
			sg_int32_t 	remote_sock;
		}remote_info;
	
		class ITcpSocket : virtual public ISocket
		{
		public:
			ITcpSocket();
			virtual ~ITcpSocket();
			
			sg_int32_t initTcpSocket();
			sg_int32_t startTcpServer(const int port);
			sg_int32_t startTcpClient();
			sg_int32_t connectServer(const sg_string_t serverIp, const sg_int32_t port);

			sg_int32_t getSocketHandle(){return m_nSocket;}
		private:
			sg_int32_t m_nSocket;
		};
	}
}