#include "ILogFile.h"

namespace IObject
{
	namespace ISystemBase
	{
		#define		MAX_LOG_SIZE	(10*1024*1024)

		ILogFile::ILogFile() :
			isActive(true)
		{
			_pThread.start(this);
		}

		ILogFile::~ILogFile()
		{
			isActive = false;

			resetFileHandle();
		}

		void ILogFile::run()
		{
			while(isActive)
			{
				if(_strLogList.size() > 0)
				{
					IString str = getLogFromList();
					writeLogImpl(str.data(), str.length());
				}
				_pThread.msleep(100);
			}
		}

		void ILogFile::outputLogInfo(const char* log, const int len, const LOG_LEVEL type)
		{
			AutoLock lk(_pLock);
			IString str = IString(log);
			_strLogList.append(str);
		}
	
		IString ILogFile::getLogFromList()
		{
			AutoLock lk(_pLock);
			IString str;
			if (_strLogList.size() > 0)
			{
				str = _strLogList.first();
				_strLogList.remove(0);
			}

			return str;
		}

		IString ILogFile::getCurrentTime()
		{
			time_t timer = time(NULL);
			struct tm  *p = localtime(&timer);

			char buff[64] = { 0 };
			snprintf(buff,sizeof(buff)-1 , "%04d-%02d-%02d %02d.%02d.%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
			return IString(buff);
		}

		long ILogFile::getFileSize(const IString fileName)
		{
			unsigned long filesize = -1;
			struct stat statbuff;
			if (stat(fileName.data(), &statbuff) < 0)
				return filesize;
			else
				filesize = statbuff.st_size;
			return filesize;
		}

		void ILogFile::getCurrentLogHandle()
		{
			if (m_strFileName == "")
			{
				char buff[1024] = { 0 };
				snprintf(buff, sizeof(buff) ,"%s.txt", getCurrentTime().data());
				m_strFileName = m_strPath.append(buff);
			}

			_pFile = fopen((m_strFileName).data(), "a");
			if (_pFile == NULL)
			{
				perror("failed to open log file\n");
			}
		}

		void ILogFile::resetFileHandle()
		{
			if (_pFile != NULL)
			{
				fflush(_pFile);
				fclose(_pFile);
				_pFile = NULL;
			}
			m_strFileName = "";
		}

		void ILogFile::writeLogImpl(const char* strLog, int len)
		{
			if(strLog == NULL)
			{
				printf("file handle error *!\n");
				return;
			}

			getCurrentLogHandle();
			if (getFileSize(m_strFileName) + len >= MAX_LOG_SIZE)
			{
				printf("reset file handle\n");
				resetFileHandle();
				writeLogImpl(strLog, len);
			}

			if(_pFile == NULL)
			{
				printf("file handle error -!\n");
				return;
			}
			if (fwrite(strLog, sizeof(char), len, _pFile) != len)
			{
				perror("fwrite error");
			}
			fflush(_pFile);
			fclose(_pFile);
			_pFile = NULL;
		}
	}
}