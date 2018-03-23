#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h>    
#include <termios.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

namespace IObject
{
	namespace ISystemBase
	{
		#define KEY_VALUE	2017
		union semun
		{
			int val;
			struct semid_ds *buf;
			unsigned short int *array;
			struct seminfo *__buf;
		};
		
		class ISemaphore
		{
		public :
			ISemaphore();
			ISemaphore(const int key);
			~ISemaphore();

			void setKeyValue(const int key){_key = key;}
			
			void initSemaphore();
			void deleteSemaphore();
			int semaphore_v();
			int semaphore_p();
			int setSemvalue();

		private:
			int _semap;	
			int _key;
		};
	}
}
