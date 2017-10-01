#pragma once

#include <glad\glad.h>

#include <string>

namespace DYE
{
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
		~IUniform() {}
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
	public:
		//==========================================
		//	method
		//==========================================
		// TO DO:
		virtual void Bind();
	public:
		//==========================================
		//	getter
		//==========================================
		Type& GetData() { return m_Data; }
		//==========================================
		//	setter
		//==========================================
		void SetData(const Type& _data) { m_Data = _data; }
		//==========================================
		//	constructor/destructor
		//==========================================
		UniformVariable(const std::string& _name) : IUniform(_name), m_Data() {}
		~UniformVariable() {}
	};
	// TO DO: Texture specialization
	// TO DO: specialization for Bind
}
