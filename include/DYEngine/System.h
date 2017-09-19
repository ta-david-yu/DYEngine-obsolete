#pragma once

#include <DYEngine\Main.h>

#include <vector>
#include <list>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>

#define SYSTEM_MGR DYE::SystemManager::GetInstance()

namespace DYE
{
	class Entity;
	class IComponent;
	class SystemManager;

	//====================================================================================
	//	ISystem: manage all components
	//====================================================================================
	class ISystem
	{
		friend class IComponent;
		friend class SystemManager;
	public:
		typedef std::map<int, IComponent*> ComponentMap;
		typedef std::pair<int, IComponent*> ComponentMapPair;

	protected:
		//==========================================
		//	memeber/variable
		//==========================================
		ComponentMap m_ComponentsList;
	public:
		//==========================================
		//	procedure
		//==========================================
		// Run through each component in the list
		// TO DO: reimplement
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		//==========================================
		//	method
		//==========================================
	private:
		void registerComponent(IComponent* _pComp);
		void unregisterComponent(IComponent* _pComp);
	protected:
	public: // temp TO DO:
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
	public:
		typedef std::map<std::type_index, std::unique_ptr<ISystem>> SystemMap;
		typedef SystemMap::iterator SystemMapItr;
		typedef SystemMap::const_iterator SystemMapConstItr;

	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static SystemManager* s_pInstance;
		SystemMap m_SystemMap;

	public:
		static SystemManager* GetInstance();
		//==========================================
		//	procedure
		//==========================================
		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();

		virtual void FixedUpdate() {}	// TO DO: to be implement

		//==========================================
		//	method
		//==========================================
		template <class TComp>
		bool HasSystem() const				// Return true if system of type TComp has already been added
		{
			return !(m_SystemMap.find(typeid(TComp)) == m_SystemMap.end());
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
				m_SystemMap.insert(std::pair<std::type_index, std::unique_ptr<ISystem>>(typeId, std::make_unique<ISystem>()));

			return m_SystemMap[typeId].get();
		}

		template <class TComp>
		void releaseSystem()				// Release system of type TComp
		{
			SystemMapItr itr = m_SystemMap.find(typeid(TComp));
			if (itr != m_SystemMap.end())
				m_SystemMap.erase(itr);
		}
		void releaseAllSystems();			// Release all systems in the list
	public:
		//==========================================
		//	getter
		//==========================================
		template <class TComp>
		ISystem* GetSystem() const
		{
			SystemMapConstItr itr = m_SystemMap.find(typeid(TComp));
			if (itr == m_SystemMap.end())
				return nullptr;
			else
				return itr->second.get();
		}
		//==========================================
		//	setter
		//==========================================

	private:
		//==========================================
		//	constructor/destructor
		//==========================================
		SystemManager() {} // TO DO
		~SystemManager() {} // TO DO
	};
}