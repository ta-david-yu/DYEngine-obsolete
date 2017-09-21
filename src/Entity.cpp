#include <DYEngine\Entity.h>

namespace DYE
{
	//====================================================================================
	//	Entity: Base Entity class as game object
	//====================================================================================

	Transform* Entity::GetTransform() const
	{
		return this->m_pTransform;
	}

	void Entity::release()								// called by  (Destroy Loop)
	{
		m_pScene->removeEntity(GetInstanceID());
	}

	void Entity::removeComponent(InstanceID _id)
	{
		auto itr = std::find_if(m_Components.begin(), m_Components.end(),
			[_id](const ComponentListPair& element) { return element.first == _id; });

		if (itr != m_Components.end())
		{
			itr->second.reset();		// release entity
			m_Components.erase(itr);	// erase entry
		}
	}

	Entity::Entity(Scene* _scene, const std::string& _name)
	{
		m_pTransform = this->AddComponent<Transform>();
		m_pScene = _scene;
		SetName(_name);
	}

	Entity::~Entity()
	{

	}
}