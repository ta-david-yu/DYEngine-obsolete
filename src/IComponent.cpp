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

	void IComponent::SetName(const std::string& _name)
	{
		m_pEntity->SetName(_name);
	}

	void IComponent::release()						// called by  (Destroy Loop)
	{
		m_pEntity->removeComponent(GetInstanceID());
	}

	void IComponent::copyFrom(const IComponent* other)
	{
		this->m_IsEnabled = other->m_IsEnabled;
	}

	//====================================================================================
	//	Transform: Basic component for every entity
	//====================================================================================

	Transform* Transform::GetParent() const
	{
		return m_pParent;
	}

	Vector3f Transform::GetPosition() const
	{
		return m_Position;
	}

	Quaternion Transform::GetRotation() const
	{
		return m_Rotation;
	}

	Vector3f Transform::GetScale() const
	{
		return m_Scale;
	}

	Vector3f Transform::Up() const
	{
		return m_Rotation.operator*(Vector3f::UnitY());
	}

	Vector3f Transform::Right() const
	{
		return m_Rotation.operator*(Vector3f::UnitX());
	}

	Vector3f Transform::Forward() const
	{
		return m_Rotation.operator*(Vector3f::UnitZ());
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

	void Transform::SetPosition(const Vector3f& _vec)
	{
		m_Position = _vec;
	}

	void Transform::SetRotation(const Quaternion& _vec)
	{
		m_Rotation = _vec;
	}

	void Transform::SetScale(const Vector3f& _vec)
	{
		m_Scale = _vec;
	}

	void Transform::removeChildren(Transform* _child)
	{
		m_ChildrenList.remove(_child);
	}

	void Transform::addChildren(Transform* _child)
	{
		m_ChildrenList.push_back(_child);
	}

	void Transform::copyFrom(const IComponent* other)
	{
		IComponent::copyFrom(other);
		
		const Transform* otherTrans = dynamic_cast<const Transform*>(other);

		this->m_Position = otherTrans->m_Position;
		this->m_Rotation = otherTrans->m_Rotation;
		this->m_Scale = otherTrans->m_Scale;

		this->m_pParent = otherTrans->m_pParent;

		// loop through target entity's children
		for (const auto& child : otherTrans->m_ChildrenList)
		{
			// clone target entity child
			Entity* cloneChild = dynamic_cast<Entity*>( Instantiate(child) );
			// set clone's parent to this
			cloneChild->GetTransform()->SetParent(this);
		}

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