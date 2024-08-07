///////////////////////////////////////////////////////////////////////////////
//
// This file is part of sc4-disable-network-construction-sounds, a DLL Plugin
// for SimCity 4 that disables the sounds that are played during the network
// construction animation.
//
// Copyright (c) 2024 Nicholas Hayes
//
// This file is licensed under terms of the MIT License.
// See LICENSE.txt for more information.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <filesystem>
#include <fstream>

enum class LogLevel : int32_t
{
	Info = 0,
	Error = 1,
	Debug = 2,
	Trace = 3
};

class Logger
{
public:

	static Logger& GetInstance();

	void Init(std::filesystem::path logFilePath, LogLevel logLevel, bool includeTimeStamp = true);

	bool IsEnabled(LogLevel option) const;

	void WriteLogFileHeader(const char* const message);

	void WriteLine(LogLevel level, const char* const message);

	void WriteLineFormatted(LogLevel level, const char* const format, ...);

private:

	Logger();
	~Logger();

	void WriteLineCore(const char* const message);

	bool initialized;
	bool writeTimeStamp;
	LogLevel logLevel;
	std::ofstream logFile;
};

