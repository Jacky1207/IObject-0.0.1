#ifndef _IAESENCRYPT_H_
#define _IAESENCRYPT_H_

#include "typedef.h"

namespace IObject
{
	namespace IControl
	{
		class IAesEncrypt
		{
		public:
			IAesEncrypt();
			~IAesEncrypt();

			void aesEncrypt(sg_uint8_t *plain, sg_uint8_t *key, sg_uint8_t *cipher);
			void aesDecrypt(sg_uint8_t *cipher, sg_uint8_t *key, sg_uint8_t *plain);
		};
	}
}

#endif