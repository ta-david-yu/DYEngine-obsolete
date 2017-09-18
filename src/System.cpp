#include <DYEngine\System.h>

#include <cassert>

namespace DYE
{
	void ISystem::registerComponent(IComponent* _pComp)
	{
		m_ComponentsList.insert(ComponentMapPair(_pComp->GetInstanceID(), _pComp));
		_pComp->m_pSystem = this;
	}
	void ISystem::unregisterComponent(IComponent* _pComp)
	{
		m_ComponentsList.erase(_pComp->GetInstanceID());
		_pComp->m_pSystem = nullptr;
	}


	SystemManager* SystemManager::s_pInstance = nullptr;

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
		for (auto const &sysPair : m_SystemMap)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->Awake();
		}
	}

	void SystemManager::Start()
	{
		for (auto const &sysPair : m_SystemMap)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->Start();
		}
	}

	void SystemManager::Update()
	{
		for (auto const &sysPair : m_SystemMap)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->Update();
		}
	}

	void SystemManager::LateUpdate()
	{
		for (auto const &sysPair : m_SystemMap)
		{
			auto const &id = sysPair.first;
			auto const &sys = sysPair.second;

			sys->LateUpdate();
		}
	}

	void SystemManager::releaseAllSystems()
	{
		m_SystemMap.clear();
	}
}