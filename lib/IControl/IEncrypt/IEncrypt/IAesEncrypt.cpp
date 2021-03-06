#include "IAesEncrypt.h"

namespace IObject
{
	namespace IControl
	{
		#define ARRAY_NUM		4
		#define ARRAY_SIZE		16

		static const int Rcon[10] = {
			0x01000000, 0x02000000,
			0x04000000, 0x08000000,
			0x10000000, 0x20000000,
			0x40000000, 0x80000000,
			0x1b000000, 0x36000000};
		/**
		 * subBytes
		 */
		static const int Sbox[16][16] = {
			0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
			0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
			0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
			0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
			0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
			0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
			0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
			0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
			0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
			0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
			0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
			0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
			0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
			0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
			0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
			0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

		/**
		 * deSubBytes
		 */
		static const int InvSbox[16][16] = {
			0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
			0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
			0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
			0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
			0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
			0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
			0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
			0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
			0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
			0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
			0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
			0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
			0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
			0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
			0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
			0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

		IAesEncrypt::IAesEncrypt()
		{
		}

		IAesEncrypt::~IAesEncrypt()
		{
		}

		void IAesEncrypt::getValueFromSBox(int index)
		{
			return Sbox[high4Bit(index)][low4Bit(index)];
		}

		void IAesEncrypt::getValueFromInvSBox(int index)
		{
			return InvSbox[high4Bit(index)][low4Bit(index)];
		}

		void IAesEncrypt::leftLoop(sg_int32_t *array, int step)
		{
			sg_int32_t tmp[4];
			memcpy(tmp, array, sizeof(tmp));

			int index = step % 4;
			for(int i=0; i< 4;i++)
			{
				int pos;
				if(i+index > 3)
					pos = i+index - 4;
				else
					pos = i+index;
				array[i] = tmp[pos];
			}
		}

		void IAesEncrypt::rightLoop(sg_int32_t *array, int step)
		{
			sg_int32_t tmp[4];
			memcpy(tmp, array, sizeof(tmp));

			int index = step % 4;
			for(i=3; i>=0;i--)
			{
				int pos;
				if(i-index < 0)
					pos = 4 + (i-index);
				else
					pos = i-index;
				array[i] = tmp[pos];
			}
		}

		sg_int32_t IAesEncrypt::getWordFromStr(const sg_uint8_t *str)
		{
			sg_int32_t one,two,three,four;
			one	  = getIntFromChar(str[0]);
			two   = getIntFromChar(str[1]);
			three = getIntFromChar(str[2]);
			four  = getIntFromChar(str[3]);

			return (one << 24) | (two << 16) | (three << 8) | four;
		}

		sg_int32_t IAesEncrypt::getWordFromArray(const sg_int32_t *array)
		{
			return ((array[0] << 24) | (array[1] << 16) | (array[2] << 8) | array[3]) & 0xffffffff;
		}

		sg_int32_t IAesEncrypt::keyExpandT(int num, int round)
		{
			int array[4];
			slitIntToArray(nu, array);
			leftLoop(array, 1);

			//
			for(int i=0; i<4; i++)
			{
				array[i] = getValueFromSBox(array[i]);
			}

			int result = getWordFromArray(array);
			return result ^ Rcon[round];
		}

		sg_int32_t IAesEncrypt::expandKey(const uint8_t *key)
		{
			/**
			 *	extend key
			 *	char key[4][4] ---> int extend[44]
			 *	{ a, e, i, m, 
			 *    b, f, j, n, 
			 *	  c, g, k, o,
			 *	  d, h, l, p}
			 *
			 *	extend[0] = (key[0][0] << 24) | (key[1][0] << 16) | (key[2][0] << 8) | key[3][0]
			 *			  = abcd;
			 *	extend[1] = efgh; extend[2] = ijkl; extend[3] = mnop;
			 */
			for(int i = 0; i < 4; i++)
				m_pExtendKey[i] = getWordFromStr(key + i * 4);

			/**
			 *	extend[4*i]	  = extend[4*i - 4] ^ T(extend[4*i -1], j);
			 *	extend[4*i+1] = extend[4*i+1 -4] ^ extend[4*i]; 
			 *	extend[4*i+2] = extend[4*i+2 -4] ^ extend[4*i+1];
			 *	extend[4*i+3] = extend[4*i+3 -4] ^ extend[4*i+2];
			 */
			for(int i = 4, j = 0; i < 44; i++) 
			{
				if( i % 4 == 0)
				{
					m_pExtendKey[i] = m_pExtendKey[i - 4] ^ keyExpandT(m_pExtendKey[i - 1], j);
					j++;//next
				}
				else
				{
					m_pExtendKey[i] = m_pExtendKey[i - 4] ^ m_pExtendKey[i - 1];
				}
			}
		}
		
		//SubBytes
		sg_int32_t IAesEncrypt::subBytes(sg_int32_t *array)
		{
			for(int i=0;i<ARRAY_NUM;i++)
			{
				array[i] = getValueFromSBox(array[i]);
			}
		}

		sg_int32_t IAesEncrypt::deSubBytes(sg_int32_t *array)
		{
			for(int i=0;i<ARRAY_NUM;i++)
			{
				array[i] = getValueFromInvSBox(array[i]);
			}
		}

		//ShiftRow
		sg_int32_t IAesEncrypt::shiftRow(sg_int32_t *array)
		{
			// row[0] << 0, row[1]<<1,row[2]<<2,row[3]<<3
			int row1[4] = {0}, row2[4] = {0}, row[4] = {0};
			memcpy(row1, array+4, ARRAY_NUM);
			memcpy(row2, array+8, ARRAY_NUM);
			memcpy(row3, array+12, ARRAY_NUM);

			leftLoop(row1, 1);
			leftLoop(row2, 2);
			leftLoop(row3, 3);
				
			//copy back to array
			memcpy(array+4, row1, ARRAY_NUM);
			memcpy(array+8, row2, ARRAY_NUM);
			memcpy(array+12, row3, ARRAY_NUM);
		
			return 0;
		}

		sg_int32_t IAesEncrypt::deShiftRow(sg_int32_t *array)
		{
			// row[0]>>0, row[1]>>1,row[2]>>2,row[3]>>3
			int row1[4] = {0}, row2[4] = {0}, row[4] = {0};
			memcpy(row1, array+4, ARRAY_NUM);
			memcpy(row2, array+8, ARRAY_NUM);
			memcpy(row3, array+12, ARRAY_NUM);

			rightLoop(row1, 1);
			rightLoop(row2, 2);
			rightLoop(row3, 3);
				
			//copy back to array
			memcpy(array+4, row1, ARRAY_NUM);
			memcpy(array+8, row2, ARRAY_NUM);
			memcpy(array+12, row3, ARRAY_NUM);
		
			return 0;
		}

		//mix column
		static const int colM[4][4] = {
			2, 3, 1, 1,
			1, 2, 3, 1,
			1, 1, 2, 3,
			3, 1, 1, 2 };
		
		inline sg_int32_t IAesEncrypt::GFMul2(int gf)
		{
			/*
			 *	GF(2^8) 2^8 mean the max of value is 256
			 *	so we need to check the highest bit is over 256 
			 *	if the num is large the 256, it needs to ^ 0x1b��
			 */

			// gf*2 == gf << 1
			int result = gf << 1;
			int a7 = result & 0x00000100;

			if(a7 != 0)
			{
				result = result & 0x000000ff;
				result = result ^ 0x1b;
			}

			return result;
		}

		inline sg_int32_t IAesEncrypt::GFMul3(int gf)
		{
			return GFMul2(gf) ^ gf;
		}
		inline sg_int32_t IAesEncrypt::GFMul4(int gf)
		{
			return GFMul2(GFMul2(gf));
		}
		inline sg_int32_t IAesEncrypt::GFMul8(int gf)
		{
			return GFMul2(GFMul4(gf))
		}
		inline sg_int32_t IAesEncrypt::GFMul9(int gf)
		{
			return GFMul8(gf) ^ gf;
		}
		inline sg_int32_t IAesEncrypt::GFMul11(int gf)
		{
			return GFMul9(gf) ^ GFMul2(gf);
		}
		inline sg_int32_t IAesEncrypt::GFMul12(int gf)
		{
			return GFMul8(gf) ^ GFMul4(gf);
		}
		inline sg_int32_t IAesEncrypt::GFMul13(int gf)
		{
			return GFMul12(gf) ^ gf;
		}
		inline sg_int32_t IAesEncrypt::GFMul14(int gf)
		{
			return GFMul12(gf) ^ GFMul2(gf);
		}

		inline sg_int32_t IAesEncrypt::GFMul(int n, int gf)
		{
			int result;
			if(n == 1)
				result = gf;
			else if(n == 2)
				result = GFMul2(gf);
			else if(n == 3)
				result = GFMul3(gf);
			else if(n == 0x9)
				result = GFMul9(gf);
			else if(n == 0xb)//11
				result = GFMul11(gf);
			else if(n == 0xd)//13
				result = GFMul13(gf);
			else if(n == 0xe)//14
				result = GFMul14(gf);

			return result;
		}

		sg_int32_t IAesEncrypt::mixColumn(sg_int32_t *array)
		{
			int tmp[4][4] = {0};
			for(int i=0;i<4;i++)
				memcpy(tmp[i], array+i*4, ARRAY_NUM);

			for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
					array[i*4+j] = GFMul(colM[i][0], tmp[0][j]) ^ GFMul(colM[i][1], tmp[1][j]) ^
								   GFMul(colM[i][2], tmp[2][j]) ^ GFMul(colM[i][3], tmp[3][j]);
			}
		}

		//demix column
		static const int deColM[4][4] = {
			0xe, 0xb, 0xd, 0x9,
			0x9, 0xe, 0xb, 0xd,
			0xd, 0x9, 0xe, 0xb,
			0xb, 0xd, 0x9, 0xe };

		sg_int32_t IAesEncrypt::deMixColumn(sg_int32_t *array)
		{
			int tmp[4][4] = {0};
			for(int i=0;i<4;i++)
				memcpy(tmp[i], array+i*4, ARRAY_NUM);

			for(int i=0;i<4;i++)
			{
				for(int j=0;j<4;j++)
					array[i*4+j] = GFMul(deColM[i][0], tmp[0][j]) ^ GFMul(deColM[i][1], tmp[1][j]) ^
								   GFMul(deColM[i][2], tmp[2][j]) ^ GFMul(deColM[i][3], tmp[3][j]);
			}
		}

		//add round key
		sg_int32_t addRoundKey(sg_int32_t *array, sg_int32_t round)
		{
			for(int i=0;i<ARRAY_NUM;i++)
				array[i] = array[i] ^ key[i];
		}
		sg_int32_t deAddRoundKey(sg_int32_t *array, sg_int32_t *key);
			for(int i=0;i<ARRAY_SIZE;i++)
				array[i] = array[i] ^ key[i];
	}
}
