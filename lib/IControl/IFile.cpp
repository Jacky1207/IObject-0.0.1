#include "IFile.h"

#include <sys/stat.h>
#include <unistd.h>


namespace IObject
{
	namespace IControl
	{
		IFile::IFile() : 
			_strFileName("")
		{
		}

		IFile::~IFile()
		{
		}

		/*
		 *
		 */
		sg_int32_t IFile::open(const sg_string_t fileName, FileMode mode)
		{
			_strFileName = fileName;
			return open(fileName.c_str(), mode);
		}
		
		sg_int32_t IFile::open(const sg_char_t *fileName, FileMode mode)
		{
			_strFileName = sg_string_t(fileName);
			return openStream(fileName, mode);
		}
		
		sg_void_t IFile::close()
		{
			closeStream();
		}
		
		sg_int32_t IFile::write(const sg_char_t* buff, const sg_int32_t len)
		{
			return writeStream(buff, len);
		}
		
		sg_int32_t IFile::read(sg_char_t *buff, sg_int32_t len)
		{
			return readStream(buff, len);
		}
		
		sg_int32_t IFile::size()
		{
			return fileSizeStream(_strFileName.c_str());
		}
	}
}
