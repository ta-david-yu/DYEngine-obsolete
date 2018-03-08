#include <DYEngine\Entity.h>

#include <DYEngine\graphics\Renderer.h>
#include <DYEngine\graphics\SpriteRenderer.h>
#include <DYEngine\graphics\MeshRenderer.h>
#include <DYEngine\utilities\Logger.h>

#include <type_traits>

#define ACTIVE_SIGN "[@]"
#define INACTIVE_SIGN "[ ]"
#define SHOW_LOCAL_ENABLE true

namespace DYE
{
	//====================================================================================
	//	Entity: Base Entity class as game object
	//====================================================================================

	bool Entity::IsActive() const
	{
		return GetTransform()->IsEnabled();
	}

	void Entity::SetActive(bool set)
	{
		GetTransform()->m_IsLocalEnabled = set;
		GetTransform()->m_IsDirtyLocalEnabled = true;
	}

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

	Entity::Entity(IScene* _scene, const std::string& _name)
	{
		m_pTransform = this->AddComponent<Transform>();
		m_pTransform->Init();
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
		std::string activeSign;

		if (SHOW_LOCAL_ENABLE)
			activeSign = (GetTransform()->m_IsLocalEnabled) ? ACTIVE_SIGN : INACTIVE_SIGN;
		else
			activeSign = (IsActive()) ? ACTIVE_SIGN : INACTIVE_SIGN;

		ret += activeSign + prefix + "____" + "(" + std::to_string(GetInstanceID()) + ") " + this->GetName() + "\n";

		// print component list
		if (SHOW_LOCAL_ENABLE)
			activeSign = (GetTransform()->m_IsLocalEnabled) ? ACTIVE_SIGN : INACTIVE_SIGN;
		else
			activeSign = (IsActive()) ? ACTIVE_SIGN : INACTIVE_SIGN;

		ret += activeSign + prefix + "________" + "(" + std::to_string(this->GetTransform()->GetInstanceID()) + ") " + this->GetTransform()->ToString() + "\n";
		for (auto const& comp : this->m_Components)
		{
			if (SHOW_LOCAL_ENABLE)
				activeSign = (comp.second->m_IsEnabled) ? ACTIVE_SIGN : INACTIVE_SIGN;
			else
				activeSign = (comp.second->IsEnabled())? ACTIVE_SIGN : INACTIVE_SIGN;
			ret += activeSign + prefix + "________" + "(" + std::to_string(comp.second->GetInstanceID()) + ") " + comp.second->ToString() + "\n";
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
		// TODO: set other states (layers, tags...), (evil)
		this->GetTransform()->copyFrom(other->GetTransform());	// copy transform state
		for (auto const& comp : other->m_Components)			// copy component state
		{
			// add comp, copy comp
			/*
			using ComponentType = std::remove_reference_t< decltype(comp.second.get()->DynamicCast()) >;

			printf("copying component %s\n", typeid(ComponentType).name());
			ComponentType* newComp = this->AddComponent<ComponentType>();
			newComp->copyFrom(dynamic_cast<ComponentType*>(comp.second.get()));
			*/
		}
	}

	IComponent* Entity::AddComponent(IComponent* comp)
	{
		IComponent* clone = comp->clone();
		clone->AttachTo(this);

		// TODO: evil
		// SystemManager
		// std::unique_ptr<IComponent> uniPtr{ new IComp }

		assert(false);
		return nullptr;
	}

	//====================================================================================
	//	AddComponent: Explicit Specialization
	//====================================================================================
	template <>
	IComponent* Entity::AddComponent<IComponent>()
	{
		LogError("Adding illegal component");
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

		m_uniqueTransform = std::move(uniPtr);
		// m_Components.push_back(ComponentListPair(ptr->GetInstanceID(), std::move(uniPtr)));
		//m_Components.insert( std::pair<std::type_index, std::unique_ptr<TComp>>(typeId, std::move(uniPtr)) );

		return ptr;
	}

	template <>
	Renderer* Entity::AddComponent<Renderer>()
	{
		// Create unique component ptr and initialize
		std::unique_ptr<Renderer> uniPtr = std::make_unique<Renderer>();
		Renderer* ptr = uniPtr.get();

		ptr->AttachTo(this);

		// Insert component ptr to system list
		SystemManager::GetInstance()->RegisterComponent<Renderer>(ptr);

		return ptr;
	}

	template <>
	MeshRenderer* Entity::AddComponent<MeshRenderer>()
	{
		// Create unique component ptr and initialize
		std::unique_ptr<MeshRenderer> uniPtr = std::make_unique<MeshRenderer>();
		MeshRenderer* ptr = uniPtr.get();

		ptr->AttachTo(this);

		// Insert component ptr to system list
		SystemManager::GetInstance()->RegisterComponent<Renderer>(ptr);

		return ptr;
	}

	template <>
	SpriteRenderer* Entity::AddComponent<SpriteRenderer>()
	{
		// Create unique component ptr and initialize
		std::unique_ptr<SpriteRenderer> uniPtr = std::make_unique<SpriteRenderer>();
		SpriteRenderer* ptr = uniPtr.get();

		ptr->AttachTo(this);

		// Insert component ptr to system list
		SystemManager::GetInstance()->RegisterComponent<Renderer>(ptr);

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