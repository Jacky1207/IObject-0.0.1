#ifndef _LOG_CONFIGERATION_H_
#define _LOG_CONFIGERATION_H_

#include "Log.h"

namespace log{

class DateTime
{
public:
	static std::string getDateTimeInfo();
};

class File
{
public:
	static void createPath(const std::string &filepath);
	static bool isPathExist(const std::string &filepath);
	static int getFileSize(const std::string& filename);
	static FiLE *createFileHandle(const std::string& filename);
	static int writeMsgIntoFile(const std::string &logmsg, const FILE* stream);
	static int getFileLine(const std::string &filename, char* line);
};

class Configeration
{
public:
	Configeration();
	~Configeration();

	inline void setCurrentFileName(const std::string &filename){_file_name = filename;}
	inline void setCurrentFilePath(const std::string &filepath){_file_path = filepath;}
	
	inline void setConfigInfo(const log::Level levl, const std::string filepath){
		_log_level = level;
		_file_path = filepath;
	}
	/*
	 *	this class get configeration from config file
	 */
	class ConfigInformation
	{
	public:
		void getConfigerationInfo(const std::string &filename, Configeration *pConf);
	private:
		std::string _file_name;
		FILE *_file;
	};
private:
	std::string _file_name;
	std::string _file_path;
	log::Level  _log_level;
};

}

#endif