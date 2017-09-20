#include <DYEngine\interfaces\IComponent.h>

namespace DYE
{
	//====================================================================================
	//	IComponent
	//====================================================================================

	IComponent::IComponent()
	{

	}

	IComponent::~IComponent() 
	{ 
		m_pSystem->unregisterComponent(this); 
	}

	Entity* IComponent::GetEntity() const 
	{ 
		return m_pEntity; 
	}

	Transform* IComponent::GetTransform() const
	{
		return m_pEntity->GetTransform();
	}

	std::string IComponent::GetName() const 
	{ 
		return m_pEntity->GetName(); 
	}

	void IComponent::release()						// TO DO: destroy from object (erased from map)
	{

	}

	//====================================================================================
	//	Transform: Basic component for every entity
	//====================================================================================

	Transform* Transform::GetParent() const
	{
		return m_pParent;
	}

	void Transform::SetParent(Transform* _parent)
	{
		if (m_pParent != nullptr)
		{
			m_pParent->removeChildren(this);
		}

		m_pParent = _parent;

		if (m_pParent != nullptr)
		{
			m_pParent->addChildren(this);
		}
	}

	void Transform::removeChildren(Transform* _child)
	{
		m_ChildrenList.remove(_child);
	}

	void Transform::addChildren(Transform* _child)
	{
		m_ChildrenList.push_back(_child);
	}

	//====================================================================================
	//	IReusable: Resuable base class that can be managed by ReusablePool
	//====================================================================================

	void IReusableComponent::setInUse(bool _set)
	{
		m_IsInUse = _set;
	}

	void IReusableComponent::ReleaseToPool()
	{
		releaseToPool();
		setInUse(false);
	}

	IReusableComponent* ReusablePool::AcquireReusable()
	{
		for (auto const& obj : m_Pool)
		{
			if (!obj->IsInUse())
			{
				obj->setInUse(true);
				return obj;
			}
		}
		expandPool(m_IncrementSize);
		return m_Pool.back();
	}

	//====================================================================================
	//	ReusablePool: Reusable Entity Management
	//====================================================================================

	void ReusablePool::ResizePool(std::size_t _size)
	{
		int diff = _size - m_MaxSize;
		if (diff > 0)
		{
			expandPool(diff);
		}
	}

	void ReusablePool::expandPool(std::size_t _incre)
	{
		for (std::size_t i = 0; i < _incre; i++)
		{
			IReusableComponent* newObj = dynamic_cast<IReusableComponent*>(Instantiate(m_Prefab));
			newObj->releaseToPool();
			m_Pool.push_back(newObj);

		}
		m_MaxSize += _incre;
	}
}