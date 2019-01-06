#pragma once

#include "DYEngine/Core.h"

#include "DYEngine/graphics/OpenGL.h"

#include <string>

namespace DYE
{
	class Texture;

	//====================================================================================
	//	IUniform: interface for uniformVariable
	//====================================================================================
	class IUniform
	{
		//==========================================
		//	memeber/variable
		//==========================================
	protected:
		std::string m_UniformName;
		GLuint m_UniformLocation;

		//==========================================
		//	method
		//==========================================
	public:
		void AttachToShader(GLuint programID);
		virtual void Bind() = 0;
		//==========================================
		//	getter
		//==========================================
	public:
		std::string GetName() const;
		GLuint GetLocation() const;
		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
	public:
		IUniform(const std::string& _name);
		virtual ~IUniform() {}
	};

	//====================================================================================
	//	UniformVariable: actual uniform data, needs
	//====================================================================================

	template <class Type>
	class UniformVariable : public IUniform
	{
		//==========================================
		//	memeber/variable
		//==========================================
	protected:
		Type m_Data;

		//==========================================
		//	method
		//==========================================
	public:
		virtual void Bind();

		//==========================================
		//	getter
		//==========================================
	public:
		inline virtual Type GetData() { return m_Data; }

		//==========================================
		//	setter
		//==========================================
		inline virtual void SetData(const Type& _data) { m_Data = _data; }

		//==========================================
		//	constructor/destructor
		//==========================================
		UniformVariable(const std::string& _name) : IUniform(_name), m_Data() {}
		~UniformVariable() { }
	};


	//====================================================================================
	//	Texture Specialization Uniform
	//====================================================================================
	template<>
	class UniformVariable<Texture*> : public IUniform
	{
		//==========================================
		//	memeber/variable
		//==========================================
	protected:
		Texture* m_Data;

		//==========================================
		//	method
		//==========================================
	public:
		virtual void Bind();

		//==========================================
		//	getter
		//==========================================
	public:
		inline virtual Texture* GetData() { return m_Data; }

		//==========================================
		//	setter
		//==========================================
		inline virtual void SetData(Texture* const& _data) { m_Data = _data; }

		//==========================================
		//	constructor/destructor
		//==========================================
	public:
		UniformVariable(const std::string& _name) : IUniform(_name), m_Data() {}
		~UniformVariable();
	};

	template<>
	class UniformVariable<Texture> : public UniformVariable<Texture*>
	{
	public:
		UniformVariable(const std::string& _name) : UniformVariable<Texture*>(_name) {}
		
	};

	//template<>
	//UniformVariable<Texture*>::~UniformVariable()
	//{
		//RESOURCE_MGR->Unload(m_Data);
	//}
}
