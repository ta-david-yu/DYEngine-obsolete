#pragma once

#include <DYEngine/Core.h>

#include <DYEngine/interfaces/IComponent.h>

namespace DYE
{

	//====================================================================================
	//	Renderer: basic renderer component
	//====================================================================================
	class DYE_API Renderer : public IComponent
	{
	public:
		// must added macro
		DYE_COMPONENT_TOSTRING

			friend class RendererSystem;
		//==========================================
		//	procedure
		//==========================================
	protected:
		virtual void RegisterRenderer();		// call by RendererSystem, to register renderUnit to Scene RenderUnitList.
		virtual void Init();
		virtual void Update();
	};
}