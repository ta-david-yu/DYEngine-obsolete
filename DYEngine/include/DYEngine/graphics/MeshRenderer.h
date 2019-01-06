#pragma once

#include "DYEngine/Core.h"

#include "DYEngine/graphics/Renderer.h"

namespace DYE
{
	class Renderer;

	//====================================================================================
	//	MeshRenderer: 3d renderer component, take a mesh and a material
	//====================================================================================
	class DYE_API MeshRenderer : public Renderer
	{
	public:
		DYE_COMPONENT_TOSTRING
	protected:
		//==========================================
		//	procedure
		//==========================================
		virtual void Init();
		virtual void RegisterRenderer();
		//==========================================
		//	method
		//==========================================
		//==========================================
		//	getter
		//==========================================
		//==========================================
		//	setter
		//==========================================
		//==========================================
		//	opeartor
		//==========================================
	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		MeshRenderer();
		~MeshRenderer();
	};
}