#include <DYEngine\Core.h>

#include <cassert>
#include <memory>

namespace DYE
{
	Core* Core::s_pInstance = nullptr;

	void Core::init()
	{
		m_pSceneManager = new SceneManager(m_pApplication);
		m_pSceneManager->init();
		m_pSystemManager = new SystemManager(m_pApplication);
		m_pSystemManager->init();
	}

	Core::Core(IApplication* app) : m_pApplication(app)
	{
		if (s_pInstance == nullptr)
			s_pInstance = this;
	}

	Core::~Core()
	{
		if (s_pInstance == this)
			s_pInstance = nullptr;
	}

	Core* Core::GetInstance()
	{
		assert(s_pInstance != nullptr);
		return s_pInstance;
	}
}