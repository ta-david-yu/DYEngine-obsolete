#pragma once

#include <DYEngine\interfaces\IComponent.h>
#include <DYEngine\Entity.h>

#include <vector>
#include <list>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <algorithm>

#define SYSTEM_MGR DYE::SystemManager::GetInstance()
#define MAX_COMPONENT_SYSTEM 1024;

namespace DYE
{
	class Entity;
	class IComponent;
	class SystemManager;
	class Transform;
	class TransformSystem;
	class IApplication;

	//====================================================================================
	//	ISystem: manage all components
	//====================================================================================
	class ISystem
	{
		friend class IComponent;
		friend class SystemManager;
	public:
		typedef std::pair<InstanceID, IComponent*> ComponentListPair;
		typedef std::vector<ComponentListPair> ComponentList;

	protected:
		//==========================================
		//	memeber/variable
		//==========================================
		std::size_t m_SystemID;
		ComponentList m_ComponentsList;
	public:
		//==========================================
		//	procedure
		//==========================================
		// Run through each component in the list
		// TO DO: reimplement
		virtual void Awake();
		virtual void Start();
		virtual void EarlyUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void FixedUpdate();
		//==========================================
		//	method
		//==========================================
	protected:
		void registerComponent(IComponent* _pComp);			// called by entity addComponent, to register component pointer to the System
		void unregisterComponent(IComponent* _pComp);		// called by component destructor, to unregister component pointer in the System
	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		ISystem() {}
		~ISystem() {}
	};


	//====================================================================================
	//	SystemManager: manage all user-created components systems
	//====================================================================================
	class SystemManager
	{
		friend class IApplication;
		friend class Core;

	public:
		using SystemListPair = std::pair<std::type_index, std::unique_ptr<ISystem>>;
		using SystemList = std::vector<SystemListPair>;
		using SystemListItr = SystemList::iterator;
		using SystemListConstItr = SystemList::const_iterator;

	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static SystemManager* s_pInstance;

		IApplication* m_pApplication;

		SystemList m_SystemList;
		std::size_t m_NextSystemIDCounter;
		//==========================================
		//	specialized system
		//==========================================
		std::unique_ptr<TransformSystem> m_uniqueTransformSystem;
		TransformSystem* m_pTransformSystem;

	public:
		static SystemManager* GetInstance();
		//==========================================
		//	procedure
		//==========================================
		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void EarlyUpdate();
		virtual void LateUpdate();
		virtual void FixedUpdate();

		//==========================================
		//	method
		//==========================================
		template <class TComp>
		bool HasSystem() const					// Return true if system of type TComp has already been added
		{
			auto itr = std::find_if(m_SystemList.begin(), m_SystemList.end(),
				[](const SystemListPair& element) { return element.first == typeid(TComp); });
			return !(itr == m_SystemList.end());
		}

		template <class TComp>
		void RegisterComponent(TComp* _pComp)	// Register a component
		{
			ISystem* system = addSystem<TComp>();
			system->registerComponent(_pComp);
		}

	private:
		template <class TComp>
		ISystem* addSystem()				// Add a new system of type TComp
		{
			std::type_index typeId = typeid(TComp);

			if (!HasSystem<TComp>())
				m_SystemList.push_back(SystemListPair(typeId, std::make_unique<ISystem>()));

			ISystem* system = m_SystemList.back().second.get();
			system->m_SystemID = m_NextSystemIDCounter++;

			return system;
		}

		template <class TComp>
		void releaseSystem()				// Release system of type TComp
		{
			SystemListItr itr = m_SystemList.find(typeid(TComp));
			if (itr != m_SystemList.end())
				m_SystemList.erase(itr);
		}
		void releaseAllSystems();			// Release all systems in the list
	public:
		//==========================================
		//	getter
		//==========================================
		template <class TComp>
		ISystem* GetSystem() const
		{
			auto itr = std::find_if(m_SystemList.begin(), m_SystemList.end(),
				[](const SystemListPair& element) { return element.first == typeid(TComp); });
			return (itr == m_SystemList.end()) ? nullptr : *itr;
		}
		//==========================================
		//	setter
		//==========================================

	private:
		//==========================================
		//	constructor/destructor
		//==========================================
		SystemManager(IApplication* _app); // TO DO
		~SystemManager();				   // TO DO
	};

	//====================================================================================
	//	Explicit specialization declaration
	//====================================================================================
	template <>
	void SystemManager::RegisterComponent<Transform>(Transform* _pComp);	// Register a component

	template <>
	ISystem* SystemManager::addSystem<Transform>();

	template <>
	bool SystemManager::HasSystem<Transform>() const;

	//====================================================================================
	//	TransformSystem: 
	//====================================================================================
	class TransformSystem : public ISystem
	{
		friend class Transform;
		friend class SystemManager;
		//==========================================
		//	memeber/variable
		//==========================================
	protected:
		static Transform* s_pRoot;

	public:
		//==========================================
		//	procedure
		//==========================================
		virtual void EarlyUpdate();

		//==========================================
		//	getter/setter
		//==========================================
		static Transform* GetRoot();
	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		TransformSystem();
		~TransformSystem();
	};
}