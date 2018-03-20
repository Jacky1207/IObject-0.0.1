/*
 *						  TFTP protocol
 *
 *			|RRQ|								|WRQ|
 *	server			client  	| 	server			client  		|
 *				   <-- RRQ 		|				   	<-- WRQ 		|
 *	oack-->						|	oack-->							|
 *				   <-- ACK 0	|					<-- data 1		|
 *	data 1-->					|	ACK 1-->						|
 *				   <-- ACK 1	|					<-- data 2		|
 *				.				|				.					|
 *				.				|				.					|
 *				.				|				.					|
 *	data n-->	   				|					<-- data n		|
 *				   <-- ACK n	V	ACK n-->						V
 */
#pragma once

#include "IUdpSocket.h"
#include "IRunable.h"
#include "IThread.h"
#include "IFile.h"

namespace IObject
{
	namespace INetwork
	{
		using namespace IControl;
		using namespace ISystemBase;
		
		class ITftpServer : virtual public IRunable
		{
		#define TFTP_PORT			69
		#define TFTP_DEFAULT_SIZE	512
		
			enum OPCODE
			{
				RRQ = 1,
				WRQ = 2,
				DATA= 3,
				ACK = 4,
				ERROR=5,
				OACK =6
			};

			typedef struct 
			{
				sg_int16_t 		opcode;
				sg_char_t 		*file;
			}Tftp_Requst;

			typedef struct 
			{
				sg_int16_t 		opcode;
				sg_char_t 		oack[0];
			}Tftp_Oack;

			typedef struct 
			{
				sg_int16_t 		opcode;
				sg_int16_t 		dataNum;
			}Tftp_Ack;

			typedef struct 
			{
				sg_int16_t 		opcode;
				sg_int16_t 		dataNum;
				sg_char_t 		data[0];
			}Tftp_Date;
			
		public:
			ITftpServer();
			virtual ~ITftpServer();

			sg_void_t startTftpServer();
			sg_void_t stopTftpServer();
			sg_void_t setTftpFilePath(sg_string_t strPath){_filePath = strPath;}

			sg_void_t sendRequst();

			static ITftpServer* getInstance();
		private://function
			sg_void_t run();
			sg_void_t tftpMsg(const sg_char_t *buff, const sg_int32_t len);
			sg_string_t getFileName(const sg_char_t *buff);
			sg_int32_t 	getFileHandle(IControl::FileMode mode);
			sg_void_t   closeFileHandle();

			sg_int32_t  sendPackeg(const sg_char_t *buff, const sg_int32_t len);

			sg_void_t upload(const sg_char_t *buff, const sg_int32_t len);
			sg_void_t download();
			sg_void_t oack();
			sg_void_t ack(sg_int32_t index);
		private: //member 
			IUdpSocket *_pSocket;
			IThread 	_pThread;
			sg_bool_t	isActive;

			//tftp client address
			sg_string_t _destIpaddr;
			//tftp file path
			sg_string_t _filePath;
			//tftp file name
			sg_string_t _fileName;

			//tftp packeg index
			sg_int32_t  _packIndex;
			//the last packeg
			sg_bool_t   _isLastPackeg;

			//file handle
			IFile *_pFileHandle;
		};
	}
}

