#include <DYEngine\Scene.h>

namespace DYE
{
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================

	Entity* Scene::CreateEntity()
	{
		std::unique_ptr<Entity> uniPtr = std::make_unique<Entity>(this);
		Entity* ptr = uniPtr.get();

		m_EntityList.push_back(EntityListPair(ptr->GetInstanceID(), std::move(uniPtr)));

		return ptr;
	}

	Entity* Scene::CreateEntity(const std::string& _name)
	{
		std::unique_ptr<Entity> uniPtr = std::make_unique<Entity>(this, _name);
		Entity* ptr = uniPtr.get();

		m_EntityList.push_back(EntityListPair(ptr->GetInstanceID(), std::move(uniPtr)));

		return ptr;
	}

	SceneID Scene::GetSceneID() const
	{
		return m_SceneID;
	}

	std::string Scene::GetSceneName() const
	{
		return m_SceneName;
	}

	void Scene::removeEntity(InstanceID _id)
	{
		auto itr = std::find_if(m_EntityList.begin(), m_EntityList.end(), 
			[_id](const EntityListPair& element) { return element.first == _id; });

		if (itr != m_EntityList.end())
		{
			itr->second.reset();		// release entity
			m_EntityList.erase(itr);	// erase entry
		}
	}

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}
}