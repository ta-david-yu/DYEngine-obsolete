#pragma once

#include <DYEngine\Base.h>
#include <DYEngine\Entity.h>
#include <DYEngine\utilities\Math.h>

#include <vector>
#include <map>
#include <list>
#include <typeinfo>
#include <typeindex>
#include <tuple>

namespace DYE
{
	class Base;
	class Entity;
	class Transform;
	class ISystem;
	struct Vector2f;
	struct Vector3f;
	struct Vector4f;
	struct Quaternion;

	//====================================================================================
	//	IComponent
	//====================================================================================
	class IComponent : public Base
	{
		friend class Entity;
		friend class ISystem;
	public:
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		ISystem* m_pSystem;
	protected:
		Entity* m_pEntity;
		//==========================================
		//	flag
		//==========================================
		bool m_IsEnabled;
	public:
		//==========================================
		//	procedure
		//==========================================
		// Must be call after creation, to be hide
		virtual void Init() = 0;					// used to load assets

		// Call by System
		// TO DO: reimplement
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() = 0;
		virtual void LateUpdate() {}

		// Call by Event
		virtual void OnEnable() {}
		virtual void OnDisable() {}
		virtual void OnDestroy() {}
		//==========================================
		//	method
		//==========================================
	private:
		void release() override;
	protected:
		// called by instantiate, use to copy data (notice that the component has to be created using add component)
		// therefore, m_pSystem and m_pEntity are handled. Derived class's copyFrom must call base.copyFrom(IComponent* _other)
		virtual void copyFrom(const IComponent* _other);		
	public:
		virtual void SetName(const std::string& _name);
	public:
		void AttachTo(Entity* _pEnt) { m_pEntity = _pEnt; }
		//==========================================
		//	getter
		//==========================================
		Entity* GetEntity() const;
		Transform* GetTransform() const;
		virtual std::string GetName() const;
		template <class TComp>
		TComp* GetComponent() const 
		{ 
			return m_pEntity->GetComponent<TComp>(); 
		}
		//==========================================
		//	setter
		//==========================================
	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		IComponent();
		~IComponent();
	};

	//====================================================================================
	//	Transform: Basic component for every entity
	//====================================================================================
	class Transform : public IComponent
	{
		friend class Entity;
		//==========================================
		//	memeber/variable
		//==========================================
		Vector3f m_Position;
		Vector3f m_Scale;
		Quaternion m_Rotation;
	private:
		Transform* m_pParent = nullptr;
		std::list<Transform*> m_ChildrenList;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================
	public:
		virtual void Init() {}
		virtual void Update() {}

		//==========================================
		//	method
		//==========================================
	protected:
		virtual void copyFrom(const IComponent* _other);
	private:
		void removeChildren(Transform* _child);
		void addChildren(Transform* _child);
		//==========================================
		//	getter
		//==========================================
	public:
		Transform* GetParent() const;
		Vector3f GetPosition() const;
		Quaternion GetRotation() const;
		Vector3f GetScale() const;
		Vector3f Up() const;
		Vector3f Right() const;
		Vector3f Forward() const;
		//==========================================
		//	setter
		//==========================================
		void SetParent(Transform* _parent);
		void SetPosition(const Vector3f& _vec);
		void SetRotation(const Quaternion& _vec);
		void SetScale(const Vector3f& _vec);
		//==========================================
		//	constructor/destructor
		//==========================================
	public:
		Transform() {}
		~Transform() {}

	};

	//====================================================================================
	//	IReusable: Resuable base class that can be managed by ReusablePool
	//====================================================================================
	class IReusableComponent : public IComponent
	{
		friend class ReusablePool;
	private:
		bool m_IsInUse = false;
		void setInUse(bool _set);
		virtual void releaseToPool() = 0;
	public:
		bool IsInUse() const { return m_IsInUse; }
		void ReleaseToPool();
	};

	//====================================================================================
	//	ReusablePool: Reusable Entity Management
	//====================================================================================
	class ReusablePool : public IComponent
	{
	public:
	private:
		std::size_t m_MaxSize = 32;
		std::size_t m_IncrementSize = 4;
		std::vector<IReusableComponent*> m_Pool;
		//==========================================
		//	memeber/variable
		//==========================================
		IReusableComponent* m_Prefab;
		//==========================================
		//	procedure
		//==========================================
	public:
		virtual void Init()
		{
			Init(32, 4);
		}
		virtual void Init(std::size_t _initSize, std::size_t _initIncre) 
		{ 
			m_MaxSize = _initSize;
			m_IncrementSize = _initIncre;
		}
		virtual void Start() { expandPool(m_MaxSize); }
		virtual void Update() {}
		//==========================================
		//	method
		//==========================================
	public:
		IReusableComponent* AcquireReusable();			// Return a not used object
		void ResizePool(std::size_t _size);				// Allocate pool count based on the number (if is smaller than max, ignore)
	private:
		void expandPool(std::size_t _incre);			// Add number of objs to pool
		//==========================================
		//	setter
		//==========================================
	public:
		void SetIncrementSize(std::size_t _size) { m_IncrementSize = _size; }
	};

	//====================================================================================
	//	DummyComponent: Test Component
	//====================================================================================
	class DummyComponent : public IComponent
	{
	public:
		virtual void Init() {}
		virtual void Update() {}
	};
}