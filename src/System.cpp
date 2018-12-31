#include <DYEngine/System.h>

#include <DYEngine/graphics/RendererSystem.h>
#include <DYEngine/graphics/Renderer.h>

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
		for (auto const& comp : m_ComponentsList)
		{
			IComponent* ptr = comp.second;
			if (ptr->IsEnabled())
			{
				ptr->Awake();
			}
		}
	}

	void ISystem::Start() 
	{
		for (auto const& comp : m_ComponentsList)
		{
			IComponent* ptr = comp.second;
			if (ptr->IsEnabled())
			{
				ptr->Start();
			}
		}
	}

	void ISystem::EarlyUpdate() 
	{
		for (auto const& comp : m_ComponentsList)
		{
			IComponent* ptr = comp.second;
			if (ptr->IsEnabled())
			{
				ptr->EarlyUpdate();
			}
		}
	}

	void ISystem::Update() 
	{
		for (auto const& comp : m_ComponentsList)
		{
			IComponent* ptr = comp.second;
			if (ptr->IsEnabled())
			{
				ptr->Update();
			}
		}
	}

	void ISystem::LateUpdate() 
	{
		for (auto const& comp : m_ComponentsList)
		{
			IComponent* ptr = comp.second;
			if (ptr->IsEnabled())
			{
				ptr->LateUpdate();
			}
		}
	}

	void ISystem::FixedUpdate() 
	{
		for (auto const& comp : m_ComponentsList)
		{
			IComponent* ptr = comp.second;
			if (ptr->IsEnabled())
			{
				ptr->FixedUpdate();
			}
		}
	}

	//====================================================================================
	//	SystemManager: manage all components
	//====================================================================================
	void SystemManager::Init()
	{
		// init transform system
		m_uniqueTransformSystem = std::make_unique<TransformSystem>();
		m_pTransformSystem = m_uniqueTransformSystem.get();

		// init graphics system
		m_uniqueRendererSystem = std::make_unique<RendererSystem>();
		m_pRendererSystem = m_uniqueRendererSystem.get();

		// UNDONE: init other specialized systems

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

	void SystemManager::RegisterRenderer()
	{
		m_pRendererSystem->RegisterRenderer();
	}

	void SystemManager::releaseAllSystems()
	{
		m_SystemList.clear();
	}

	SystemManager::SystemManager() :
		m_NextSystemIDCounter(0), 

		m_pTransformSystem(nullptr),
		m_pRendererSystem(nullptr)	// TODO: add more system init
	{
	}

	SystemManager::~SystemManager()
	{
	}

	//====================================================================================
	//	RegisterComponent: Explicit Specialization
	//====================================================================================
	template <>
	void SystemManager::RegisterComponent<Transform>(Transform* _pComp)
	{
		ISystem* system = m_pTransformSystem;
		system->registerComponent(_pComp);

		// set every transform's parent to Root
		_pComp->SetParent(TransformSystem::GetRoot());
	}

	template <>
	void SystemManager::RegisterComponent<Renderer>(Renderer* _pComp)
	{
		ISystem* system = m_pRendererSystem;
		system->registerComponent(_pComp);
	}

	//====================================================================================
	//	HasSystem: Explicit Specialization
	//====================================================================================
	template <>
	bool SystemManager::HasSystem<Transform>() const
	{
		return true;
	}

	template <>
	bool SystemManager::HasSystem<Renderer>() const
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