#include "ITcpClient.h"

namespace IObject
{
	namespace INetwork
	{
		ITcpClient *ITcpClient::_pClient = NULL;
		ITcpClient::ITcpClient() : 
				_pSocket(NULL),
				_pConnection(NULL),
				_isReconnect(false),
				_pTimer(NULL)
		{
			_pSocket = new ITcpSocket();
		}
		
		ITcpClient::~ITcpClient()
		{
			if(_pSocket != NULL)
			{
				_pSocket->disConnect();
				delete _pSocket;
				_pSocket = NULL;
			}
			
			if(_pConnection != NULL)
			{
				delete _pConnection;
				_pConnection = NULL;
			}
			LOG_WRITE(NETWORK, LOG_INFO, "~ITcpClient");
		}
		
		sg_int32_t ITcpClient::connectTcpServer(const std::string serverIp, const sg_int32_t port)
		{
			//save server infor.
			_strServerIp = serverIp;
			_nPort = port;
			
			int ret = _pSocket->connectServer(serverIp, port);
			if(ret < 0)
			{
				LOG_WRITE(NETWORK, LOG_ERROR, "tcp client connecting fail!");
				return ret;
			}

			if(_pConnection == NULL)
			{
				_pConnection = new IConnection(_pSocket);
				_pConnection->registerReadFun(&ITcpClient::readyReadFun);
				_pConnection->registerDisconnectFun(&ITcpClient::disconnectFun);
				_pClient = this;
			}
			remote_info info = {serverIp, port, _pSocket->getSocketHandle()};
			_pConnection->setSocket(info);
			LOG_WRITE(NETWORK, LOG_DEBUG, "create client connection");
			return ret;
		}
		
		sg_int32_t ITcpClient::send(const sg_char_t *buff, const sg_int32_t len)
		{
			if(_pConnection == NULL)
			{
				LOG_WRITE(NETWORK, LOG_ERROR, "connection is not ready!");
				return -1;
			}
			_pConnection->sendData(buff,len);
		}
		
		sg_int32_t ITcpClient::readyReadFun(sg_int32_t sock, sg_char_t *pData,  sg_int32_t len)
		{
			_pClient->readyRead(pData,len);
		}

		sg_void_t ITcpClient::disconnectFun(const sg_int32_t sock)
		{
			/**
			 *	send data error.
			 *	check if reconnection enabled
			 */
			
			LOG_WRITE(NETWORK, LOG_DEBUG, "reconnection %d", _pClient->_isReconnect);
			if(_pClient->_isReconnect)
			{
				LOG_WRITE(NETWORK, LOG_DEBUG, "start reconnection.");
				_pClient->startReconnction();
			}
		}

		sg_void_t ITcpClient::enableReconnection(const sg_int32_t time)
		{
			_isReconnect = true;
			_nReconnectionTime = time;
		}

		sg_void_t ITcpClient::startReconnction()
		{
			//start timer.
			_pTimer = new ITimer();
			_pTimer->registerTimeoutFun(&ITcpClient::onTimerout);
			_pTimer->start(_nReconnectionTime);
			LOG_WRITE(NETWORK, LOG_DEBUG, "timer start!");
		}

		sg_void_t ITcpClient::onTimerout()
		{
			//reinit socket.
			_pClient->_pSocket->initTcpSocket();
			//connect
			int ret = _pClient->connectTcpServer(_pClient->_strServerIp, _pClient->_nPort);
			if(ret >= 0)
			{
				LOG_WRITE(NETWORK, LOG_DEBUG, "reconnection success");
				_pClient->_pTimer->stop();

				LOG_WRITE(NETWORK, LOG_DEBUG, "stop timer !");
				delete _pClient->_pTimer;
				_pClient->_pTimer = NULL;
			}
		}
	}
}
