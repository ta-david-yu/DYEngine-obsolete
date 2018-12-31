#pragma once

#include <DYEngine/Resource.h>
#include <DYEngine/utilities/Math.h>
#include <DYEngine/graphics/RenderUnit.h>

namespace DYE
{
	//====================================================================================
	//	Mesh: vertices, normals, faces
	//====================================================================================
	class Mesh : public IResourceValue
	{
		friend class Resource<Mesh>;
		friend struct RenderUnit;
	public:
		DYE_RESOURCE_PATH("mesh/");
		//==========================================
		//	memeber/variable
		//==========================================
	protected:
		std::vector<Vector3f> m_Vertices;
		std::vector<Vector3f> m_Normals;
		std::vector<Vector3f> m_Colors;
		std::vector<Vector2f> m_UVCoords;
		std::vector<uint32_t> m_Triangles;
	protected:
		bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) override; // TO DO:
		//==========================================
		//	flag
		//==========================================

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
		//	constructor/destructor
		//==========================================
	};
}