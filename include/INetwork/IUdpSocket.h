#pragma once

#include "ISocket.h"
#include "IConnection.h"
#include "IRunable.h"
#include "IThread.h"

namespace IObject
{
	namespace INetwork
	{
		class IUdpSocket : virtual public ISocket
		{
		public :
			IUdpSocket();
			virtual ~IUdpSocket();
			
			sg_int32_t initUdpSocket();
			sg_int32_t startUdpServer(const sg_string_t serverIp, const sg_int32_t port);
			sg_void_t stopUdpServer();
			
			sg_int32_t sendUdpMsg(const sg_string_t destIp,const sg_int32_t destPort, const sg_char_t* buff, const sg_int32_t leng);
			sg_int32_t recvUdpMsg(sg_string_t &destIp, sg_int32_t &destPort, sg_char_t *buff ,sg_int32_t leng);

		private:
			sg_int32_t m_nSocket;
		};
	}
}