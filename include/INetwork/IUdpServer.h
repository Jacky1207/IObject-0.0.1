/*
 *		IUdpServer
 *	this class used for UDP connection. 
 *	you just need to inherit from this class, and achieve you own readyRead function.
 *	then you can get udp data from readyRead function.a
 */

#pragma once

#include "IRunable.h"
#include "IUdpSocket.h"
namespace IObject
{
	namespace INetwork
	{
		class IUdpServer : virtual public IRunable
		{
		public:
			IUdpServer();
			virtual ~IUdpServer();
			
			sg_void_t startUdpServer(const sg_int32_t port);
			sg_int32_t sendMsg(const sg_string_t destIp,const sg_int32_t destPort, const sg_char_t* buff, const sg_int32_t leng);
			sg_void_t run();

			virtual sg_int32_t readyRead(sg_string_t &destIp, sg_int32_t &destPort, sg_char_t *buff ,sg_int32_t leng) = 0;
		private:
			IThread _pThread;
			bool  isActive;
			IUdpSocket *_pSocket;
		};
	}
}