#include <DYEngine\interfaces\IComponent.h>

namespace DYE
{
	IComponent::IComponent()
	{

	}

	IComponent::~IComponent() 
	{ 
		m_pSystem->unregisterComponent(this); 
	}

	IEntity* IComponent::GetEntity() const 
	{ 
		return m_pEntity; 
	}

	std::string IComponent::GetName() const 
	{ 
		return m_pEntity->GetName(); 
	}

	void IComponent::release()						// TO DO: destroy from object (erased from map)
	{

	}

}