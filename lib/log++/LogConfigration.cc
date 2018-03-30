#include "LogConfigeration.h"
#include <dir.h>
#include <sys/stat.h>
#include <uninstd.h>
#include <string.h>

namespace log{

std::string DateTime::getDateTimeInfo()
{
	time_t timer = time(NULL);
	struct tm  *p = localtime(&timer);

	char buff[64] = { 0 };
	snprintf(buff,sizeof(buff)-1 , "%04d-%02d-%02d %02d.%02d.%02d",		\
			p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	return std::string(buff);
}

bool File::createPath(const std::string &filepath)
{
	if(isPathExist(filepath))
		return true;

	int status = mkdir(filepath.c_str());
	if(status == -1)
		return false;

	return true;
}
bool File::isPathExist(const std::string &filepath)
{
	if(filepath.empty())
		return false;

	struct stat st;
	return (stat(filepath, &st) == 0);
}
int File::getFileSize(const std::string& filename)
{
	int filesize = -1;
	struct stat statbuff;
	if (stat(fileName.data(), &statbuff) < 0)
		return filesize;
	else
		filesize = statbuff.st_size;
	return filesize;
}
FiLE *File::createFileHandle(const std::string& filename)
{
	if(filename.empty())
		return NULL;
	FILE *file = fopen(filename.c_str*(), "a");
	if(file == NULL)
	{
		perror("open file %s failed\n", filename.c_str());
		return NULL;
	}
}
int File::writeMsgIntoFile(const std::string &logmsg, const FILE* stream)
{
	int size = logmsg.size();
	int ret = fwrite(logmsg.c_str(), 1, size, stream);
	if(ret < size)
		perror("write error!\n");

	return ret;
}

int File::getFileLine(const FILE* stream, char* line)
{
	return fgets(line, kmax_file_line, stream);
}

void Configeration::ConfigInformation::getConfigerationInfo(const std::string &filename, Configeration *pConf)
{
	_file = File::createFileHandle(filename);
	if(_file == NULL)	return;

	while(1)
	{
		char buff[kmax_file_line+1] = {0};
		int len = File::getFileLine(_file, buff);
		if(len < 0)
			break;

		char *type = strtok(buff, "=");
	}
}

}