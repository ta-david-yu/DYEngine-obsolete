#pragma once

#include <DYEngine\Entity.h>
#include <DYEngine\Core.h>
#include <DYEngine\utilities\Delegate.h>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace DYE
{
	class Entity;
	class IApplication;

	using SceneID = int;
	using BuildSceneFunc = Delegate<void, IScene*>;
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================
	class IScene
	{
		friend class Entity;
		friend class IApplication;
		friend class Core;

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
		friend class Core;
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
}