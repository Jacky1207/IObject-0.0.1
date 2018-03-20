/*******************************************************************
 *
 *		IConnection class
 *	this class is used for net connection.
 *	it will start a thread for recv net data.
 *	and function members for send net data.
 *
 *
 ******************************************************************/

#pragma once

#include <tr1/memory>
#include "ITcpSocket.h"
#include "ISocket.h"
#include "IRunable.h"
#include "IMutex.h"
#include "ISelect.h"
#include "IList.h"

namespace IObject
{
	namespace INetwork
	{
		#define SELECT
		
		using namespace ISystemBase;
		typedef sg_int32_t(* ProReadyReadFun)(sg_int32_t nSock ,sg_char_t *pData, sg_int32_t len);
		//client disconnect callback
		typedef sg_void_t(* DisConnectCallbackFun)(const sg_int32_t nSock);

		class IConnection : virtual public ISelect
		{
		public:
			IConnection(ISocket *pSocket);
			virtual ~IConnection();

			//set current socket of connection
			sg_void_t setSocket(sg_int32_t nSocket);
			sg_void_t setSocket(const remote_info nSocket);
			
			sg_void_t sendData(const sg_char_t *buff, const sg_int32_t len);
			sg_int32_t sendData(const sg_int32_t sock, const sg_char_t *buff, const sg_int32_t len);
			sg_int32_t sendData(const IString strIp, const sg_char_t *buff, const sg_int32_t len);
			
			sg_void_t disConnectSocket(const sg_int32_t sock);
			
			sg_void_t registerReadFun(ProReadyReadFun fun){ _readyReadFun = fun;}
			sg_void_t registerDisconnectFun(DisConnectCallbackFun fun){ _disconnectCallbackFun = fun;}

			void eventHandle(const sg_int32_t fd);

			sg_int32_t getClientSize(){return m_nSocketList.size();}

		private:
			sg_void_t closeConnect(const sg_int32_t sock);
		private:
			ProReadyReadFun _readyReadFun;

			DisConnectCallbackFun _disconnectCallbackFun;
			//
			ISocket *_pSocket;

			//socket of connection
			IList<remote_info> m_nSocketList;

			//enable heart beat
			sg_bool_t _isEnableHeartBeat;

			//mutex for socket
			IMutex m_pMutex;
		};
//		typedef std::tr1::shared_ptr< IConnection >	IConnectionPtr; 
	}
}
