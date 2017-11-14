#pragma once

#include <iostream>

#define LOG Logger::GetInstance()

namespace DYE
{
	class Logger
	{
	public:
		enum LogType
		{
			Info,
			Debug,
			Error,
			Warning,

			NumOfType
		};

	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static Logger* s_pInstance;

		FILE* m_pFile = nullptr;

		//==========================================
		//	method
		//==========================================
	public:
		static Logger* GetInstance();

		void SetOutputFile(FILE* file);

		void Print(LogType type, const char* file, int line, const char* msg, ...);
		void CustomPrint(const char* type, const char* file, int line, const char* msg, ...);

		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================

	};

#ifdef DEBUG

#define LogError( ... )															\
  do																			\
  {																				\
    LOG->Print(Logger::LogType::Error, __FILE__, __LINE__, __VA_ARGS__ );		\
  } while(false)							

#define LogDebug( ... )															\
  do																			\
  {																				\
    LOG->Print(Logger::LogType::Debug, __FILE__, __LINE__, __VA_ARGS__ );		\
  } while(false)							

#define LogInfo( ... )															\
  do																			\
  {																				\
    LOG->Print(Logger::LogType::Info, __FILE__, __LINE__, __VA_ARGS__ );		\
  } while(false)							

#define LogWarning( ... )														\
  do																			\
  {																				\
    LOG->Print(Logger::LogType::Warning, __FILE__, __LINE__, __VA_ARGS__ );		\
  } while(false)							

#define LogGL( ... )															\
  do																			\
  {																				\
    LOG->CustomPrint("OPENGL", __FILE__, __LINE__, __VA_ARGS__ );				\
  } while(false)

#else

#define LogError( ... )		__VA_ARGS__
#define LogDebug( ... )     __VA_ARGS__
#define LogInfo( ... )		__VA_ARGS__
#define LogWarning( ... )   __VA_ARGS__
#define Log( TYPE, ... )    __VA_ARGS__

#endif // DEBUG
}