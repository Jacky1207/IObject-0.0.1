#ifndef _LOG_ERROR_H_
#define _LOG_ERROR_H_

#include "Log.h"

namespace log{

class LogError
{
public;
	LogError();
	virtual ~LogError();

	void format(const std::string &msg, ...);
private:
	const log::Level m_level = log::Level::Error;
	
};

}

#endif