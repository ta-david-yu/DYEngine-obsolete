#include <DYEngine\graphics\Shader.h>


namespace DYE
{
	//====================================================================================
	//	Shader
	//====================================================================================
	void Shader::Init(const std::string& filename, ShaderType type)
	{
		m_Type = type;

		// gl create
		createShader();

		std::string source = loadSource(filename);

		compileShaderFromSource(source);
	}

	void Shader::createShader()
	{
		switch (m_Type)
		{
		case DYE::Shader::VERTEX_SHADER:
			m_ShaderID = glCreateShader(GL_VERTEX_SHADER);
			break;
		case DYE::Shader::GEOMETRY_SHADER:
			m_ShaderID = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		case DYE::Shader::FRAGMENT_SHADER:
			m_ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			m_ShaderID = 0;
			break;
		}
	}

	void Shader::destroyShader()
	{
		glDeleteShader(m_ShaderID);
	}

	std::string Shader::loadSource(const std::string& filename)
	{
		// TO DO: load file
	}

	void Shader::compileShaderFromSource(const std::string& source)
	{
		const char* src = source.c_str();
		glShaderSource(m_ShaderID, 1, &src, 0);
		glCompileShader(m_ShaderID);

		// error handling
		GLint statusCode;
		glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &statusCode);
		if (statusCode != GL_TRUE)
		{
			// TO DO: print error log to logger
			if (m_ShaderID != 0)
			{
				GLint infoLogSize;
				glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogSize);

				GLint length;
				GLchar* infoLog = new GLchar[infoLogSize];
				glGetShaderInfoLog(m_ShaderID, infoLogSize, &length, infoLog);

				std::string errorLog(infoLog);

				delete[] infoLog;
			}
		}
	}

	GLuint Shader::GetShaderID() const
	{
		return m_ShaderID;
	}

	Shader::ShaderType Shader::GetShaderType() const
	{
		return m_Type;
	}

	Shader::Shader() : m_ShaderID(-1)
	{
		
	}

	Shader::~Shader()
	{
		destroyShader();
	}


	//====================================================================================
	//	ShaderProgram: Resource. Each shaders in the same program is assumed to have
	//====================================================================================
	ShaderProgram* ShaderProgram::s_pCurrentShaderProgram = nullptr;
	
	void ShaderProgram::loadFromFile(const std::string& filename, int argc, void *args)
	{
		init(filename);
	}

	void ShaderProgram::init(const std::string& filename)
	{
		createShaderProgram();

		addShaders(filename + ".vs", Shader::ShaderType::VERTEX_SHADER);
		addShaders(filename + ".fs", Shader::ShaderType::FRAGMENT_SHADER);

		linkShaders();
	}

	ShaderProgram* ShaderProgram::GetCurrentShaderProgram()
	{
		return s_pCurrentShaderProgram;
	}

	void ShaderProgram::Bind()
	{
		s_pCurrentShaderProgram = this;

		//gl bind
		glUseProgram(m_ProgramID);
	}

	void ShaderProgram::createShaderProgram()
	{
		m_ProgramID = glCreateProgram();
	}

	Shader* ShaderProgram::addShaders(const std::string& filename, Shader::ShaderType type)
	{
		Shader* shader = new Shader();
		shader->Init(filename, type);

		m_Shaders[type] = shader;
		return shader;
	}

	void ShaderProgram::linkShaders()
	{
		for (unsigned int i = 0; i < Shader::SHADER_TYPE_MAX; i++)
		{
			Shader* shader = m_Shaders[i];
			if (shader != nullptr)
				glAttachShader(m_ProgramID, shader->GetShaderID());
		}

		glLinkProgram(m_ProgramID);
	}

	void ShaderProgram::destroyShaderProgram()
	{
		for (unsigned int i = 0; i < Shader::SHADER_TYPE_MAX; i++)
		{
			Shader* shader = m_Shaders[i];
			if (shader != nullptr)
			{
				delete shader;
			}
		}
		glDeleteProgram(m_ProgramID);
	}

	GLuint ShaderProgram::GetProgramID() const
	{
		return m_ProgramID;
	}

	ShaderProgram::ShaderProgram() : m_ProgramID(-1)
	{
		for (unsigned int i = 0; i < Shader::ShaderType::SHADER_TYPE_MAX; i++)
		{
			m_Shaders[i] = nullptr;
		}
	}

	ShaderProgram::~ShaderProgram()
	{
		destroyShaderProgram();
	}
}
