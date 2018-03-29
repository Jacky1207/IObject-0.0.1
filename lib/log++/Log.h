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

#define LOG(level, )	Log##level().

class CreateLogHandle
{
public:
	static 
};

}

#endif