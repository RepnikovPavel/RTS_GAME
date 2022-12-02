// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "string"
#include "CoreMinimal.h"


class RTS_API LoggingSystem
{
private:
	LoggingSystem(const char* EventLogPath);
	static LoggingSystem* _InstancePtr;
public:
	static LoggingSystem* Instance(const char* EventLogPath);
public:
	void WriteToLog(std::string SomeText) const;
public:
	~LoggingSystem();
private:
	std::string _EventLogPath;
};