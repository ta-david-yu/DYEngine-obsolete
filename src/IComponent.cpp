#include <DYEngine\interfaces\IComponent.h>

#include <type_traits>

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

	bool IComponent::IsEnabled() const
	{
		// check if transform enabled
		return m_pEntity->IsActive() & m_IsEnabled;
	}

	void IComponent::SetEnabled(bool set)
	{
		this->m_IsEnabled = set;

		if (set)
			OnEnable();
		else
			OnDisable();
	}

	void IComponent::SetName(const std::string& _name)
	{
		m_pEntity->SetName(_name);
	}

	void IComponent::release()						// called by  (Destroy Loop)
	{
		m_pEntity->removeComponent(GetInstanceID());
	}

	void IComponent::copyFrom(IComponent* other)
	{
		this->m_IsEnabled = other->m_IsEnabled;
	}

	//====================================================================================
	//	Transform: Basic component for every entity
	//====================================================================================
	void Transform::Init()
	{
		m_IsLocalEnabled = true;
		m_IsEnabled = true;

		// reset dirty flag
		resetDirtyState();
	}

	void Transform::EarlyUpdate()
	{
		// and change children global enabled
		if (m_IsDirtyLocalEnabled)
		{
			this->m_IsEnabled = m_pParent->m_IsEnabled && this->m_IsLocalEnabled;
			for (auto const & child : m_ChildrenList)
			{
				// child->m_IsEnabled = this->m_IsEnabled && child->m_IsLocalEnabled;
				child->m_IsDirtyLocalEnabled = true;
			}
		}

		// TO DO: deferred update, update state according to parent position, flag

		// reset dirty flag
		resetDirtyState();
	}


	Transform* Transform::GetParent()
	{
		return (m_pParent == TransformSystem::GetRoot())? nullptr : m_pParent;
	}

	const Transform* Transform::GetParent() const
	{
		return (m_pParent == TransformSystem::GetRoot()) ? nullptr : m_pParent;
	}

	Transform* Transform::GetRoot()
	{
		Transform* temp = this->GetParent();
		if (temp == nullptr)
		{
			return this;
		}

		while (temp->GetParent() != nullptr)
		{
			temp = temp->GetParent();
		}
		return temp;
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

	Vector3f Transform::GetLocalPosition() const
	{
		return m_LocalPosition;
	}

	Quaternion Transform::GetLocalRotation() const
	{
		return m_LocalRotation;
	}

	Vector3f Transform::GetLocalScale() const
	{
		return m_LocalScale;
	}

	Mat4x4 Transform::GetModelMatrix() const
	{
		// Translate * Rotation * Scale
		auto pos = this->GetPosition();
		auto scale = this->GetScale();
		auto rot = this->GetRotation();

		Mat4x4 modelMatrix = 
			pos.ToTranslateMatrix() * rot.ToMat4x4() * scale.ToScaleMatrix();

		return modelMatrix;
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
		if (this->GetParent() != nullptr)
		{
			m_pParent->removeChildren(this);
		}

		if (_parent != nullptr)
		{
			// if it is a child of this, swap position
			if (_parent->GetParent() == this)
			{
				_parent->SetParent(this->GetParent());
			}

			m_pParent = _parent;

			m_pParent->addChildren(this);
		}
	}

	void Transform::SetPosition(const Vector3f& _vec)
	{
		m_Position = _vec;
		m_PositionDirtyState = Global;
	}

	void Transform::SetRotation(const Quaternion& _vec)
	{
		m_Rotation = _vec;
		m_RotationDirtyState = Global;
	}

	void Transform::SetLocalPosition(const Vector3f& _vec)
	{
		m_LocalPosition = _vec;
		m_PositionDirtyState = Local;
	}

	void Transform::SetLocalRotation(const Quaternion& _vec)
	{
		m_LocalRotation = _vec;
		m_RotationDirtyState = Local;
	}

	void Transform::SetLocalScale(const Vector3f& _vec)
	{
		m_Scale = _vec;
		m_ScaleDirtyState = Local;
	}

	void Transform::removeChildren(Transform* _child)
	{
		m_ChildrenList.remove(_child);
	}

	void Transform::addChildren(Transform* _child)
	{
		m_ChildrenList.push_back(_child);
	}

	bool Transform::hasChildren(const Transform* _child) const
	{
		return std::find(m_ChildrenList.begin(), m_ChildrenList.end(), _child) != m_ChildrenList.end();
	}

	void Transform::resetDirtyState()
	{
		m_PositionDirtyState = DirtyState::Clean;
		m_RotationDirtyState = DirtyState::Clean;
		m_ScaleDirtyState = DirtyState::Clean;

		m_IsDirtyLocalEnabled = false;
	}

	void Transform::copyFrom(IComponent* other)
	{
		IComponent::copyFrom(other);
		
		Transform* otherTrans = dynamic_cast<Transform*>(other);

		this->m_IsLocalEnabled = otherTrans->m_IsLocalEnabled;

		this->SetPosition(otherTrans->GetPosition());
		this->SetPosition(otherTrans->GetLocalPosition());
		this->SetRotation(otherTrans->GetRotation());
		this->SetLocalRotation(otherTrans->GetLocalRotation());
		this->SetLocalScale(otherTrans->GetLocalScale());

		this->SetParent(otherTrans->GetParent());

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

	Transform::Transform() : m_pParent(nullptr)
	{

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