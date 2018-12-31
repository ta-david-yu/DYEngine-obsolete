#pragma once

#include <DYEngine/graphics/Renderer.h>

namespace DYE
{
	class Renderer;

	//====================================================================================
	//	SpriteRenderer: 3d renderer component, take a material, drawn as rect
	//====================================================================================
	class SpriteRenderer : public Renderer
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
		void SetSprite();
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
		SpriteRenderer();
		~SpriteRenderer();
		
	};
}