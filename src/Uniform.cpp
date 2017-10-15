#include <DYEngine\graphics\Uniform.h>
#include <DYEngine\Utility.h>

#include <glad\glad.h>

namespace DYE
{
	IUniform::IUniform(const std::string& _name) : m_UniformName(_name)
	{

	}

	std::string IUniform::GetName() const
	{
		return m_UniformName;
	}

	GLuint IUniform::GetLocation() const
	{
		return m_UniformLocation;
	}

	void IUniform::AttachToShader(GLuint programID)
	{
		// TO DO: get location, program id
	}

	//====================================================================================
	//	UniformVariable::Bind Specialization
	//====================================================================================

	template<>
	void UniformVariable<int>::Bind()
	{
		glUniform1i(m_UniformLocation, m_Data);
	}

	template<>
	void UniformVariable<float>::Bind()
	{
		glUniform1f(m_UniformLocation, m_Data);
	}

	template<>
	void UniformVariable<double>::Bind()
	{
		glUniform1d(m_UniformLocation, m_Data);
	}

	template<>
	void UniformVariable<unsigned int>::Bind()
	{
		glUniform1ui(m_UniformLocation, m_Data);
	}

	template<>
	void UniformVariable<bool>::Bind()
	{
		glUniform1i(m_UniformLocation, m_Data);
	}

	template<>
	void UniformVariable<Vector2f>::Bind()
	{
		glUniform2f(m_UniformLocation, m_Data.x(), m_Data.y());
	}

	template<>
	void UniformVariable<Vector3f>::Bind()
	{
		glUniform3f(m_UniformLocation, m_Data.x(), m_Data.y(), m_Data.z());
	}

	template<>
	void UniformVariable<Vector4f>::Bind()
	{
		glUniform4f(m_UniformLocation, m_Data.x(), m_Data.y(), m_Data.z(), m_Data.w());
	}

	// TO DO: Mat4x4
	// TO DO: Texture
}