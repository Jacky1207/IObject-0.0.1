#ifndef _LOG_H_
#define _LOG_H_

namespace log{

enum class Level
{
	Global = 0x1,
	Debug  = 0x2,
	Info   = 0x4,
	Warning= 0x8,
	Error  = 0x10,
	Unknown = 0xff
};

/*
 *	enum for log output way.
 */
enum class Output
{
	OutputFile	   = 0x1,
	OutputTerminal = 0x2,
	OutputTcpServer= 0x4,
	OutputHtml	   = 0x8,
	Unknown		   = 0xff
};

/*
 *	cast enum to int
 */
template <typename T>
class CastEnum
{
public:
	static int castToInt(T t){ return static_cast<int>(t); }
};

#define LOG(level, msg, ...)	Log##level().format(msg, ...)
static const MAX_LOG_LEN = 2048;

class Log
{
public:
};

}

#endif