#pragma once

#include <DYEngine/utilities/Macro.h>

#include <DYEngine/Base.h>
#include <DYEngine/Entity.h>
#include <DYEngine/utilities/Math.h>

#include <vector>
#include <map>
#include <list>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <tuple>

#define DYE_COMPONENT_DYNAMICCAST(T) virtual T& DynamicCast()				\
		{																	\
		return *this;														\
		}

#define DYE_COMPONENT_TOSTRING virtual std::string ToString() const			\
		{																	\
		using Type = std::remove_pointer_t<decltype(this)>;					\
		return std::string(typeid(Type).name());							\
		}

// using ComponentType = std::remove_pointer_t< decltype(comp.second.get()) >;

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

	enum DirtyState
	{
		Clean,
		Local,
		Global
	};

	//====================================================================================
	//	IComponent
	//====================================================================================
	class IComponent : public Base
	{
	public:
		// must added macro
		DYE_COMPONENT_TOSTRING
	
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
		bool m_IsEnabled = true;
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
		virtual void EarlyUpdate() {}
		virtual void FixedUpdate() {}
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
		virtual void copyFrom(IComponent* _other);
		// called by AddComponent(IComp), return an identical component pointer.
		virtual IComponent* clone() { assert(false); return nullptr; }		// TO DO: to abstract
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
		virtual bool IsEnabled() const;
		virtual void SetEnabled(bool set);
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
		virtual ~IComponent();
	};

	//====================================================================================
	//	Transform: Basic component for every entity
	//====================================================================================
	class Transform : public IComponent
	{
	public:
		// must added macro
		DYE_COMPONENT_TOSTRING

		friend class Entity;
		friend class TransformSystem;
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		Vector3f m_Position;
		Vector3f m_Scale;
		Quaternion m_Rotation;

		Vector3f m_LocalPosition;
		Vector3f m_LocalScale;
		Quaternion m_LocalRotation;

		bool m_IsLocalEnabled;
	private:
		Transform* m_pParent = nullptr;
		std::list<Transform*> m_ChildrenList;
		//==========================================
		//	flag
		//==========================================
		DirtyState m_PositionDirtyState = DirtyState::Clean;
		DirtyState m_RotationDirtyState = DirtyState::Clean;
		DirtyState m_ScaleDirtyState = DirtyState::Clean;

		bool m_IsDirtyLocalEnabled = false;

		//==========================================
		//	procedure
		//==========================================
	public:
		virtual void Init();
		virtual void EarlyUpdate();		// deferred update
		virtual void Update() {}

		//==========================================
		//	method
		//==========================================
	protected:
		virtual void copyFrom(IComponent* _other);
		virtual IComponent* clone();
	private:
		void removeChildren(Transform* _child);
		void addChildren(Transform* _child);
		bool hasChildren(const Transform* _child) const;
		void resetDirtyState();
		//==========================================
		//	getter
		//==========================================
	public:
		// TO DO: local, global operation
		Transform* GetParent();
		const Transform* GetParent() const;
		Transform* GetRoot();

		Vector3f GetPosition() const;
		Quaternion GetRotation() const;
		Vector3f GetScale() const;
		Vector3f GetLocalPosition() const;
		Quaternion GetLocalRotation() const;
		Vector3f GetLocalScale() const;
		Mat4x4 GetModelMatrix() const;// return a model matrix for an object converting from this space to global space

		Vector3f Up() const;
		Vector3f Right() const;
		Vector3f Forward() const;
	
		virtual bool IsEnabled() const { return m_IsEnabled; }
		//==========================================
		//	setter
		//==========================================
		void SetParent(Transform* _parent);
		void SetPosition(const Vector3f& _vec);
		void SetRotation(const Quaternion& _vec);
		void SetLocalPosition(const Vector3f& _vec);
		void SetLocalRotation(const Quaternion& _vec);
		void SetLocalScale(const Vector3f& _vec);

		virtual void SetEnabled(bool set) const { /* DO NOTHING */ }
		//==========================================
		//	constructor/destructor
		//==========================================
	public:
		Transform();
		~Transform() {}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//====================================================================================
	//	IReusable: Resuable base class that can be managed by ReusablePool
	//====================================================================================
	class IReusableComponent : public IComponent
	{
	public:
		// must added macro
		DYE_COMPONENT_TOSTRING

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
		// must added macro
		DYE_COMPONENT_TOSTRING
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
	class DebugCPUComponent : public IComponent
	{
	public:
		// must added macro
		DYE_COMPONENT_TOSTRING
	public:
		int LoopCount = 400;
	public:
		virtual void Init() {}
		virtual void Update()
		{
			int c = LoopCount;
			while (c--)
			{
				int t = c;
				while (t--)
					printf("");
			}
		}
	};
}