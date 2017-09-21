#include <DYEngine\System.h>

#include <cassert>
#include <algorithm>

namespace DYE
{
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
		for (auto const &sysPair : m_SystemList)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->Awake();
		}
	}

	void SystemManager::Start()
	{
		for (auto const &sysPair : m_SystemList)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->Start();
		}
	}

	void SystemManager::Update()
	{
		printf("UPDATE\n");
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
}