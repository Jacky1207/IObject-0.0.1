#include "ITcpServer.h"


namespace IObject
{
	namespace INetwork
	{
	 	ITcpServer *ITcpServer::_pServer = NULL;
		ITcpServer::ITcpServer() : 
				_isActive(true),
				_pSocket(NULL),
				_pConnection(NULL)
		{
			_pSocket = new ITcpSocket();
			_pThread.start(this);
		}
		
		ITcpServer::~ITcpServer()
		{
			_isActive = false;
			if(_pSocket != NULL)
			{
				_pSocket->disConnect();
				delete _pSocket;
				_pSocket = NULL;
			}

			#if 0
			std::list<IConnection *>::iterator it;
			for(it = m_pConnectionList.begin();it!=m_pConnectionList.end();it++){
         		delete *it;
     		}
			m_pConnectionList.clear();
			#endif
			if(_pConnection != NULL)
			{
				delete _pConnection;
				_pConnection = NULL;
			}
			
			ITcpServer::_pServer = NULL;
			
			LOG_WRITE(NETWORK, LOG_INFO, "~ITcpServer");
		}

		sg_int32_t ITcpServer::startTcpServer(const int port)
		{
			return	_pSocket->startTcpServer(port);
		}
		
		sg_void_t ITcpServer::run()
		{
			LOG_WRITE(NETWORK, LOG_DEBUG, "tcp server thread run");
			while(_isActive)
			{	
				std::string strClientIp;
				sg_int32_t nClientPort;
				sg_int32_t nSocket = _pSocket->acceptSocket(strClientIp,nClientPort);
				if(nSocket > 0 )
				{
					LOG_WRITE(NETWORK, LOG_DEBUG, "append socket(%d) to client list", nSocket);
					if(_pConnection == NULL)
					{
						_pConnection = new IConnection(_pSocket);
						if( _pConnection == NULL)
						{
							LOG_WRITE(NETWORK, LOG_ERROR, "tcp server create connection fail!");
							continue;
						}
						_pConnection->registerReadFun(&ITcpServer::readyReadFun);
//						_pConnection->registerDisconnectFun(&ITcpServer::disconnectFun);
					}

					remote_info info = {strClientIp, nClientPort, nSocket};
					_pConnection->setSocket(info);
					_pServer = this;

//					m_pConnectionList.push_back(p);
				}
			}
		}
		
		sg_int32_t ITcpServer::readyReadFun(sg_int32_t sock ,sg_char_t *buff,  sg_int32_t len)
		{
			_pServer->readyRead(sock, buff,  len);
		}

		sg_void_t ITcpServer::disconnectFun(const sg_int32_t sock)
		{
			AutoLock lk(_pServer->m_pLock);
			std::list<IConnection *>::iterator it;
			for(it = _pServer->m_pConnectionList.begin();it!=_pServer->m_pConnectionList.end();it++)
			{
				IConnection *p = (IConnection *)*it;
				if(sock)
				{
					_pServer->m_pConnectionList.erase(it);
					delete p;
					break;
				}
			}
		}

		sg_void_t ITcpServer::send(int sock ,const sg_char_t *buff, const sg_int32_t len)
		{			
			AutoLock lk(m_pLock);
			#if 0
			if(m_pConnectionList.size() == 0)
			{
				LOG_WRITE(NETWORK, LOG_ERROR, "connection is not ready!");
				return;
			}
			#endif
			#if 0
			LOG_WRITE(NETWORK, LOG_DEBUG, "tcp server client size=%d", m_pConnectionList.size());
			std::list<IConnection *>::iterator it;
			for(it = m_pConnectionList.begin();it!=m_pConnectionList.end();it++)
			{
				IConnection* p = (IConnection *)*it;
				LOG_WRITE(NETWORK, LOG_DEBUG, "tcp server send data to client[%d]", p->getSocket());
				_pConnection->sendData(buff, len);
			}
			#endif
			_pConnection->sendData(sock, buff, len);
		}

		sg_void_t ITcpServer::send(const sg_char_t *buff, const sg_int32_t len)
		{
			AutoLock lk(m_pLock);

			#if 0
			if(m_pConnectionList.size() == 0)
			{
				LOG_WRITE(NETWORK, LOG_ERROR, "connection is not ready!");
				return;
			}
			
			LOG_WRITE(NETWORK, LOG_DEBUG, "tcp server client size=%d", m_pConnectionList.size());
			std::list<IConnection *>::iterator it;
			for(it = m_pConnectionList.begin();it!=m_pConnectionList.end();it++)
			{
				IConnection *p = (IConnection *)*it;
				LOG_WRITE(NETWORK, LOG_DEBUG, "tcp server send data to client[%d]", p->getSocket());
				p->sendData(buff, len);
			}
			#endif
			_pConnection->sendData(buff, len);
		}

		sg_int32_t ITcpServer::getClientCount()
		{
			return _pConnection->getClientSize();
		}
	}
}
