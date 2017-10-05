#include <DYEngine\Scene.h>

#include <functional>

namespace DYE
{
	//====================================================================================
	//	Scene: managing objects
	//====================================================================================

	Entity* IScene::CreateEntity()
	{
		std::unique_ptr<Entity> uniPtr = std::make_unique<Entity>(this);
		Entity* ptr = uniPtr.get();

		m_EntityList.push_back(EntityListPair(ptr->GetInstanceID(), std::move(uniPtr)));

		return ptr;
	}

	Entity* IScene::CreateEntity(const std::string& _name)
	{
		std::unique_ptr<Entity> uniPtr = std::make_unique<Entity>(this, _name);
		Entity* ptr = uniPtr.get();

		m_EntityList.push_back(EntityListPair(ptr->GetInstanceID(), std::move(uniPtr)));

		return ptr;
	}

	SceneID IScene::GetSceneID() const
	{
		return m_SceneID;
	}

	std::string IScene::GetSceneName() const
	{
		return m_SceneName;
	}

	bool IScene::IsLoaded() const
	{
		return m_IsLoaded;
	}

	void IScene::release()
	{
		m_EntityList.clear();

		m_IsLoaded = false;
	}

	void IScene::removeEntity(InstanceID _id)
	{
		auto itr = std::find_if(m_EntityList.begin(), m_EntityList.end(), 
			[_id](const EntityListPair& element) { return element.first == _id; });

		if (itr != m_EntityList.end())
		{
			itr->second.reset();		// release entity
			m_EntityList.erase(itr);	// erase entry
		}
	}

	IScene::IScene(SceneID id) : m_SceneID(id)
	{

	}

	IScene::~IScene()
	{
		release();
	}
}