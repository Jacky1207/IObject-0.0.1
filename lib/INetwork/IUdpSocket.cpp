#include "IUdpSocket.h"

namespace IObject
{
	namespace INetwork
	{
		IUdpSocket::IUdpSocket() :
				m_nSocket(-1)
		{
			initUdpSocket();
		}
		
		IUdpSocket::~IUdpSocket()
		{
			disConnect(m_nSocket);
			LOG_WRITE(NETWORK ,LOG_INFO, "~IUdpSocket");
		}
		
		sg_int32_t IUdpSocket::initUdpSocket()
		{
			m_nSocket = ISocket::initSocket(UdpSocket);
			if(m_nSocket < 0)
				LOG_WRITE(NETWORK ,LOG_ERROR, "init socket error: %d",ISocket::getSocketError());
				
			LOG_WRITE(NETWORK ,LOG_DEBUG, "init socket succes: %d",m_nSocket);
			return m_nSocket;
		}
		
		sg_int32_t IUdpSocket::startUdpServer(const sg_string_t serverIp, const sg_int32_t port)
		{
			ISocket::setLocalInfo(serverIp, port);
			int ret = ISocket::bindSocket();
			if(ret != 0)
				LOG_WRITE(NETWORK ,LOG_ERROR, "startUdpServer error: %d",ISocket::getSocketError());
				
			LOG_WRITE(NETWORK ,LOG_DEBUG, "startUdpServer succes!");

			return ret;
		}

		sg_void_t IUdpSocket::stopUdpServer()
		{
			ISocket::disConnect(m_nSocket);
		}

		
		sg_int32_t IUdpSocket::sendUdpMsg(const sg_string_t destIp,const sg_int32_t destPort, const sg_char_t* buff, const sg_int32_t leng)
		{
			LOG_WRITE(NETWORK ,LOG_DEBUG, "send udp msg to ip:%s port:%d",destIp.c_str(),destPort);
			return ISocket::sendMsgTo(buff, leng, destPort, destIp);
		}
		
		sg_int32_t IUdpSocket::recvUdpMsg(sg_string_t &destIp, sg_int32_t &destPort, sg_char_t *buff ,sg_int32_t leng)
		{
			return ISocket::readMsgfrom(buff, leng, destPort, destIp);
		}
	}
}
