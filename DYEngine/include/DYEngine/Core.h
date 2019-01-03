#pragma once

#ifdef DYE_PLATFORM_WINDOWS
	#ifdef DYE_BUILD_DLL
		#define DYE_API __declspec(dllexport)
		#define DYE_TEMPLATE 
	#else
		#define DYE_API __declspec(dllimport)
		#define DYE_TEMPLATE extern
	#endif // DYE_BUILD_DLL
#else
	#error DYE only supports Windows
#endif // DYE_PLATFORM_WINDOWS


#pragma warning( disable:4251 )