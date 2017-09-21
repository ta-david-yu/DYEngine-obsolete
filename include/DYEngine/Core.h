#pragma once

#include <DYEngine\Main.h>

#define CORE Core::GetInstance()

namespace DYE
{
	class IApplication;
	//====================================================================================
	//	Core: core class for managing scenes and systems
	//====================================================================================
	class Core
	{
		friend class IApplication;
	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static Core* s_pInstance;
		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================
	public:
		void Init();
		//==========================================
		//	method
		//==========================================
		static Core* GetInstance();
	private:
		Scene* createScene();
		//==========================================
		//	getter
		//==========================================

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	private:
		Core();
		~Core();
	};
}