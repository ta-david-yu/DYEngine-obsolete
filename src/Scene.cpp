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

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}
}