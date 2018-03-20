/*
 *	this class used for io stream. eg: files
 *
 *	
 *
 *
 *
 *
 */

#pragma once

#include "typedef.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>


namespace IObject
{
	namespace IControl
	{
		enum FileMode
		{
			READONLY,
			WRITEONLY,
			READWRITE
		};
		
		class IStream
		{
		public:
			IStream();
			virtual ~IStream();

			sg_int32_t openStream(const sg_char_t *stream, FileMode mode);
			sg_int32_t closeStream();
			sg_int32_t writeStream(const sg_char_t *stream, const sg_int32_t len);
			sg_int32_t readStream(sg_char_t *stream, sg_int32_t len);
			sg_int32_t fileSizeStream(const sg_char_t *file);
		private:
			FILE *_pFile;
		};
		
	}
}
