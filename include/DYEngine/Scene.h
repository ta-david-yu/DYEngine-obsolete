#pragma once

#include <DYEngine\Entity.h>

#include <vector>
#include <string>
#include <memory>

namespace DYE
{
	class Entity;

	typedef unsigned int SceneID;
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================
	class Scene
	{
		friend class Entity;

		typedef std::pair<InstanceID, std::unique_ptr<Entity>> EntityListPair;
		typedef std::vector<EntityListPair> EntityList;

		//==========================================
		//	memeber/variable
		//==========================================
	private:
		SceneID m_SceneID;
		std::string m_SceneName;
		EntityList m_EntityList;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================

		//==========================================
		//	method
		//==========================================
	private:
		void removeEntity(InstanceID _id);
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