#pragma once

#include <DYEngine\Main.h>

#include <vector>
#include <string>
#include <memory>

namespace DYE
{
	typedef unsigned int SceneID;
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================
	class Scene
	{
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