#include <DYEngine\graphics\MaterialAttribute.h>

namespace DYE
{
	RenderPass::RenderPass()
	{

	}

	RenderPass::~RenderPass()
	{
		for (auto const& uniform : Uniforms)
		{
			delete uniform;
		}
	}
}