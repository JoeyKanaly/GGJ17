#include "Log.h"

Log* Log::myLogInstance = NULL;

Log::Log()
{
	std::string stringBuffer = getFormattedTime();
	logFile = "./logs/Log " + stringBuffer + ".txt";
}

Log * Log::instance()
{
	if (myLogInstance == nullptr)
		myLogInstance = new Log();
	return myLogInstance;
}

void Log::writeToLog(std::string message)
{
	std::string currentTime = getFormattedTime() + " : ";
	std::ofstream file(logFile.c_str(), std::ios::out | std::ios::app);
	if (file.is_open())
	{
		file.write(currentTime.c_str(), strlen(currentTime.c_str()));
		file.write(message.c_str(), strlen(message.c_str()));
		file.write("\n", strlen("\n"));
		file.close();
	}
}