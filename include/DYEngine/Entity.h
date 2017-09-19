#pragma once

#include <DYEngine\Main.h>

#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <string>

namespace DYE
{
	class Base;
	class IComponent;
	class Transform;
	class ISystem;
	class SystemManager;

	//====================================================================================
	//	Entity: Base Entity class as game object
	//====================================================================================
	class Entity : public Base
	{
	public:
		typedef std::multimap<std::type_index, std::unique_ptr<IComponent>> ComponentMap;
		typedef ComponentMap::iterator ComponentMapItr;
		typedef ComponentMap::const_iterator ComponentMapConstItr;

	protected:
		//==========================================
		//	memeber/variable
		//==========================================
		ComponentMap m_Components;
		Transform* m_Transform;
		//==========================================
		//	flag
		//==========================================
		bool m_IsActive;
	public:
		//==========================================
		//	procedure
		//==========================================

		//==========================================
		//	method
		//==========================================
		template <class TComp>
		TComp* AddComponent()
		{
			// Create unique component ptr and initialize
			std::unique_ptr<TComp> uniPtr = std::make_unique<TComp>();
			TComp* ptr = uniPtr.get();

			ptr->AttachTo(this);

			// Insert component ptr to system list
			SystemManager::GetInstance()->RegisterComponent<TComp>(ptr);

			// Move unique component ptr to object list
			std::type_index typeId = typeid(TComp);
			m_Components.insert( std::pair<std::type_index, std::unique_ptr<TComp>>(typeId, std::move(uniPtr)) );

			return ptr;
		}
	protected:
		void release() override;
		//==========================================
		//	getter
		//==========================================
	public:
		Transform* GetTransform() const;

		template <class TComp>
		TComp* GetComponent() const										// TO DO: use dynamic cast
		{
			ComponentMapConstItr itr = m_Components.find(typeid(TComp));
			if (itr == m_Components.end())
				return nullptr;
			else
				return dynamic_cast<TComp*>( itr->second.get() );
		}
		//==========================================
		//	setter
		//==========================================

	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		Entity();							// Initialize with a tranform component
		Entity(const std::string& _name);
		~Entity();
	};
}