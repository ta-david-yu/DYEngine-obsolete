#pragma once

#include <DYEngine/Core.h>

#include <DYEngine/utilities/Rect.h>
#include <DYEngine/interfaces/IComponent.h>

namespace DYE
{
	//====================================================================================
	//	Shader: Managed by Shader Program, have many types
	//====================================================================================
	class DYE_API Camera : public IComponent
	{
	public:
		DYE_COMPONENT_TOSTRING

		enum Projection
		{
			Perspective,
			Orthographic
		};
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		Projection m_ProjectionType = Projection::Orthographic;
		float m_Size = 5.0f;
		float m_FieldOfView = 60.0f;
		float m_NearZ = 0.3f;
		float m_FarZ = 1000.0f;
		float m_Depth = -1;
		// TODO: Add render target RenderTexture* TargetTexture = null, or TargetWindow / Display
		Rect m_ViewportRect = Rect(0, 0, 1, 1);

		//==========================================
		//	method
		//==========================================
		//==========================================
		//	getter
		//==========================================
	public:
		inline float GetOrthographicSize() const { return m_Size; }
		inline float GetFieldOfView() const { return m_FieldOfView; }
		inline float GetNearZ() const { return m_NearZ; }
		inline float GetFarZ() const { return m_FarZ; }
		inline float GetDepth() const { return m_Depth; }
		inline bool IsOrthographic() const { return m_ProjectionType == Projection::Orthographic; }

		inline Rect& GetRect() { return m_ViewportRect; }

		//==========================================
		//	setter
		//==========================================
	public:
		inline void SetOrthographicSize(float value) { m_Size = value; }
		inline void SetFieldOfView(float value) { m_FieldOfView = value; }
		inline void SetNearZ(float value) { m_NearZ = value; }
		inline void SetFarZ(float value) { m_FarZ = value; }
		inline void SetDepth(float value) { m_Depth = value; }

		//==========================================
		//	constructor/destructor
		//==========================================
	};
}