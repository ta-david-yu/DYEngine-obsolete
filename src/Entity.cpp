#include <DYEngine\Entity.h>

#include <type_traits>

namespace DYE
{
	//====================================================================================
	//	Entity: Base Entity class as game object
	//====================================================================================

	Transform* Entity::GetTransform() const
	{
		return this->m_pTransform;
	}

	void Entity::release()								// called by  (Destroy Loop)
	{
		m_pScene->removeEntity(GetInstanceID());
	}

	void Entity::removeComponent(InstanceID _id)
	{
		auto itr = std::find_if(m_Components.begin(), m_Components.end(),
			[_id](const ComponentListPair& element) { return element.first == _id; });

		if (itr != m_Components.end())
		{
			itr->second.reset();		// release entity
			m_Components.erase(itr);	// erase entry
		}
	}

	Entity::Entity(Scene* _scene, const std::string& _name)
	{
		m_pTransform = this->AddComponent<Transform>();
		m_pScene = _scene;
		SetName(_name);
	}

	Entity::~Entity()
	{

	}

	std::string Entity::ToString() const
	{
		return toStringSuccessor("");
	}

	std::string Entity::toStringSuccessor(std::string prefix) const
	{
		std::string ret;

		ret += prefix + "____(" + std::to_string(GetInstanceID()) + ") " + this->GetName() + "\n";

		// print component list
		ret += prefix + "________(" + std::to_string(this->GetTransform()->GetInstanceID()) + ") " + this->GetTransform()->ToString() + "\n";
		for (auto const& comp : this->m_Components)
		{
			ret += prefix + "________(" + std::to_string(comp.second->GetInstanceID()) + ") " + comp.second->ToString() + "\n";
		}

		// print children
		for (auto const& child : this->GetTransform()->m_ChildrenList)
		{
			ret += child->GetEntity()->toStringSuccessor(prefix + "__");
		}

		return ret;
	}

	void Entity::copyFrom(const Entity* other)
	{
		// TO DO: set other states (layers, tags...)
		this->m_IsActive = other->m_IsActive;					// copy state flag
		this->GetTransform()->copyFrom(other->GetTransform());	// copy transform state
		for (auto const& comp : other->m_Components)			// copy component state
		{
			// TO DO: fix auto dynamic type casting
			/*
			// add comp, copy comp
			using ComponentType = std::remove_reference_t< decltype(comp.second.get()->DynamicCast()) >;

			printf("copying component %s\n", typeid(ComponentType).name());
			ComponentType* newComp = this->AddComponent<ComponentType>();
			newComp->copyFrom(dynamic_cast<ComponentType*>(comp.second.get()));
			*/
		}
	}

	//====================================================================================
	//	AddComponent: Explicit Specialization
	//====================================================================================
	template <>
	IComponent* Entity::AddComponent<IComponent>()
	{
		// TO DO: error log
		printf("ADDING ILLEGAL COMPONENT\n");
		assert(false);
		return nullptr;
	}

	template <>
	Transform* Entity::AddComponent<Transform>()
	{
		// Create unique component ptr and initialize
		std::unique_ptr<Transform> uniPtr = std::make_unique<Transform>();
		Transform* ptr = uniPtr.get();

		ptr->AttachTo(this);

		// Insert component ptr to system list
		SystemManager::GetInstance()->RegisterComponent<Transform>(ptr);

		// Move unique component ptr to object list
		std::type_index typeId = typeid(Transform);

		m_uniqueTransform = std::move(uniPtr);
		// m_Components.push_back(ComponentListPair(ptr->GetInstanceID(), std::move(uniPtr)));
		//m_Components.insert( std::pair<std::type_index, std::unique_ptr<TComp>>(typeId, std::move(uniPtr)) );

		return ptr;
	}

	//====================================================================================
	//	GetComponent: Explicit Specialization
	//====================================================================================
	template <>
	Transform* Entity::GetComponent<Transform>() const
	{
		return m_pTransform;
	}
}