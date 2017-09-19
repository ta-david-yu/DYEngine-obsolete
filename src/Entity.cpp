#include <DYEngine\Entity.h>

namespace DYE
{
	Transform* Entity::GetTransform() const
	{
		return this->m_Transform;
	}

	void Entity::release()								// TO DO: destroy from objectMgr (erased from vector), 
	{

	}
	
	Entity::Entity() 
	{
		m_Transform = this->AddComponent<Transform>();
	}

	Entity::Entity(const std::string& _name)
	{
		SetName(_name);
		Entity();
	}

	Entity::~Entity()
	{

	}
}