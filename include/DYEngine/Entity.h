#pragma once

#include <DYEngine\Main.h>

#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <string>

#define DEFAULT_NAME ""

namespace DYE
{
	class Base;
	class IComponent;
	class Transform;
	class ISystem;
	class SystemManager;
	class Scene;

	//====================================================================================
	//	Entity: Base Entity class as game object
	//====================================================================================
	class Entity : public Base
	{
		friend IComponent;
		friend Scene;
	public:
		typedef std::pair<InstanceID, std::unique_ptr<IComponent>> ComponentListPair;
		typedef std::vector<ComponentListPair> ComponentList;
		typedef ComponentList::iterator ComponentItr;
		typedef ComponentList::const_iterator ComponentConstItr;

	protected:
		//==========================================
		//	memeber/variable
		//==========================================
		Scene* m_pScene;
		Transform* m_pTransform;
		ComponentList m_Components;
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
	private:
		void removeComponent(InstanceID _id);				// called by component release (Destroy)
	public:
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
			
			m_Components.push_back(ComponentListPair(ptr->GetInstanceID(), std::move(uniPtr)));
			//m_Components.insert( std::pair<std::type_index, std::unique_ptr<TComp>>(typeId, std::move(uniPtr)) );

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
		TComp* GetComponent() const
		{
			for (auto const& comp : m_Components)
			{
				TComp* _ret = dynamic_cast<TComp*>(comp.second.get());
				if (_ret != nullptr)
					return _ret;
			}
			return nullptr;
		}
		//==========================================
		//	setter
		//==========================================

	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		Entity(Scene* _scene = nullptr, const std::string& _name = DEFAULT_NAME);						// Initialize with a tranform component
		~Entity();
	};
}