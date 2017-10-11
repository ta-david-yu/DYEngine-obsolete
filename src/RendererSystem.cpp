#include <DYEngine\graphics\RendererSystem.h>
#include <DYEngine\graphics\Renderer.h>

namespace DYE
{
	void RendererSystem::RegisterRenderer()
	{
		for (auto const& comp : m_ComponentsList)
		{
			Renderer* renderer = static_cast<Renderer*>(comp.second);
			if (renderer->IsEnabled())
			{
				renderer->RegisterRenderer();
			}
		}
	}
}