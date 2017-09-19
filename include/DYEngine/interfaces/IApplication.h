#pragma once

#include <DYEngine/Main.h>

namespace DYE
{
	class IApplication
	{
	public:
		IApplication();
		~IApplication();

	private:

	};

	class BaseApplication : public IApplication
	{
	public:
		BaseApplication();
		~BaseApplication();

	private:

	};
}