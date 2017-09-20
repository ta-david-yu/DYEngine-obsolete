#pragma once

#include <DYEngine/Main.h>

namespace DYE
{
	class IApplication
	{
	public:
		IApplication();
		~IApplication();

		virtual void Run();

	protected:
		void init();
		void gameLoop();			// main game loop
		void release();

		virtual void createScene() = 0;		// setup scene

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