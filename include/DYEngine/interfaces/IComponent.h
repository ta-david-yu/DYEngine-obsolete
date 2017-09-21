#pragma once

#include <DYEngine\Main.h>

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
		virtual void Init() = 0;

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
	protected:
		void release() override;
	private:
		using Base::SetName;								// Move to private so the name cant be changed
	public:
		void AttachTo(Entity* _pEnt) { m_pEntity = _pEnt; }
		//==========================================
		//	getter
		//==========================================
		Entity* GetEntity() const;
		Transform* GetTransform() const;
		std::string GetName() const;
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
		// TO DO: add pos, rot...
		//==========================================
		//	memeber/variable
		//==========================================
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
	private:
		void removeChildren(Transform* _child);
		void addChildren(Transform* _child);
		//==========================================
		//	getter
		//==========================================
	public:
		Transform* GetParent() const;
		//==========================================
		//	setter
		//==========================================
		void SetParent(Transform* _parent);
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