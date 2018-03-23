#include "ILogTerminal.h"
#include "IString.h"
#include <iostream>

namespace IObject
{
	namespace ISystemBase
	{
		ILogTerminal::ILogTerminal()
		{
		}

		ILogTerminal::~ILogTerminal()
		{
		}

		void ILogTerminal::outputLogInfo(const char* log, const int len, const LOG_LEVEL type)
		{
			IString tmp;
			switch (type)
			{
			case LOG_ERROR:
				tmp = BOLDRED;
				break;
			case LOG_WARNING:
				tmp = YELLOW;
				break;
			case LOG_INFO:
				tmp = BLUE;
				break;
			case LOG_DEBUG:
				tmp = GREEN;
				break;
			}
			ouputTerminal(log, tmp.data());
		}	

		void ILogTerminal::ouputTerminal(const char* log, const char* type)
		{
			std::cout << type << log << RESET << std::endl;
		}
	}
}

