#include "IShared.h"
#include "ILog.h"

namespace IObject
{
	namespace ISystemBase
	{
		IShared::IShared() : 
			_key(KEY_VALUE)
		{
		}

		IShared::IShared(const int key) :
			_key(key)
		{
		}
		
		IShared::~IShared()
		{
			detachShared();
		}
		
		void IShared::initShared(const sg_uint32_t size)
		{			
			_share= shmget((key_t)_key, sizeof(size+4), 0666 | IPC_CREAT);
			if(_share < 0)
				fprintf(stderr, "shmget failed\n");
			
			attachShared();
			
			_semphore.initSemaphore();
		}
		
		void IShared::attachShared()
		{
			//将共享内存连接到当前进程的地址空间
			shm_addr = shmat(_share, 0, 0);
			if(shm_addr == (void*)-1)
			{
			   fprintf(stderr, "shmat failed\n");
			}
			
			shared = (_Shared *)shm_addr;
		}
		
		void IShared::detachShared()
		{
			shmdt(shared);
		}

		void IShared::pushData(const char* buff, const int leng)
		{
			_Shared sh;
			sh.shared_buff = new char[leng];
			memcpy(sh.shared_buff, buff, leng);
			sh.leng = leng;
			memcpy(shm_addr, (char*)&sh, leng+4);
//			memcpy(shared->shared_buff, buff, leng);
//			shared->leng = leng;
			//v option.means write compilt.

			_semphore.semaphore_v();
		}
		
		void IShared::readData(char *buff, int &leng)
		{
			if(_semphore.semaphore_p() == 0)
			{
				_Shared *sh = (_Shared *)shm_addr;
				memcpy(buff, sh->shared_buff, sh->leng);
				leng = sh->leng;
			}
		}
	}
}