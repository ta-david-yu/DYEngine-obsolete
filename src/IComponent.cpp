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

	std::string IComponent::GetName() const 
	{ 
		return m_pEntity->GetName(); 
	}
}