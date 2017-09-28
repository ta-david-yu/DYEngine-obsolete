#pragma once

#include <DYEngine\interfaces\IComponent.h>
#include <DYEngine\System.h>

namespace DYE
{

	class IComponent;

	class Renderer : public IComponent
	{
		friend class ISystem;
		//==========================================
		//	procedure
		//==========================================
	protected: 
		virtual void registerRenderUnit();		// call by RendererSystem, to register renderUnit to Scene RenderUnitList.
	};
}