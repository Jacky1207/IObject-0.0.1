#ifndef __DLMS_AES_H
#define __DLMS_AES_H

#include "typedef.h"
/* Includes ------------------------------------------------------------------*/

/* Public  defines -----------------------------------------------------------*/
// 默认支持AES-GCM-128报文加密模式
#define CRYPT_OK            (0)                 // Result OK
#define CRYPT_ERROR         (1)                 // Generic Error
#define GCM_MODE_IV         (0)                 // state-machine-IV
#define GCM_MODE_AAD        (1)                 // state-machine-AAD
#define GCM_MODE_TEXT       (2)                 // state-machine-TEXT
#define GCM_ENCRYPT         (0)                 // GCM报文加密模式
#define GCM_DECRYPT         (1)                 // GCM报文解密模式
#define STORE16H(x, y)       { (y)[0] = (sg_uint8_t)(((x)>>8)&255); (y)[1] = (sg_uint8_t)((x)&255); }

/* Private types defines -----------------------------------------------------------*/
typedef struct {
	sg_uint8_t         K[176];       // extend key
	sg_uint8_t         H[16],        // multiplier
	                   X[16],        // accumulator
	                   Y[16],        // counter
	                   Y_0[16],      // initial counter
	                   buf[16];      // buffer for stuff
	sg_int8_t          ivmode,       // Which mode is the IV in?
	                   mode,         // mode the GCM code is in
	                   buflen;       // length of data in buf
	sg_int8_t          empty;
	sg_int32_t         totlen;       // 64-bit counter used for IV and AAD
	sg_int32_t         pttotlen;     // 64-bit counter for the PT
} gcm_state;


/* AES -128-BIT Private  variables ------------------------------------------*/
#define Nk (4)          // 一个密钥的列数
#define Nc (4)          // state数组和扩展密钥的列数
#define Nr (10)         // 加密轮数

/* Public  functions ---------------------------------------------------------*/
void AES_Expandkey( sg_uint8_t *key, sg_uint8_t *expKey);
void AES_Encrypt( sg_uint8_t *in, sg_uint8_t *expKey, sg_uint8_t *out);
void AES_Decrypt( sg_uint8_t *in, sg_uint8_t *expKey, sg_uint8_t *out);
void gcm_packet(sg_uint8_t *key, sg_uint8_t keyLen, sg_uint8_t *dt, sg_int32_t dtLen, sg_uint8_t *iv,  sg_uint8_t ivLen, sg_uint8_t *aad, sg_int32_t aadLen, sg_uint8_t *tag, sg_uint8_t tagLen, sg_uint8_t dir);

void MixSubColumns(sg_uint8_t *state);
void InvMixSubColumns(sg_uint8_t *state);
#endif
