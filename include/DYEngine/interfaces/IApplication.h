#pragma once

#include <DYEngine\Core.h>
#include <DYEngine\Time.h>

#include <iostream>

namespace DYE
{
	class Core;

	//====================================================================================
	//	IApp: user interface for game engine
	//====================================================================================
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
	public:
		virtual void Run();								// init -> gameLoop(createScene -> Core->Init) -> release

	private:
		void init();
		void gameLoop();					// main game loop
		void release();

	protected:
		virtual void setupScenes() = 0;		// setup scene, need to implement

		//==========================================
		//	method
		//==========================================
		template <typename TApp>
		IScene* createScene(void (TApp::*buildFunc)(IScene*))
		{
			return m_pCore->m_pSceneManager->createScene(buildFunc);
		}

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

	//====================================================================================
	//	BaseApp: example application
	//====================================================================================
	class BaseApplication : public IApplication
	{
	public:
		BaseApplication() {}
		~BaseApplication() {}

	private:
		// user define function
		IScene* m_pTutScene;
		IScene* m_pTestScene0;
		IScene* m_pTestScene1;

		virtual void setupScenes();

		void buildTutScene(IScene* scene);

		void buildTestScene0(IScene* scene);

		void buildTestScene1(IScene* scene);
	};
}