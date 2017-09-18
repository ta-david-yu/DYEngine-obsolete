#pragma once

#include <DYEngine\Main.h>

#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>

namespace DYE
{
	class IEntity;
	class ISystem;

	//====================================================================================
	//	IComponent
	//====================================================================================
	class IComponent : public Base
	{
		friend class IEntity;
		friend class ISystem;
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		ISystem* m_pSystem;
	protected:
		IEntity* m_pEntity;
		//==========================================
		//	flag
		//==========================================
		bool m_IsEnabled;
	public:
		//==========================================
		//	procedure
		//==========================================
		// Must be call after creation, to be hide
		virtual void Init() {}

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
		void SetName(const std::string& _name) = delete;
	public:
		void AttachTo(IEntity* _pEnt) { m_pEntity = _pEnt; }
		//==========================================
		//	getter
		//==========================================
		IEntity* GetEntity() const { return m_pEntity; }
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

		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================
		virtual void Update() {}

		//==========================================
		//	method
		//==========================================

		//==========================================
		//	getter
		//==========================================

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	public:
		Transform() {}
		~Transform() {}

	};

	//====================================================================================
	//	DummyComponent: Test Component
	//====================================================================================
	class DummyComponent : public IComponent
	{
	public:
		virtual void Update() {}
	};
}