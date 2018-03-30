#ifndef _LOG_INFO_H_
#define _LOG_INFO_H_

#include "Log.h"

namespace log{

class LogInfo
{
public;
	LogInfo();
	virtual ~LogInfo();

	void format(const std::string &msg, ...);
private:
	const log::Level m_level = log::Level::Info;
	const std::string _type = "debug"; 
};

}

#endif