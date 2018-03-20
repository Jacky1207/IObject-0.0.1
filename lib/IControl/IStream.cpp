#include "IStream.h"
#include "IRunable.h"
#include "ILog.h"

namespace IObject
{
	namespace IControl
	{
		using namespace ISystemBase;
		IStream::IStream()  :
			_pFile(NULL)
		{
		}

		IStream::~IStream()
		{
			if(_pFile != NULL)
			{
				fflush(_pFile);
				fclose(_pFile);
			}
		}

		sg_int32_t IStream::openStream(const sg_char_t *stream, FileMode mode)
		{

			sg_string_t fileMode;
			if(mode == READONLY)
			{
				fileMode = "r";
			}
			else if (mode == WRITEONLY)
			{
				fileMode = "w";
			}
			else if (mode == READWRITE)
			{
				fileMode = "w+";
			}

			_pFile = fopen(stream, fileMode.c_str());
			if(_pFile != NULL)
			{
				LOG_WRITE(STREAM, LOG_ERROR, "failed to open stream!");
				return -1;
			}

	
			LOG_WRITE(STREAM, LOG_DEBUG, "open stream \"%s\" success!",stream);
			return 0;
		}

		sg_int32_t IStream::closeStream()
		{
			fflush(_pFile);
			fclose(_pFile);

			_pFile = NULL;
		}

		sg_int32_t IStream::readStream(sg_char_t *stream, sg_int32_t len)
		{
			if(_pFile == NULL)
				return -1;

			return fread(stream, sizeof(sg_char_t), len, _pFile);
		}

		sg_int32_t IStream::writeStream(const sg_char_t *stream, const sg_int32_t len)
		{
			if(_pFile == NULL)
				return -1;

			return fwrite(stream, sizeof(sg_char_t), len, _pFile);
		}

		sg_int32_t IStream::fileSizeStream(const sg_char_t *file)
		{
			unsigned long filesize = -1;
			struct stat statbuff;
			if(stat(file, &statbuff) < 0)
			{
				return filesize;
			}
			else
			{
				filesize = statbuff.st_size;
			}
			return filesize;
		}
	}
}

