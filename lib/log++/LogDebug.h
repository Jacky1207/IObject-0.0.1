#ifndef _LOG_DEBUG_H_
#define _LOG_DEBUG_H_

#include "Log.h"

namespace log{

class LogDebug
{
public;
	LogDebug(const log::Level &level, const std::string &msg, ...);
	virtual ~LogDebug();

private:
	log::level m_level;
	
};

}

#endif