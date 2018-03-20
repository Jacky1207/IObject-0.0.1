/*******************************************************************
 *
 *		ITcpServer class
 *	this class is used for a tcp server.
 *	it will start a thread for accept client.and put client into a list.
 *  in the connection list,every connection has its own thread for read and write.
 *  member function:
 *		
 * 	member var:
 *		m_pSocket:			tcp socket
 *
 *
 ******************************************************************/
#pragma once

#include "ITcpSocket.h"
#include "IConnection.h"
#include "IRunable.h"
#include "IThread.h"
#include "IList.h"
#include "IMutex.h"

namespace IObject
{
	namespace INetwork
	{
		using namespace ISystemBase;
		class ITcpServer : public IRunable
		{
		public:
			ITcpServer();
			virtual ~ITcpServer();
			sg_void_t run();
			
			//virtual function for a tcp server.
			virtual sg_int32_t readyRead(sg_int32_t sock, sg_char_t *buff, sg_int32_t len) = 0;
			sg_int32_t startTcpServer(const int port);

			sg_int32_t getClientCount();

			sg_void_t send(int sock ,const sg_char_t *buff, const sg_int32_t len);
			sg_void_t send(const sg_char_t *buff, const sg_int32_t len);
		private:
			static ITcpServer* _pServer;
			static sg_int32_t readyReadFun(sg_int32_t sock, sg_char_t *buff, sg_int32_t len);
			static sg_void_t disconnectFun(const sg_int32_t sock);
			
			ITcpSocket *_pSocket;

			std::list <IConnection *> m_pConnectionList;
			//_pConnection is a tcp connection
			IConnection 	*_pConnection;
			
			sg_bool_t _isActive;
			IThread _pThread;
			//lock
			IMutex m_pLock;

			typedef struct
			{
				sg_int32_t 	sock;
				sg_string_t ipaddr;
				sg_int32_t	port;
			}_ConnectInfo;
			IList <_ConnectInfo> m_pConnectInfoList;
		};
	}
}
	
