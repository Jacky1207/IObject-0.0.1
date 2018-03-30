#include "LogDebug.h"
#include "LogConfigration.h"

void LogDebug::format(std::string &msg, ...)
{
	std::string time = log::DateTime::getDateTimeInfo();

	char buff[MAX_LOG_LEN];
	memset(buff, 0, MAX_LOG_LEN);
	va_list arg;

	va_start(arg, msg);
	vsprintf(buff, msg.c_str(), arg);
	va_end(arg);
	msg = time + _type + std::string(buff);
}