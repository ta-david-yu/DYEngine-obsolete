#pragma once

#include <DYEngine\Resource.h>
#include <DYEngine\graphics\MaterialAttribute.h>

#include <vector>

namespace DYE
{

	using RenderOrder = unsigned;

	class ShaderProgram;

	//====================================================================================
	//	Material: material file
	//====================================================================================
	class Material : public IResourceValue
	{

	public:
		friend class Resource<Material>;
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		RenderOrder m_RenderOrder = 1000;
		std::vector<RenderPass> m_RenderPasses;
		
		//==========================================
		//	method
		//==========================================
	protected:
		bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr);
		//==========================================
		//	getter
		//==========================================

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
		~Material();									// unload each shader program for passes
	};
}