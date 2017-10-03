#include <DYEngine\System.h>

#include <cassert>
#include <algorithm>
#include <queue>

namespace DYE
{
	//====================================================================================
	//	ISystem: manage all components
	//====================================================================================
	void ISystem::registerComponent(IComponent* _pComp)
	{
		m_ComponentsList.push_back(ComponentListPair(_pComp->GetInstanceID(), _pComp));
		_pComp->m_pSystem = this;
	}

	void ISystem::unregisterComponent(IComponent* _pComp)
	{
		InstanceID id = _pComp->GetInstanceID();
		auto itr = std::find_if(m_ComponentsList.begin(), m_ComponentsList.end(),
			[id](const ComponentListPair& element) { return element.first == id; });

		if (itr != m_ComponentsList.end())
			m_ComponentsList.erase(itr);

		_pComp->m_pSystem = nullptr;
	}


	void ISystem::Awake() 
	{
		// TO DO:
		for (auto const& comp : m_ComponentsList)
		{
			IComponent* ptr = comp.second;
			// if (ptr->Get)
		}
	}

	void ISystem::Start() 
	{

	}

	void ISystem::EarlyUpdate() 
	{

	}

	void ISystem::Update() 
	{

	}

	void ISystem::LateUpdate() 
	{

	}

	void ISystem::FixedUpdate() 
	{
	
	}

	//====================================================================================
	//	SystemManager: manage all components
	//====================================================================================
	SystemManager* SystemManager::s_pInstance = nullptr;
	std::size_t SystemManager::s_nextSystemID = 0;

	SystemManager* SystemManager::GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new SystemManager();
		}
		assert(s_pInstance != nullptr);
		return s_pInstance;
	}

	void SystemManager::Awake()
	{
		m_pTransformSystem->Awake();

		for (auto const &sysPair : m_SystemList)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->Awake();
		}
	}

	void SystemManager::Start()
	{
		m_pTransformSystem->Start();

		for (auto const &sysPair : m_SystemList)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->Start();
		}
	}

	void SystemManager::EarlyUpdate()
	{
		m_pTransformSystem->EarlyUpdate();

		for (auto const &sysPair : m_SystemList)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->EarlyUpdate();
		}
	}

	void SystemManager::Update()
	{
		for (auto const &sysPair : m_SystemList)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->Update();
		}
	}

	void SystemManager::LateUpdate()
	{
		for (auto const &sysPair : m_SystemList)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->LateUpdate();
		}
	}

	void SystemManager::FixedUpdate()
	{
		m_pTransformSystem->FixedUpdate();

		for (auto const &sysPair : m_SystemList)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->FixedUpdate();
		}
	}

	void SystemManager::releaseAllSystems()
	{
		m_SystemList.clear();
	}

	SystemManager::SystemManager()
	{
		m_pTransformSystem = nullptr;
	}

	//====================================================================================
	//	RegisterComponent: Explicit Specialization
	//====================================================================================
	template <>
	void SystemManager::RegisterComponent<Transform>(Transform* _pComp)
	{
		ISystem* system = addSystem<Transform>();
		system->registerComponent(_pComp);

		// set every transform's parent to Root
		_pComp->SetParent(TransformSystem::GetRoot());
	}

	//====================================================================================
	//	addSystem: Explicit Specialization
	//====================================================================================
	template<>
	ISystem* SystemManager::addSystem<Transform>()
	{
		std::type_index typeId = typeid(Transform);

		if (m_pTransformSystem == nullptr)
		{
			m_uniqueTransformSystem = std::make_unique<TransformSystem>();
			m_pTransformSystem = m_uniqueTransformSystem.get();
		}

		return m_pTransformSystem;
	}

	//====================================================================================
	//	HasSystem: Explicit Specialization
	//====================================================================================
	template <>
	bool SystemManager::HasSystem<Transform>() const
	{
		return true;
	}

	//====================================================================================
	//	TransformSystem: 
	//====================================================================================
	Transform* TransformSystem::s_pRoot = nullptr;

	Transform* TransformSystem::GetRoot()
	{
		if (s_pRoot == nullptr)
			s_pRoot = new Transform();

		return s_pRoot;
	}

	void TransformSystem::EarlyUpdate()
	{
		// update state based on dirty flag, in the order of graph (BFS)
		std::queue<Transform*> queue;
		
		queue.push(s_pRoot);

		while (!queue.empty())
		{
			Transform* curr = queue.front();				// pop
			queue.pop();

			curr->EarlyUpdate();							// deferred update

			for (auto const& child : curr->m_ChildrenList)	// push children
			{
				queue.push(child);
			}
		}
	}

	TransformSystem::TransformSystem()
	{
	}

	TransformSystem::~TransformSystem()
	{

	}
}