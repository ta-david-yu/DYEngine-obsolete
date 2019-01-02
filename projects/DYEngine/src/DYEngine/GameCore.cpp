#include <DYEngine/GameCore.h>

#include <cassert>
#include <memory>

namespace DYE
{
	GameCore* GameCore::s_pInstance = nullptr;

	void GameCore::Init()
	{
		m_pSceneManager = new SceneManager();
		m_pSceneManager->Init();
		m_pSystemManager = new SystemManager();
		m_pSystemManager->Init();
	}

	GameCore::GameCore(IApplication* app) : m_pApplication(app)
	{
		if (s_pInstance == nullptr)
			s_pInstance = this;
	}

	GameCore::~GameCore()
	{
		if (s_pInstance == this)
			s_pInstance = nullptr;
	}

	GameCore* GameCore::GetInstance()
	{
		assert(s_pInstance != nullptr);
		return s_pInstance;
	}

	SystemManager* GameCore::GetSystemManager() const
	{
		return m_pSystemManager;
	}

	SceneManager* GameCore::GetSceneManager() const
	{
		return m_pSceneManager;
	}
}