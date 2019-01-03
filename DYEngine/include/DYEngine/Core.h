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

#ifdef  DYE_ENABLE_ASSERT
	#define DYE_ASSERT(x, ...)																				\
	do																										\
	{																										\
		if (!(x)) { LogError("Assertion Failed: {0}", __VA_ARGS__); LOG->ForceFlush(); __debugbreak(); }	\
	} while(false)	
#else
	#define DYE_ASSERT(x, ...)
#endif //  DYE_ENABLE_ASSERT



#pragma warning( disable:4251 )