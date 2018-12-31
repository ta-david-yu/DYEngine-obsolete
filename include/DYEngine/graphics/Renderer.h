#pragma once

#include <DYEngine/interfaces/IComponent.h>

namespace DYE
{

	//====================================================================================
	//	Renderer: basic renderer component
	//====================================================================================
	class Renderer : public IComponent
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