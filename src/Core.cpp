#include <DYEngine\Core.h>

#include <cassert>

namespace DYE
{
	Core* Core::s_pInstance = nullptr;

	Core::Core(IApp* app) : m_pApplication(app)
	{
		if (s_pInstance != nullptr)
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