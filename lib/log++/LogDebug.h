#ifndef _LOG_DEBUG_H_
#define _LOG_DEBUG_H_

#include "Log.h"

namespace log{

class LogDebug
{
public;
	LogDebug();
	virtual ~LogDebug();

	void format(std::string &msg, ...);
private:
	const log::Level m_level = log::Level::Debug;
	const std::string _type = "debug"; 
};

}

#endif