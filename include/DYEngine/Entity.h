#pragma once

#include <DYEngine\Base.h>
#include <DYEngine\interfaces\IComponent.h>
#include <DYEngine\System.h>
#include <DYEngine\Scene.h>

#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <string>

#define DEFAULT_NAME "ENTITY_NAME"

namespace DYE
{
	class Base;
	class IComponent;
	class Transform;
	class ISystem;
	class SystemManager;
	class IScene;
	class Renderer;
	class SpriteRenderer;
	class MeshRenderer;

	//====================================================================================
	//	Entity: Base Entity class as game object
	//====================================================================================
	class Entity : public Base
	{
		friend class IComponent;
		friend class IScene;
		friend class Base;
	public:
		using ComponentListPair = std::pair<InstanceID, std::unique_ptr<IComponent>>;
		using ComponentList = std::vector<ComponentListPair>;
		using ComponentItr = ComponentList::iterator;
		using ComponentConstItr = ComponentList::const_iterator;

	protected:
		//==========================================
		//	memeber/variable
		//==========================================
		IScene* m_pScene;
		Transform* m_pTransform;
		ComponentList m_Components;
		std::unique_ptr<Transform> m_uniqueTransform;
		//==========================================
		//	flag
		//==========================================
	public:
		//==========================================
		//	procedure
		//==========================================

		//==========================================
		//	method
		//==========================================
	public:
		std::string ToString() const;						// print scene graph including component
	private:
		std::string toStringSuccessor(std::string prefix) const;
	protected:
		virtual void copyFrom(const Entity* other);
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

		IComponent* AddComponent(IComponent* comp);		// copy a same component from the input, TO DO
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
		bool IsActive() const;
		//==========================================
		//	setter
		//==========================================
		void SetActive(bool set);

	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		Entity(IScene* _scene = nullptr, const std::string& _name = DEFAULT_NAME);						// Initialize with a tranform component
		~Entity();
	};

	//====================================================================================
	//	Explicit specialization declaration
	//====================================================================================

	template <>
	IComponent* Entity::AddComponent<IComponent>();

	template <>
	Transform* Entity::AddComponent<Transform>();

	template <>
	Renderer* Entity::AddComponent<Renderer>();

	template <>
	MeshRenderer* Entity::AddComponent<MeshRenderer>();

	template <>
	SpriteRenderer* Entity::AddComponent<SpriteRenderer>();

	template <>
	Transform* Entity::GetComponent<Transform>() const;

}