#include <DYEngine\interfaces\IEntity.h>

namespace DYE
{
	Transform* IEntity::GetTransform() const
	{
		return this->m_Transform;
	}

	void IEntity::release()								// TO DO: destroy from objectMgr (erased from vector), 
	{

	}
	
	IEntity::IEntity() 
	{
		m_Transform = this->AddComponent<Transform>();
	}

	IEntity::IEntity(const std::string& _name)
	{
		SetName(_name);
		IEntity();
	}

	IEntity::~IEntity()
	{

	}
}