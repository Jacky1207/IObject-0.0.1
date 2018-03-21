#pragma once

#include <string>

typedef void sg_void_t;
typedef bool sg_bool_t;	
typedef char sg_int8_t;	
typedef char sg_char_t;
typedef unsigned char sg_uchar_t;
typedef unsigned char sg_uint8_t;	
typedef short sg_int16_t;
typedef int sg_int32_t;
typedef unsigned short sg_uint16_t; 
typedef unsigned int sg_uint32_t; 
typedef long sg_long_t;	
typedef unsigned long sg_ulong_t;  
typedef long long sg_longlong_t;
typedef	std::string sg_string_t;

#if defined(_WIN32) || defined(_WIN64)
#else
#endif

#define RUN_DECLSPEC_EXPORT __declspec(dllexport)
#define RUN_DECLSPEC_IMPORT __declspec(dllimport)

namespace IObject
{
#define NETWORK			"Network"
#define ITCP			"ITcp"
#define IUDP			"IUdp"
#define STREAM			"Stream"
#define IFILE			"File"
#define TFTP			"Tftp"
#define ILIST			"List"
#define ISELECT			"ISelect"
#define ISHARED			"Shared"
#define ISIGNAL			"Signal"
#define ITIMER			"Timer"
#define ITHREAD			"Thread"
#define ISERIAL			"Serial"

	enum CaseSensitivity
	{
		CaseInsensitive = 0,
		CaseSensitive = 1
	};
	
	
}

#define SEGBASE_API

