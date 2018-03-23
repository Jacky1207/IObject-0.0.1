#pragma once

#include "typedef.h"
#include "ISemaphore.h"
/*
 *	IShared is a class for shared buff with programs
 *	usual use ISemaphore together
 *
 *	| 4 bytes |  ...  |
 *     leng      data
 */

namespace IObject
{
	namespace ISystemBase
	{
		typedef struct 
		{
			sg_uint32_t 	leng;			//length of user data.
			char   			*shared_buff;	//buffer of data.	
		}_Shared;
		
		
		class IShared
		{
		public :
			IShared();
			IShared(const int key);
			~IShared();
			
			void initShared(const sg_uint32_t size);
			void deleteShared();
			
			void attachShared();
			void detachShared();
			
			void pushData(const char* buff, const int leng);
			void readData(char *buff, int &leng);
			
			int  getDataLeng();
		private:
			int 	_share;				//shared buff handle
			void 	*shm_addr;			//addr of shared buff
			_Shared *shared;			//shm_addr
			int		_key;
			
			ISemaphore _semphore;
		};
	}
}