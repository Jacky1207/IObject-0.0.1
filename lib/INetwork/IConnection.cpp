#include "IConnection.h"
#include "ILog.h"
#include "typedef.h"

namespace IObject
{
	namespace INetwork
	{
		IConnection::IConnection(ISocket *pSocket) : 
					_disconnectCallbackFun(NULL)
		{
			_pSocket = pSocket;
		}
		
		IConnection::~IConnection()
		{
			for(int i=0; i<m_nSocketList.size(); i++)
			{
				remote_info info = m_nSocketList.at(i);
				closeConnect(info.remote_sock);
			}
			m_nSocketList.clear();
			
			LOG_WRITE(NETWORK, LOG_INFO, "~IConnection");
		}

		sg_void_t IConnection::setSocket(const remote_info nSocket)
		{
			m_nSocketList.append(nSocket);
			ISelect::addEvent(nSocket.remote_sock);
		}
		
		/*
		 *	there are two way for reading data.
		 * 1. epoll such as select.
		 * 2. by own thread
		 */
		sg_void_t IConnection::eventHandle(const sg_int32_t fd)
		{
			LOG_WRITE(NETWORK, LOG_DEBUG, "read data come %d",fd);

			char buf[1024] = {0};
			int len = _pSocket->readMsg(fd,buf,1024);
			if(len > 0)
			{
				LOG_WRITE(NETWORK, LOG_DEBUG, "read data %s - %d",buf, len);
				_readyReadFun(fd,buf,len);
			}
			else if(len == 0)
			{
				/**
				 * when a tcp connect is closing.
				 * we recv a event in eventhandle.but read nothing.
				 * so we remove the conenction.
				 */
				LOG_WRITE(NETWORK, LOG_INFO, "connection %d disconnect", fd);
				disConnectSocket(fd);
				if(_disconnectCallbackFun != NULL)
					_disconnectCallbackFun(fd);
			}
		}

		sg_void_t IConnection::disConnectSocket(const sg_int32_t sock)
		{
			AutoLock lock(m_pMutex);
			for(int i=0; i<m_nSocketList.size(); i++)
			{
				remote_info info = m_nSocketList.at(i);
				if(info.remote_sock == sock)
				{
					m_nSocketList.remove(i);

					closeConnect(info.remote_sock);
				}
			}
		}

		sg_void_t IConnection::closeConnect(const sg_int32_t sock)
		{
			/**
			 *	removeEvent need in front of DisConnect function.
			 *	because when close a socket first,
			 *	epoll_ctl with EPOLL_CTL_DEL will fail like this:
			 *	
			 *	epool_ctl : Bad file descriptor
			 */
			ISelect::removeEvent(sock);
			_pSocket->disConnect(sock);
		}

		sg_void_t IConnection::sendData(const sg_char_t *buff, const sg_int32_t len)
		{
			AutoLock lock(m_pMutex);
			LOG_WRITE(NETWORK, LOG_DEBUG, "socket size = %d", m_nSocketList.size());
			
			for(int i=0; i<m_nSocketList.size(); i++)
			{
				remote_info info = m_nSocketList.at(i);
				int leng = _pSocket->sendMsg(info.remote_sock,	buff,  len);
				if(leng == 0)
					LOG_WRITE(NETWORK, LOG_ERROR, "send to %s failed!", info.remote_ip.data());
			}
		}

		sg_int32_t IConnection::sendData(const IString strIp, const sg_char_t *buff, const sg_int32_t len)
		{
			AutoLock lock(m_pMutex);
			for(int i=0; i<m_nSocketList.size(); i++)
			{
				remote_info info = m_nSocketList.at(i);
				if(strIp.compare(info.remote_ip) == true)
				{
					return _pSocket->sendMsg(info.remote_sock,	buff,  len);
				}
			}
		}
		
		sg_int32_t IConnection::sendData(const sg_int32_t sock,const sg_char_t *buff, const sg_int32_t len)
		{
			AutoLock lock(m_pMutex);
			return _pSocket->sendMsg(sock,  buff,  len);
		}
	}
}
