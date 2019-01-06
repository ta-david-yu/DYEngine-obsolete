#include "DYEngine/util/Logger.h"

#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdarg>

#define  LOG_BUFFER_SIZE 2048

namespace DYE
{
	Logger* Logger::s_pInstance = nullptr;

	Logger* Logger::GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Logger();
			s_pInstance->SetOutputFile(NULL);
		}
		
		assert(s_pInstance != nullptr);
		return s_pInstance;
	}

	void Logger::SetOutputFile(FILE* file)
	{
		m_pFile = file;
	}


	void Logger::Print(Logger::LogType type, const char* file, int line, const char* msg, ...)
	{
		const static char* LOG_TYPE[Logger::LogType::NumOfType] =
		{
			"INFO",
			"DEBUG",
			"ERROR",
			"WARNING"
		};
		

		char formattedMsg[LOG_BUFFER_SIZE];

		// Print out the file and line in visual studio format so the error can be
		// double clicked in the output window file(line) : error
		std::size_t nameSize = strlen(file);
		const char* fileSection = file;
		if (nameSize > 20)
			fileSection = file + strlen(file) - 20;

		int offset = std::sprintf(formattedMsg, "%-9s%-20s(%4d)    ", LOG_TYPE[type], fileSection, line);
		
		// print
		{
			va_list args;
			va_start(args, msg);
			vsnprintf(formattedMsg + offset, LOG_BUFFER_SIZE, msg, args);

			if (m_pFile != nullptr)
				vfprintf(m_pFile, formattedMsg, args);

			vfprintf(stderr, formattedMsg, args);
			va_end(args);
		}

		if (m_pFile != nullptr)
			fprintf(m_pFile, "\n");

		fprintf(stderr, "\n");
	}

	void Logger::CustomPrint(const char* type, const char* file, int line, const char* msg, ...)
	{
		char formattedMsg[LOG_BUFFER_SIZE];

		// Print out the file and line in visual studio format so the error can be
		// double clicked in the output window file(line) : error
		std::size_t nameSize = strlen(file);
		const char* fileSection = file;
		if (nameSize > 20)
			fileSection = file + strlen(file) - 20;

		int offset = std::sprintf(formattedMsg, "%-9s%-20s(%4d)    ", type, fileSection, line);

		// print
		{
			va_list args;
			va_start(args, msg);
			vsnprintf(formattedMsg + offset, LOG_BUFFER_SIZE, msg, args);

			if (m_pFile != nullptr)
				vfprintf(m_pFile, formattedMsg, args);

			vfprintf(stderr, formattedMsg, args);
			va_end(args);
		}

		if (m_pFile != nullptr)
			fprintf(m_pFile, "\n");

		fprintf(stderr, "\n");
	}

	void Logger::ForceFlush()
	{
		if (m_pFile != nullptr)
			fflush(m_pFile);
	}
}