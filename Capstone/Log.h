#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <time.h>
#include "Tools.h"

class Log
{
public:
	static Log* instance();
	void writeToLog(std::string message);
private:
	Log();
	Log(Log const &) {};
	Log operator=(const Log &l) {};
	static Log* myLogInstance;
	std::string logFile;
};

#endif