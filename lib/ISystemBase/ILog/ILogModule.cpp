#include "ILogModule.h"
#include "ILogFile.h"
#include "ILogTerminal.h"

namespace IObject
{
	namespace ISystemBase
	{
		ILogModule::ILogModule()
		{
			printf("1************\n");
			ILogModule *p;
		#ifdef LOG_FILE
			p = new ILogFile();
			printf("2************\n");
			_pLogModule.append(p);
		#endif

		#ifdef LOG_TERMINAL
			p = new ILogTerminal();
			_pLogModule.append(p);
		#endif
		}
		ILogModule::~ILogModule()
		{
			if(_pLogModule.size() > 0)
				_pLogModule.clear();
		}

		void ILogModule::outputLog(const char* log, const int len, const LOG_LEVEL type)
		{
			for(int i=0; i<_pLogModule.size(); i++)
			{
				ILogModule *p = _pLogModule.at(i);
				p->outputLogInfo(log, len, type);
			}
		}
	}
}
