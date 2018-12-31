#pragma once

#include <DYEngine/Entity.h>
#include <DYEngine/utilities\Delegate.h>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace DYE
{
	class Entity;
	class IApplication;
	class IScene;

	using SceneID = int;
	using BuildSceneFunc = Delegate<void, IScene*>;
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================
	class IScene
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
		virtual void load() = 0;						// create object and comps, call build function
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
		IScene(SceneID id = 0);
		~IScene();
	};

	//====================================================================================
	//	Scene: managing objects
	//====================================================================================
	template <typename TApp>
	class Scene : public IScene
	{
		friend class SceneManager;
	private:
		BuildSceneFunc m_BuildFunction;

	protected:
		virtual void load()
		{
			// build scene out of the build function
			m_BuildFunction(this);

			m_IsLoaded = true;
		}
	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		Scene(SceneID id, TApp* owner,void (TApp::*buildFunc)(IScene*)) : IScene(id), m_BuildFunction(owner, buildFunc)
		{ }

		~Scene()
		{ }
	};

	//====================================================================================
	//	SceneManager: Used to manage scene operation
	//====================================================================================
	class SceneManager
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

		IApplication* m_pApplication;

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

	private:
		template <typename TApp>
		IScene* createScene(void (TApp::*buildFunc)(IScene*))		// create a ptr to scene and add it to the list
		{
			IScene* ptr = new Scene<TApp>(m_SceneIDCounter, dynamic_cast<TApp*>(m_pApplication), buildFunc);

			m_Scenes.push_back(SceneListPair(m_SceneIDCounter, std::unique_ptr<IScene>(ptr)));

			m_SceneIDCounter++;

			return m_Scenes.back().second.get();
		}

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
		SceneManager(IApplication* app);
		~SceneManager();
	};
}