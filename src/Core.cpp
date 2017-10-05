#include <DYEngine\Core.h>

#include <cassert>
#include <memory>

namespace DYE
{
	Core* Core::s_pInstance = nullptr;

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
		// assert(s_pInstance != nullptr);
		return s_pInstance;
	}

	IScene* Core::loadScene(SceneID id)
	{
		IScene* currScene = getScene(m_CurrSceneID);
		if (currScene->IsLoaded())
			currScene->release();

		IScene* nextScene = getScene(id);
		nextScene->load();

		m_CurrSceneID = id;

		return nextScene;
	}

	IScene* Core::getScene(SceneID id) const
	{
		assert(id < m_SceneIDCounter);

		return m_Scenes[id].second.get();
	}
}