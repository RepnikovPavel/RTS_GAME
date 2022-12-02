#include "LoggingSystem.h"
#include <fstream>
#include <chrono>
#include <time.h>

LoggingSystem::LoggingSystem(const char* EventLogPath)
{
	auto start_time = std::chrono::system_clock::now();
	std::time_t time_to_log_file = std::chrono::system_clock::to_time_t(start_time);
	std::ofstream _EventLog(EventLogPath,std::ios_base::trunc);
	char time_str[26];
	ctime_s(time_str,sizeof(time_str),&time_to_log_file);
	_EventLog << time_str << std::endl;
	_EventLog.close();
	_EventLogPath = EventLogPath;
}

LoggingSystem::~LoggingSystem()
{
	delete _InstancePtr;
}

LoggingSystem* LoggingSystem::Instance(const char* EventLogPath)
{
	if (!_InstancePtr)
	{
		_InstancePtr = new LoggingSystem(EventLogPath);
	}
	return _InstancePtr;
}

void LoggingSystem::WriteToLog(std::string SomeText) const
{
	std::ofstream _EventLog(_EventLogPath, std::ios_base::app);
	_EventLog<<SomeText;
	_EventLog.close();
}

LoggingSystem* LoggingSystem::_InstancePtr{nullptr};