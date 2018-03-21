#ifndef _IAESENCRYPT_H_
#define _IAESENCRYPT_H_

/*
 *	aes encrypt for 128bit
 *
 *
 *
 *
 */
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

			void aesEncrypt();
			void aesDecrypt();
		private://functions
			inline sg_int32_t getIntFromChar(sg_uint8_t c)
			{
				sg_int32_t result = (sg_int32_t)c;
				return result & 0x000000ff;
			}
			inline void slitIntToArray(int num, sg_int32_t *array)
			{
				for(int i=0;i<4;i++)
					array[i] = (num >> (32-(i+1)*8)) & 0x000000ff;
			}
			inline int high4Bit(int num)
			{
				return (num & 0x000000f0) >> 4;
			}
			inline int low4Bit(int num)
			{
				return num & 0x0000000f;
			}

			inline int GFMul(int n, int gf);
			inline int GFMul2(int gf);
			inline int GFMul3(int gf);
			inline int GFMul4(int gf);
			inline int GFMul8(int gf);
			inline int GFMul9(int gf);
			inline int GFMul11(int gf);
			inline int GFMul12(int gf);
			inline int GFMul13(int gf);
			inline int GFMul14(int gf);
		
			void getValueFromSBox(int index);
			void getValueFromInvSBox(int index);

			void leftLoop(sg_int32_t *array, int step);
			void rightLoop(sg_int32_t *array, int step);

			sg_int32_t keyExpandT(int num, int round);

			sg_int32_t getWordFromStr(const sg_uint8_t *str);
			sg_int32_t getWordFromArray(const sg_int32_t *array);
			sg_int32_t expandKey(const sg_uint8_t *key);
			/*
			 *	Encrypt
			 */
			sg_int32_t subBytes(sg_int32_t *array);
			sg_int32_t shiftRow(sg_int32_t *array);
			sg_int32_t mixColumn(sg_int32_t *array);
			sg_int32_t addRoundKey(sg_int32_t *array, sg_int32_t round);

			/*
			 *	Decrypt
			 */
			sg_int32_t deSubBytes(sg_int32_t *array);
			sg_int32_t deShiftRow(sg_int32_t *array);
			sg_int32_t deMixColumn(sg_int32_t *array);
			sg_int32_t deAddRoundKey(sg_int32_t *array, sg_int32_t *key);
		private://members
			sg_int32_t	m_pExtendKey[44];
			sg_uint8_t	m_pIV[12];
		};
	}
}

#endif