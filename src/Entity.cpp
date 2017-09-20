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

	void Entity::release()								// TO DO: destroy from objectMgr (erased from vector), 
	{

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