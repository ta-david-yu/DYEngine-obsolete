#pragma once

#include <DYEngine/Scene.h>
#include <DYEngine/System.h>
#include <DYEngine/utilities/Delegate.h>

#include <functional>
#include <memory>

#define GAME_CORE GameCore::GetInstance()
#define SYSTEM_MGR GAME_CORE->GetSystemManager()
#define SCENE_MGR GAME_CORE->GetSceneManager()

namespace DYE
{
	class IScene;
	class IApplication;
	class SceneManager;
	class SystemManager;

	//====================================================================================
	//	Core: core class for managing scenes and systems
	//====================================================================================
	class GameCore
	{
		friend class IApplication;
		friend class IScene;
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static GameCore* s_pInstance;
		IApplication* m_pApplication;

		//==========================================
		//	managers
		//==========================================
		SceneManager* m_pSceneManager;
		SystemManager* m_pSystemManager;

		//==========================================
		//	procedure
		//==========================================

		//==========================================
		//	method
		//==========================================
	public:
		static GameCore* GetInstance();

		SceneManager* GetSceneManager() const;
		SystemManager* GetSystemManager() const;

		//==========================================
		//	procedure
		//==========================================
		void Init();

		//==========================================
		//	constructor/destructor
		//==========================================
	private:
		GameCore(IApplication* app);
		~GameCore();
	};
}