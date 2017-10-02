#pragma once

#include <DYEngine\Core.h>

namespace DYE
{
	class Core;

	class IApplication
	{
	public:
		//==========================================
		//	memeber/variable
		//==========================================
	protected:
		Core* m_pCore;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================
		virtual void Run();								// init -> gameLoop(createScene -> Core->Init) -> release

	protected:
		void init();
		void gameLoop();			// main game loop
		void release();

		virtual void createScene() = 0;		// setup scene
		//==========================================
		//	method
		//==========================================

		//==========================================
		//	getter
		//==========================================

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	public:
		IApplication();
		~IApplication();
	};

	class BaseApplication : public IApplication
	{
		// TO DO:
	public:
		BaseApplication() {}
		~BaseApplication() {}

	private:

	};
}