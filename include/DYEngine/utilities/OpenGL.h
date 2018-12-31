#pragma once

#include <DYEngine/utilities/Logger.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace DYE
{
	std::string glGetErrorMessage();
	bool glCheckError(const char* functionName);
}

#ifdef DEBUG

// glGetError to clear previous buffered error
#define glCall(glFunction)						\
	do											\
	{                                           \
		glGetError();							\
		glFunction;								\
		if(glCheckError(#glFunction))			\
			LogGL(glGetErrorMessage().c_str());	\
	} while (false)

#define glCheckAfterCall(glFunction)			\
	do											\
	{                                           \
		if(glCheckError(#glFunction))			\
			LogGL(glGetErrorMessage().c_str());	\
	} while (false)
	

#else

#define glCheckCall(glFunction) glFunction
#define glCheckAfterCall(glFunction)

#endif // DEBUG