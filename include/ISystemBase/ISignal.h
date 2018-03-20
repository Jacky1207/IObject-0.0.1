#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

namespace IObject
{
	namespace ISystemBase
	{
		#define MINEVENT(n)	(SIGRTMIN+n)
		#define MAXEVNET(n) (SIGRTMAX-n)
		#define MIN			15
		#define MAX			30
		#define EVENT(n)	(n < 16) ? (MINEVENT(n)) : (MAXEVNET(MAX-n))	
		
		typedef void(* SignalEventFun)(const int sig);
		class ISignal
		{
		public:
			ISignal();
			~ISignal();
			
			void init(int type);
			
			void attachKernelSignal(int fd_dev);
			void attachUserSignal();
			
			void registerSignalFun(SignalEventFun fun){ _signalFun = fun; }
		private: //members
			SignalEventFun _signalFun;
			int  _signalType;
		private: //funcions
		};
	}
}