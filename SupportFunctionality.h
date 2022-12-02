// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


class RTS_API SupportFunctionality
{
public:
	SupportFunctionality();
	~SupportFunctionality();
	static const char* BoolToCStr(bool bool_value)
	{
		return (bool_value?"true":"false");
	}
};

template<typename TypeToLoad>
class Loader
{
public:
	Loader(const FString& SourcePath)
	{
		ConstructorHelpers::FObjectFinder<TypeToLoad> Finder(*SourcePath);
		if (Finder.Succeeded())
		{
			_DataPtr = Finder.Object;
		}
#ifdef AWallSpline_CHECK_SUCCESS_OF_LOAD_DATA
		LoggingSystem* LogPtr = LoggingSystem::Instance(LOG_FILE_PATH);
		std::string OutputString;
		OutputString += TCHAR_TO_ANSI(*SourcePath);
		OutputString+=" loading ";
		OutputString+=SupportFunctionality::BoolToCStr(Finder.Succeeded());
		OutputString+="\n";
		LogPtr->WriteToLog(OutputString);
#endif
	}
public:
	TypeToLoad* GetDataPtr()
	{
		return _DataPtr;
	}
private:
	TypeToLoad* _DataPtr;
};
