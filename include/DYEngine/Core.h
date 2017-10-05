#pragma once

#include <DYEngine\Scene.h>

#define CORE Core::GetInstance()

namespace DYE
{
	class Scene;
	class IApplication;

	//====================================================================================
	//	Core: core class for managing scenes and systems
	//====================================================================================
	class Core
	{
		friend class IApplication;
		friend class Scene;
	public:
		using SceneListPair = std::pair<SceneID, Scene*>;
		using SceneList = std::vector<SceneListPair>;

	private:
		//==========================================
		//	memeber/variable
		//==========================================
		IApp* m_pApplication;

		static Core* s_pInstance;
		SceneList m_Scenes;

		SceneID m_CurrScene = 0;
		SceneID m_NextScene = -1;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================
	public:
		void Init();
		//==========================================
		//	method
		//==========================================
		static Core* GetInstance();
	private:
		Scene* createScene();				// create a ptr to scene and add it to the list
		Scene* loadScene(SceneID);			// instant load scene
		//==========================================
		//	getter
		//==========================================

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	private:
		Core(IApp* app);
		~Core();
	};
}