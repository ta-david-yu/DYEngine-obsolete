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

	using SceneID = int;
	//====================================================================================
	//	Core: core class for managing scenes and systems
	//====================================================================================
	class Core
	{
		friend class IApplication;
		friend class IScene;
	public:
		using SceneListPair = std::pair<SceneID, std::unique_ptr<IScene>>;
		using SceneList = std::vector<SceneListPair>;

	private:
		//==========================================
		//	memeber/variable
		//==========================================
		IApplication* m_pApplication;

		static Core* s_pInstance;
		SceneList m_Scenes;

		SceneID m_SceneIDCounter = 0;

		SceneID m_CurrSceneID = 0;
		SceneID m_NextSceneID = -1;
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

		template <typename TApp>
		IScene* createScene(void (TApp::*buildFunc)(IScene*))		// create a ptr to scene and add it to the list
		{
			IScene* ptr = new Scene<TApp>(m_SceneIDCounter, dynamic_cast<TApp*>(m_pApplication), buildFunc);

			m_Scenes.push_back(SceneListPair(m_SceneIDCounter, std::unique_ptr<IScene>(ptr)));

			m_SceneIDCounter++;

			return m_Scenes.back().second.get();
		}
		IScene* loadScene(SceneID id);						// instant load scene
		//==========================================
		//	getter
		//==========================================
		IScene* getScene(SceneID id) const;

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	private:
		Core(IApplication* app);
		~Core();
	};
}