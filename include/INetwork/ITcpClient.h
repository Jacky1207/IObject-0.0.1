/*******************************************************************
 *
 *		ITcpClient class
 *	this class used for a tcp client.
 *	when building a tcp client ,you need to achieve function readyRead.
 *  member function:
 *		readyRead()  		achieved by derived class
 * 	member var:
 *		m_pSocket:			tcp socket
 *
 *
 ******************************************************************/
#pragma once

#include "ITcpSocket.h"
#include "IConnection.h"
#include "ITimer.h"

namespace IObject
{
	namespace INetwork
	{
		class ITcpClient
		{
		public:
			ITcpClient();
			virtual ~ITcpClient();
			
			sg_int32_t connectTcpServer(const std::string serverIp, const sg_int32_t port);
			//function for send data.
			sg_int32_t send(const sg_char_t *buff, const sg_int32_t len);
			//virtual function for a tcp client.
			virtual sg_int32_t readyRead(sg_char_t *pData, sg_int32_t len) = 0;
			//enable reconnection mechanism
			sg_void_t enableReconnection(const sg_int32_t time);
			sg_void_t disableReconnection(){_isReconnect = false;}
			sg_bool_t isReconnectionEnabled(){return _isReconnect;}
		protected:
			
		private:
			//server info
			std::string	_strServerIp;
			sg_int32_t 	_nPort;
			//_pSocket is a tcp socket.
			ITcpSocket 		*_pSocket;
			//_pConnection is a tcp connection
			IConnection 	*_pConnection;
			//reconnection
			sg_bool_t		_isReconnect;
			sg_int32_t 		_nReconnectionTime;
			//timer for reconnection.
			ITimer 			*_pTimer;
			sg_void_t 		startReconnction();
			
			//this 
			static ITcpClient *_pClient;
			//timeout Function
			static sg_void_t onTimerout();
			//read
			static sg_int32_t readyReadFun(sg_int32_t sock,sg_char_t *pData, sg_int32_t len);
			/**
			 *	when a socket is closed by server,
			 *	the client will get success when send data to server.
			 *	and recv 0 bytes in recv thread.
			 *  so we need to close socket in this situation
			 */
			static sg_void_t disconnectFun(const sg_int32_t sock);
		};
	}
}
