#pragma once

#include "DYEngine/Core.h"

#include "DYEngine/graphics/Uniform.h"

#include <vector>
#include <memory>

namespace DYE
{
	class IUniform;
	class ShaderProgram;

	//====================================================================================
	//	AttributeType: attribute types in enumerator
	//====================================================================================
	enum AttributeType
	{
		Depth = GL_DEPTH_TEST,
		Stencil = GL_STENCIL_TEST,
		Blend = GL_BLEND
	};

	enum AttribFunc
	{
		Never = GL_NEVER,
		Less = GL_LESS,
		Equal = GL_EQUAL,
		LEqual = GL_LEQUAL,
		Greater = GL_GREATER,
		NotEqual = GL_NOTEQUAL,
		GEqual = GL_GEQUAL,
		Always = GL_ALWAYS,

		ErrorFunc
	};

	//====================================================================================
	//	DepthAttribute
	//====================================================================================
	struct DYE_API DepthAttribute
	{
		bool IsEnabled = true;
		AttribFunc Func = AttribFunc::Less;
	};

	//====================================================================================
	//	StencilAttribute
	//====================================================================================
	struct DYE_API StencilAttribute
	{
		enum StencilOp
		{
			Zero = GL_ZERO,
			Keep = GL_KEEP,
			Replace = GL_REPLACE,
			Incr = GL_INCR,
			Decr = GL_DECR,
			Invert = GL_INVERT,

			ErrorOp
		};

		bool IsEnabled = false;
		AttribFunc Func = AttribFunc::Less;
		StencilOp Op = StencilOp::Replace;
		GLint Ref = 0x00000000;
		GLint Msk = 0xFFFFFFFF;
	};

	//====================================================================================
	//	BlendAttribute
	//====================================================================================
	struct DYE_API BlendAttribute
	{
		enum BlendFactor
		{
			Zero = GL_ZERO,
			One = GL_ONE,
			SrcColor = GL_SRC_COLOR,
			OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
			SrcAlpha = GL_SRC_ALPHA,
			OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
			DstAlpha = GL_DST_ALPHA,
			OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
			DstColor = GL_DST_COLOR,
			OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,

			ErrorFactor
		};

		bool IsEnabled = false;
		BlendFactor SrcFactor = BlendFactor::SrcAlpha;
		BlendFactor DstFactor = BlendFactor::OneMinusSrcAlpha;
	};

	//=========================================================================================
	//	RenderPass: representing one pass for a material. Keep shader, attributes and uniforms
	//=========================================================================================
	class DYE_API RenderPass
	{

	public:
		using UniformList = std::vector<IUniform*>;
		//==========================================
		//	memeber/variable
		//==========================================
		ShaderProgram* pProgram;

		DepthAttribute DepthAttr;
		StencilAttribute StencilAttr;
		BlendAttribute BlendAttr;

		UniformList Uniforms;

		//==========================================
		//	method
		//==========================================
		template<typename Type>
		void AddUniform(const std::string& _name, const Type& _data)
		{
			UniformVariable<Type>* ptr = new UniformVariable<Type>(_name);
			ptr->SetData(_data);

			Uniforms.push_back(ptr);

			// get uniform location from shader program.
			ptr->AttachToShader(pProgram->GetProgramID()); 
		}

		//==========================================
		//	constructor/destructor
		//==========================================
		RenderPass();
		~RenderPass();
	};

	//=========================================================================================
	//	Utilities Function
	//=========================================================================================
	inline AttribFunc StringToAttributFunc(const std::string& funcStr)
	{
		if (funcStr == "never")
			return AttribFunc::Never;
		else if (funcStr == "less")
			return AttribFunc::Less;
		else if (funcStr == "equal")
			return AttribFunc::Equal;
		else if (funcStr == "lequal")
			return AttribFunc::LEqual;
		else if (funcStr == "greater")
			return AttribFunc::Greater;
		else if (funcStr == "notequal")
			return AttribFunc::NotEqual;
		else if (funcStr == "gequal")
			return AttribFunc::GEqual;
		else if (funcStr == "always")
			return AttribFunc::Always;
		else
			return AttribFunc::ErrorFunc;
	}

	inline StencilAttribute::StencilOp StringToStencilOp(const std::string& opStr)
	{
		if (opStr == "zero")
			return StencilAttribute::StencilOp::Zero;
		else if (opStr == "keep")
			return StencilAttribute::StencilOp::Keep;
		else if (opStr == "replace")
			return StencilAttribute::StencilOp::Replace;
		else if (opStr == "incr")
			return StencilAttribute::StencilOp::Incr;
		else if (opStr == "decr")
			return StencilAttribute::StencilOp::Decr;
		else if (opStr == "invert")
			return StencilAttribute::StencilOp::Invert;
		else
			return StencilAttribute::StencilOp::ErrorOp;
	}

	inline BlendAttribute::BlendFactor StringToBlendFactor(const std::string& srcStr)
	{
		if (srcStr == "zero")
			return BlendAttribute::BlendFactor::Zero;
		else if (srcStr == "one")
			return BlendAttribute::BlendFactor::One;
		else if (srcStr == "src_color")
			return BlendAttribute::BlendFactor::SrcColor;
		else if (srcStr == "one_minus_src_color")
			return BlendAttribute::BlendFactor::OneMinusSrcColor;
		else if (srcStr == "src_alpha")
			return BlendAttribute::BlendFactor::SrcAlpha;
		else if (srcStr == "one_minus_src_alpha")
			return BlendAttribute::BlendFactor::OneMinusSrcAlpha;
		else if (srcStr == "dst_alpha")
			return BlendAttribute::BlendFactor::DstAlpha;
		else if (srcStr == "one_minus_dst_alpha")
			return BlendAttribute::BlendFactor::OneMinusDstAlpha;
		else if (srcStr == "dst_alpha")
			return BlendAttribute::BlendFactor::DstColor;
		else if (srcStr == "one_minus_dst_color")
			return BlendAttribute::BlendFactor::OneMinusDstColor;
		else
			return BlendAttribute::BlendFactor::ErrorFactor;
	}

	std::vector<std::string> StringTokenizer(std::string str, std::string delim, bool igEmptyTok = true);
}