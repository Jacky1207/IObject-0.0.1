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
	LogInformation p(level, msg);
	_pList.push_back(p);
}

void *LogModule::log_dispose_thread(void *param)
{
	LogModule *pLog = (LogModule* )param;
	while(_is_thread_active)
	{
		usleep(_thread_sleep_time);
		if(_pList.size() > 0)
		{
			LogInformation plog = _pList.front();
			_pList.pop_front();

			_ptr_configeration.getInformation();
			log::Level level = _ptr_configeration.getConfigLevel();
			log::Output out  = _ptr_configeration.getConfigOutput();

			if((CastEnum::castToInt(level) < CastEnum::castToInt(plog.getLogLevel))
				continue;
			if(CastEnum::castToInt(out) & CastEnum::castToInt(log::Output::OutputFile) != 0)
			{
				LogFile log;
				log.writeMsgToFile(level, );
			}
			if(CastEnum::castToInt(out) & CastEnum::castToInt(log::Output::OutputTerminal) != 0)
			{
				LogTerminal log;
				log.writeMsgToFile();
			}
			if(CastEnum::castToInt(out) & CastEnum::castToInt(log::Output::OutputTcpServer) != 0)
			{
				LogTcpServer log;
				log.writeMsgToFile();
			}
			if(CastEnum::castToInt(out) & CastEnum::castToInt(log::Output::OutputHtml) != 0)
			{
				LogHtml log;
				log.writeMsgToFile();
			}
		}
	}
}
