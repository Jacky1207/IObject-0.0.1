#pragma once

#include "IStream.h"

namespace IObject
{
	namespace IControl
	{
		class IFile : public IStream
		{
		public:
			IFile();
			virtual ~IFile();

			sg_int32_t open(const sg_string_t fileName, FileMode mode);
			sg_int32_t open(const sg_char_t *fileName, FileMode mode);
			sg_void_t close();
			sg_int32_t write(const sg_char_t* buff, const sg_int32_t len);
			sg_int32_t read(sg_char_t *buff, sg_int32_t len);

			sg_int32_t size();
			
		private:
			sg_string_t _strFileName;
		};
	}
}
