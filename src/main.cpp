#include "ITcpClient.h"
#include "ITcpServer.h"
#include "IUdpServer.h"
#include "typedef.h"
#include "ILog.h"
#include "IList.h"
#include "IString.h"
#include <stdio.h>

struct tcpMsg
{
	char	req_type[5];		//request type get/post
#define 		DCU			1
#define 		METER		2
#define 		VPN			3
#define 		NTP			4
#define 		SNMP		5
#define 		DHCP		6
#define 		COMM		7
#define 		ADVANCE		8
	char 	msg_type[2];			//msg type 
	unsigned int 	msg_length;			//length of msg
	
	/**
	 *	msg format
	 * name:value&...
	 */
	char 	*msg_value;			//data of msg
};


using namespace IObject::INetwork;
using namespace IObject::ISystemBase;
class TcpClient : public ITcpClient
{
public :
	TcpClient();
	~TcpClient();
	
	int readyRead(char *buff, int len);
};

TcpClient::TcpClient()
{
}
TcpClient::~TcpClient()
{
}

int TcpClient::readyRead(char *buff, int len)
{
	printf("recv %d: %s\n", len, buff);
	tcpMsg *msg = (tcpMsg*)buff;
	for(int i=0;i<len;i++)
		printf("buf[%d] = 0x%x %c\n", i,buff[i], buff[i]);
	
	printf("%s %s %d\n", msg->req_type, msg->msg_type, msg->msg_length);
}

class TcpServer : public ITcpServer
{
public:
	TcpServer();
	~TcpServer();
	
	int readyRead(int sock, char *buff, int len);
private:
	
};

TcpServer::TcpServer()
{
}

TcpServer::~TcpServer()
{
}

class UdpClient : public IUdpServer
{
public:
	UdpClient();
	~UdpClient();
	
	int readyRead(std::string &destIp, sg_int32_t &destPort, sg_char_t *buff ,sg_int32_t leng);
};

UdpClient::UdpClient()
{}

UdpClient::~UdpClient()
{}

int UdpClient::readyRead(std::string &destIp, sg_int32_t &destPort, sg_char_t *buff ,sg_int32_t leng)
{
	LOG_WRITE("UdpClient", LOG_DEBUG, "recv from %s:%d, [%d:%s]\n", destIp.c_str(), destPort, leng, buff);
	return 0;
}
//TcpServer tcp;
int TcpServer::readyRead(int sock, char *buff, int len)
{
	printf("recv %s\n", buff);
	LOG_WRITE("TcpServer", LOG_DEBUG, "recv %d: %d[%s]", sock, len, buff);
#if 1
	struct tcpMsg *msg = (struct tcpMsg *)buff;
	if(strstr(msg->req_type, "GET")!= NULL)
	{
		char data[] = "vpn_server_ip: 120.234.18.2&vpn_subnet: 192.125.155.1/24&vpn_pre_shared: star&";
		msg->msg_length = strlen(data);
		memcpy(msg->msg_value, data, strlen(data));
		
		
//		tcp.send(buff, len+msg->msg_length+4);
	}
#endif
}

int main(int argc,char *argv[])
{
#if 0	//tcp client
	IList<IString > pList;
	pList.append("IIIII");
	pList.append("OOOOO");
	pList.append("VVVVV");
	pList.append("EEEEE");
	
	printf("size %d\n", pList.size());
#endif
	printf("1------\n");
	TcpClient tcp;
	printf("2------\n");
	tcp.connectTcpServer("192.125.155.117",55555);

	char buff[24] = {0};
	int index = 0;
	memcpy(buff, "GET", strlen("GET"));
	index += 5;
	memcpy(buff+index, "0", 2);
	index += 2;
	tcp.send(buff, index);
	while(1);
//	{
//		tcp.send("this is tcp client!",strlen("this is tcp client!"));
//		sleep(3);
//	}

#define SERVER_PORT			55555
#if 0	//tcp server
	printf("1---------------\n");
	TcpServer tcp;
	tcp.startTcpServer(SERVER_PORT);
	printf("2---------------\n");
	while(1)
	{
		sleep(5);
		if(tcp.getClientCount() > 0)
			tcp.send("this is tcp server!\n",strlen("this is tcp server!\n"));
	}
#endif

#if 0
	TcpClient tcp;
	tcp.enableReconnection(3000);
	tcp.connectTcpServer("192.125.155.117", SERVER_PORT);
	while(1)
	{
		tcp.send("this is tcp client!\n",strlen("this is tcp client!\n"));
		sleep(1);
	}
	
#endif

#if 0  //udp server
#define UDP_PORT	43210
#define UDP_PORT1	43211
	UdpClient udp;
	udp.startUdpServer(UDP_PORT);
	
	UdpClient udp1;
	udp1.startUdpServer(UDP_PORT1);
	
	sg_string_t destIp = "192.125.155.117";
	sg_int32_t  destPort = 60000;
	while(1)
	{
		tcp.send("this is tcp server!\n",strlen("this is tcp server!\n"));
		udp.sendMsg(destIp, destPort,"this is udp server!",strlen("this is udp server!"));
		sleep(5);
	}
#endif
	return 0;
}
