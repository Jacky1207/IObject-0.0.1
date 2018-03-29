#include "LogOutput.h"
#include "LogFile.h"
#include "LogTerminal.h"

log::LogModule *LogModule::_plog_module = NULL;
LogModule::LogModule() : 
	_is_thread_active(true)
{
	pthread_create(&pthread_id, NULL, log_dispose_thread, (void *)this);
	if(pthread_id < 0)
		perror("create thread error!\n");
}

LogModule::~LogModule()
{
	_is_thread_active = false;
	pthread_join(pthread_id, NULL);
}

LogModule *LogModule::getInstance()
{
	if(_plog_module == NULL)
	{
		_plog_module = new LogModule();
	}
	return _plog_module;
}

void LogModule::appendLogMessage(const log::Level &level,const std::string &msg)
{
	_log_level = level;
	_pList.push_back(msg);
}

void *LogModule::log_dispose_thread(void *param)
{
	LogModule *pLog = (LogModule* )param;
	while(_is_thread_active)
	{
		switch(_log_level)
		{
			case log::Level::Debug:
				LogFile log;
				log.writeMsgToFile();
				break;
			case log::Level::Info:
				break;
			case log::Level::Error:
				break;
		}
		usleep(100 *1000 *1000);
	}
}
