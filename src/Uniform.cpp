#include <DYEngine\graphics\Uniform.h>

#include <DYEngine\graphics\Texture.h>
#include <DYEngine\Utility.h>

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
		m_UniformLocation = glGetUniformLocation(programID, m_UniformName.c_str());
		// TO DO: get location, program id
	}

	//====================================================================================
	//	UniformVariable::Bind Specialization
	//====================================================================================
	template<>
	void UniformVariable<int>::Bind()
	{
		glCall(glUniform1i(m_UniformLocation, m_Data));
	}

	template<>
	void UniformVariable<float>::Bind()
	{
		glCall(glUniform1f(m_UniformLocation, m_Data));
	}

	template<>
	void UniformVariable<double>::Bind()
	{
		glCall(glUniform1d(m_UniformLocation, m_Data));
	}

	template<>
	void UniformVariable<unsigned int>::Bind()
	{
		glCall(glUniform1ui(m_UniformLocation, m_Data));
	}

	template<>
	void UniformVariable<bool>::Bind()
	{
		glCall(glUniform1i(m_UniformLocation, m_Data));
	}

	template<>
	void UniformVariable<Vector2f>::Bind()
	{
		glCall(glUniform2f(m_UniformLocation, m_Data.x(), m_Data.y()));
	}

	template<>
	void UniformVariable<Vector3f>::Bind()
	{
		glCall(glUniform3f(m_UniformLocation, m_Data.x(), m_Data.y(), m_Data.z()));
	}

	template<>
	void UniformVariable<Vector4f>::Bind()
	{
		glCall(glUniform4f(m_UniformLocation, m_Data.x(), m_Data.y(), m_Data.z(), m_Data.w()));
	}

	template<>
	void UniformVariable<Mat2x2>::Bind()
	{
		glCall(glUniformMatrix2fv(m_UniformLocation, 1, GL_FALSE, m_Data.GetValuePtr()));
	}

	template<>
	void UniformVariable<Mat3x3>::Bind()
	{
		glCall(glUniformMatrix3fv(m_UniformLocation, 1, GL_FALSE, m_Data.GetValuePtr()));
	}

	template<>
	void UniformVariable<Mat4x4>::Bind()
	{
		glCall(glUniformMatrix4fv(m_UniformLocation, 1, GL_FALSE, m_Data.GetValuePtr()));
	}
	
	void UniformVariable<Texture*>::Bind()
	{
		m_Data->bindTexture();
		glCall(glUniform1i(m_UniformLocation, m_Data->GetTextureUnit()));
	}

	UniformVariable<Texture*>::~UniformVariable()
	{
		RESOURCE_MGR->Unload(m_Data);
	}
}