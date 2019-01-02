#pragma once

#include <DYEngine/Core.h>

#include <DYEngine/Entity.h>
#include <DYEngine/utilities\Delegate.h>

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <type_traits>

#define DYE_SCENE_CLASS friend class SceneManager;

namespace DYE
{
	class IApplication;

	using SceneID = int;
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================
	class DYE_API IScene : public NonCopyable
	{
		friend class Entity;
		friend class IApplication;
		friend class SceneManager;

		typedef std::pair<InstanceID, std::unique_ptr<Entity>> EntityListPair;
		typedef std::vector<EntityListPair> EntityList;

		//==========================================
		//	memeber/variable
		//==========================================
	protected:
		bool m_IsLoaded = false;
		SceneID m_SceneID;
		std::string m_SceneName;
		EntityList m_EntityList;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================
		virtual void load();						// create object and comps, call build function
		void release();									// called when destroyed
		//==========================================
		//	method
		//==========================================
	private:
		void removeEntity(InstanceID _id);				// called by entity release <- DestructionUpdate

	public:
		Entity* CreateEntity();
		Entity* CreateEntity(const std::string& _name);
		//==========================================
		//	getter
		//==========================================
	public:
		SceneID GetSceneID() const;
		std::string GetSceneName() const;
		bool IsLoaded() const;
		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
		IScene();
		~IScene();
	};

	//====================================================================================
	//	SceneManager: Used to manage scene operation
	//====================================================================================
	class DYE_API SceneManager : public NonCopyable
	{
		friend class IApplication;
		friend class GameCore;

	public:
		using SceneListPair = std::pair<SceneID, std::unique_ptr<IScene>>;
		using SceneList = std::vector<SceneListPair>;

	private:
		//==========================================
		//	memeber/variable
		//==========================================
		SceneID m_SceneIDCounter = 0;
		SceneID m_CurrSceneID = 0;
		SceneID m_NextSceneID = -1;
		bool m_IsLoadingNextScene = false;

		SceneList m_Scenes;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	method
		//==========================================
	public:
		void LoadScene(SceneID id);									// delay load for gmae logic

		//==========================================
		//	procedure
		//==========================================
		void Init();
		void LoadNextScene();

		template <class TScene>
		IScene* CreateScene()										// create a ptr to scene and add it to the list
		{
			bool isDerivedFromIScene = std::is_base_of<IScene, TScene>::value;

			assert(isDerivedFromIScene);

			IScene* ptr = new TScene();

			ptr->m_SceneID = m_SceneIDCounter;

			m_Scenes.push_back(SceneListPair(m_SceneIDCounter, std::unique_ptr<IScene>(ptr)));

			m_SceneIDCounter++;

			return m_Scenes.back().second.get();
		}

	private:
		IScene* loadScene(SceneID id);								// instant load scene

		//==========================================
		//	getter
		//==========================================
		IScene* getScene(SceneID id) const;

	public:
		bool IsLoadingNextScene() const;
		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	private:
		SceneManager();
		~SceneManager();
	};
}