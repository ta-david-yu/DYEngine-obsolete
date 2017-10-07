#pragma once

#include <DYEngine\Scene.h>
#include <DYEngine\utilities\Delegate.h>

#include <functional>
#include <memory>

#define CORE Core::GetInstance()

namespace DYE
{
	class IScene;
	class IApplication;
	class SceneManager;
	class SystemManager;

	//====================================================================================
	//	Core: core class for managing scenes and systems
	//====================================================================================
	class Core
	{
		friend class IApplication;
		friend class IScene;
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static Core* s_pInstance;
		IApplication* m_pApplication;

		//==========================================
		//	managers
		//==========================================
		SceneManager* m_pSceneManager;
		SystemManager* m_pSystemManager;

		//==========================================
		//	procedure
		//==========================================
		void init();

		//==========================================
		//	method
		//==========================================
	public:
		static Core* GetInstance();
		//==========================================
		//	constructor/destructor
		//==========================================
	private:
		Core(IApplication* app);
		~Core();
	};
}