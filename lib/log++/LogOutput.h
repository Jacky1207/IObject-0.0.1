#ifndef _LOG_OUTPUT_MODULE_H_
#define _LOG_OUTPUT_MODULE_H_

#include <list>

#include "Log.h"
#define PTHREAD_T

#ifdef PTHREAD_T
#include <pthread.h>
#endif

namespace log{

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

	std::list<std::string> _pList;
#ifdef PTHREAD_T
	pthread_t pthread_id;
#endif
};

}

#endif