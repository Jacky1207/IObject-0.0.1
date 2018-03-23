#include "ISemaphore.h"

namespace IObject
{
	namespace ISystemBase
	{
		ISemaphore::ISemaphore() 
			: _semap(-1), _key(KEY_VALUE)
		{
			
		}

		ISemaphore::ISemaphore(const int key)
			: _semap(-1), _key(key)
		{
		}
		
		ISemaphore::~ISemaphore()
		{
		}
		
		void ISemaphore::initSemaphore()
		{
			_semap = semget((key_t)_key, 1, 0666 | IPC_CREAT);
			if(_semap < 0)
				fprintf(stderr, "Failed to semget semaphore\n");
			if(setSemvalue() != 0)
			{
				fprintf(stderr, "Failed to initialize semaphore\n");
			}

		}
		void ISemaphore::deleteSemaphore()
		{
			//delete semaphore
			union semun sem_union;  
		  
			if(semctl(_semap, 0, IPC_RMID, sem_union) == -1)  
				fprintf(stderr, "Failed to delete semaphore\n");  
		}
		
		//V option: +1(sv)
		int  ISemaphore::semaphore_v()
		{
			struct sembuf sem_b;  
			sem_b.sem_num = 0;  
			sem_b.sem_op = 1;//V()  
			sem_b.sem_flg = SEM_UNDO;  
			if(semop(_semap, &sem_b, 1) == -1)  
			{  
				fprintf(stderr, "semaphore_v failed\n");  
				return -1;  
			} 
			return 0;  
		}
		
		//P option:  -1(sv)
		int  ISemaphore::semaphore_p()
		{
			struct sembuf sem_b;  
			sem_b.sem_num = 0;  
			sem_b.sem_op = -1;//P()  
			sem_b.sem_flg = SEM_UNDO;  
			if(semop(_semap, &sem_b, 1) == -1)  
			{  
				int val = semctl(_semap, 0, GETVAL);
				if(val <= 0)
				{
					printf("------signal cant be use %d------\n",val);
				}
				perror("semaphore_p :");
				return -1;  
			}  
			return 0;  
		}

		//before P/V options, must set val first 
		int  ISemaphore::setSemvalue()
		{
			union semun sem_union;  
		  
			sem_union.val = 1;  
			if(semctl(_semap, 0, SETVAL, sem_union) == -1)  
				return -1;  
			return 0;  
		}
	}
}