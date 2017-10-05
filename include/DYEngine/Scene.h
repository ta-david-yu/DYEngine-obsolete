#pragma once

#include <DYEngine\Entity.h>
#include <DYEngine\Core.h>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace DYE
{
	class Entity;
	class IApp;

	using SceneID = int;
	using BuildSceneFunc = std::function<void(IApp const&, Scene*)>;
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================
	class Scene
	{
		friend class Entity;
		friend class IApp;

		typedef std::pair<InstanceID, std::unique_ptr<Entity>> EntityListPair;
		typedef std::vector<EntityListPair> EntityList;

		//==========================================
		//	memeber/variable
		//==========================================
	private:
		bool m_IsLoaded = false;
		BuildSceneFunc m_pBuildFunction;
		SceneID m_SceneID;
		std::string m_SceneName;
		EntityList m_EntityList;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================
		void load();									// create object and comps, call build function
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
		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
		Scene();
		~Scene();
	};
}