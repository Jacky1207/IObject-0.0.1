#ifndef _ISERIAL_H_
#define _ISERIAL_H_

#include "IInterface.h"
#include "IList.h"

using namespace IObject::ISystembase;
namespace IObject
{
	namespace IControl
	{
		class ISerial
		{
		public:
			ISerial();
			virtual ~ISerial();
		
			enum BAUDRATE
			{
			}
			sg_int32_t open(const char* com);
			sg_int32_t open(const char* com, sg_uint32_t baud);
			sg_int32_t open(const IString com);
			sg_int32_t open(const IString com, sg_uint32_t baud);
			sg_int32_t close();

			sg_int32_t setBaudrate(sg_uint32_t baud);
			sg_int32_t write(const char* buff, int len);
			sg_int32_t read(char *buff, int len);

			virtual sg_int32_t readyRead(sg_int32_t comm, sg_char_t *buff, sg_int32_t len) = 0;
		private:
			static sg_int32_t readyReadFun(sg_int32_t comm, sg_char_t *buff, sg_int32_t len);

			int m_nSerial;
			
		};
	}
}


#endif
