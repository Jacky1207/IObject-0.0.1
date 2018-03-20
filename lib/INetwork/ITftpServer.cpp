#include "ITftpServer.h"

namespace IObject
{
	namespace INetwork
	{
		ITftpServer *pTftpServer = NULL;
		ITftpServer::ITftpServer() : 
			isActive(true),
			_pFileHandle(NULL),
			_isLastPackeg(false)
		{
		}

		ITftpServer::~ITftpServer()
		{
		}

		sg_void_t ITftpServer::startTftpServer()
		{
			_pSocket = new IUdpSocket();
			_pSocket->startUdpServer("" ,TFTP_PORT);

			_pThread.start(this);
			LOG_WRITE(TFTP ,LOG_DEBUG, "tftp server start");
		}
		
		sg_void_t ITftpServer::stopTftpServer()
		{
			isActive = false;
			_pSocket->stopUdpServer();
			LOG_WRITE(TFTP ,LOG_DEBUG, "tftp server stop");
		}

		ITftpServer* ITftpServer::getInstance()
		{
			if(pTftpServer == NULL)
				pTftpServer = new ITftpServer();

			return pTftpServer;
		}

		sg_void_t ITftpServer::upload(const sg_char_t *buff, const sg_int32_t len)
		{
			if(len < TFTP_DEFAULT_SIZE)
				_isLastPackeg = true;

			_pFileHandle->write(buff, len);
			
			if(_isLastPackeg)
			{
				closeFileHandle();
			}
		}

		sg_void_t ITftpServer::download()
		{
			if(_isLastPackeg)
			{
				closeFileHandle();
				return;
			}
			char buff[520] = {0};

			Tftp_Date *data = (Tftp_Date *)buff;
			data->opcode = DATA;
			data->opcode = _packIndex + 1;
			int len = _pFileHandle->read(data->data, TFTP_DEFAULT_SIZE);
			if(len < TFTP_DEFAULT_SIZE)
				_isLastPackeg = true;

			sendPackeg( buff, len + 4);
		}

		sg_int32_t ITftpServer::getFileHandle(IControl::FileMode mode)
		{
			if(_pFileHandle == NULL)
			{
				_pFileHandle = new IControl::IFile();
				if(!_pFileHandle->open(_fileName, mode))
				{
					LOG_WRITE(TFTP ,LOG_ERROR, "faile to open file %s",_fileName.c_str());
					delete _pFileHandle;
					_pFileHandle = NULL;
					return -1;
				}
			}

			_packIndex = 0;
			_isLastPackeg = false;
			return 0;
		}

		sg_void_t ITftpServer::closeFileHandle()
		{
			_pFileHandle->close();
			delete _pFileHandle;
			_pFileHandle = NULL;
		}

		sg_void_t ITftpServer::oack()
		{
			int len = _pFileHandle->size();
			char buff[64] = {0};

			Tftp_Oack *oack = (Tftp_Oack *)buff;

			snprintf(oack->oack, sizeof(buff)-3, "tsize%c%d%c",'\0',len,'\0');

			sendPackeg(buff, sizeof(buff));
		}

		sg_void_t ITftpServer::ack(sg_int32_t index)
		{
			char buff[5] = {0};
			Tftp_Ack *ack = (Tftp_Ack *)buff;
			ack->opcode = ACK;
			ack->dataNum = index;

			sendPackeg(buff , sizeof(Tftp_Ack));
		}

		sg_int32_t ITftpServer::sendPackeg(const sg_char_t * buff,const sg_int32_t len)
		{
			return _pSocket->sendUdpMsg(_destIpaddr, TFTP_PORT, buff, len);
		}

		sg_string_t ITftpServer::getFileName(const sg_char_t *buff)
		{
			int len = strlen(buff);
			return _filePath + sg_string_t(buff,len);
		}
		
		sg_void_t ITftpServer::tftpMsg(const sg_char_t *buff, const sg_int32_t len)
		{
			Tftp_Requst *req = (Tftp_Requst *)buff;
			if(req->opcode == RRQ)
			{
				_fileName = getFileName(req->file);
				if(getFileHandle(IControl::READONLY))
				{
					LOG_WRITE(TFTP ,LOG_ERROR, "RRQ FILE ERROR");	
					return;
				}
				LOG_WRITE(TFTP ,LOG_DEBUG, "RRQ %s ",_fileName.c_str());		
				oack();
			}
			else if(req->opcode == WRQ)
			{
				_fileName = getFileName(req->file);
				if(getFileHandle(IControl::WRITEONLY))
				{
					LOG_WRITE(TFTP ,LOG_ERROR, "WRQ FILE ERROR");
					return;
				}
				LOG_WRITE(TFTP ,LOG_DEBUG, "WRQ %s ",_fileName.c_str());		
				oack();
			}
			else if(req->opcode == ACK)
			{
				Tftp_Ack* ack = (Tftp_Ack*)buff;
				LOG_WRITE(TFTP ,LOG_DEBUG, "ACK %d ",ack->dataNum);		
				//send data
				_packIndex = ack->dataNum;
				download();
			}
			else if(req->opcode == OACK)
			{
				Tftp_Oack* oack = (Tftp_Oack*)buff;
			}
			else if(req->opcode == DATA)
			{
				Tftp_Date* data = (Tftp_Date*)buff;
				_packIndex = data->dataNum;
				//save date
				upload(data->data, sizeof(buff) - 4);
				//send ack
				ack(_packIndex);
			}
		}

		sg_void_t ITftpServer::run()
		{
			LOG_WRITE(TFTP ,LOG_DEBUG, "tftp server thread start");
			while(isActive)
			{
				sg_int32_t port;
				sg_string_t strIp;
				char buff[2048];
				int leng = _pSocket->recvUdpMsg(strIp, port, buff, sizeof(buff));
				if(leng > 0 )
				{
					if(port == TFTP_PORT && _destIpaddr.empty())
					{
						_destIpaddr = strIp;
					}
					//if there arm more then one tftp requst. ignore other first
					if(_destIpaddr != strIp)
						continue;
					
					tftpMsg(buff, leng);
				}
			}
			LOG_WRITE(TFTP ,LOG_DEBUG, "tftp server thread stop");
		}
	}
}

