#pragma once

#include <DYEngine\interfaces\IComponent.h>

namespace DYE
{
	class NonCopyable;
	class Base;
	class IComponent;

	class SpriteComponent : public IComponent
	{		
		// TO DO:
		//==========================================
		//	memeber/variable
		//==========================================
		//==========================================
		//	procedure
		//==========================================
		virtual void Init();

		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();

		// Call by Event
		virtual void OnEnable();
		virtual void OnDisable();
		virtual void OnDestroy();
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
		//==========================================
		//	constructor/destructor
		//==========================================
		SpriteComponent();
		~SpriteComponent();
		
	};
}