#include "DYEngine/util/Logger.h"

#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdarg>
#include <direct.h>		// _mkdir

#define  LOG_BUFFER_SIZE 2048

namespace DYE
{
	Logger* Logger::s_pInstance = nullptr;

	Logger* Logger::GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Logger();
		}
		
		assert(s_pInstance != nullptr);
		return s_pInstance;
	}

	Logger::Logger() : m_FileStream()
	{
		_mkdir(LOG_DIR);
	}

	void Logger::SetOutputFile(std::string filename)
	{
		if (m_FileStream.is_open())
		{
			m_FileStream.close();
		}

		m_FileStream.open(LOG_DIR + filename);
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
		
		va_list args;
		va_start(args, msg);
		customPrint(LOG_TYPE[type], file, line, msg, args);
		va_end(args);
	}

	void Logger::CustomPrint(const char* type, const char* file, int line, const char* msg, ...)
	{
		va_list args;
		va_start(args, msg);
		customPrint(type, file, line, msg, args);
		va_end(args);
	}

	void Logger::customPrint(const char* type, const char* file, int line, const char* msg, va_list args)
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
			int length = vsnprintf(formattedMsg + offset, LOG_BUFFER_SIZE, msg, args);

			std::string formattedString = std::string(formattedMsg) + "\n";

			if (m_FileStream.is_open())
			{
				m_FileStream.write(formattedString.c_str(), formattedString.length());
			}

			fprintf(stderr, formattedMsg);
		}

		fprintf(stderr, "\n");
	}

	void Logger::ForceFlush()
	{
		if (m_FileStream.is_open())
			m_FileStream.flush();
	}
}