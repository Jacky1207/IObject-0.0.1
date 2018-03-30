#ifndef _LOG_OUTPUT_MODULE_H_
#define _LOG_OUTPUT_MODULE_H_

#include <list>

#include "Log.h"
#include "LogConfigeration.h"
#define PTHREAD_T

#ifdef PTHREAD_T
#include <pthread.h>
#endif

namespace log{

class LogInformation
{
public:
	LogInformation(const log::Level level,const std::string msg) : 
			_level(level), _log_msg(msg){}
	~LogInformation();

	log::Level& getLogLevel() const { return _level; }
	std::string& getLogMsg() const { return _log_msg; }
private:
	log::Level	_level;
	std::string _log_msg;
};

class LogModule
{
public:
	LogModule();
	~LogModule();

	void appendLogMessage(const log::Level &level,const std::string &msg);
	static LogModule *getInstance();
private:
	static void *log_dispose_thread(void *param);

	static LogModule *_plog_module;
	bool _is_thread_active;
	log::Level _log_level;

	std::list<LogInformation > _pList;
	Configeration _ptr_configeration;
	const int  _thread_sleep_time = 150*1000*1000;
#ifdef PTHREAD_T
	pthread_t pthread_id;
#endif
};

}

#endif