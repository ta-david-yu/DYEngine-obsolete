#include <DYEngine\graphics\Shader.h>
#include <DYEngine\utilities\XMLParser.h>
#include <DYEngine\utilities\Logger.h>


namespace DYE
{
	//====================================================================================
	//	Shader
	//====================================================================================
	void Shader::Init(const std::string& filename, ShaderType type, bool isSource)
	{
		m_Type = type;

		// gl create
		createShader();

		// TO DO: add global uniform to shader (MVP matrix, light positions...)

		if (!isSource)
		{
			std::string source = loadSource(filename);

			compileShaderFromSource(source);
		}
		else
		{
			compileShaderFromSource(filename);
		}
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

	void Shader::DestroyShader()
	{
		glDeleteShader(m_ShaderID);
	}

	std::string Shader::loadSource(const std::string& filename)
	{
		// TO DO: load file
		return std::string();
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

	}


	//====================================================================================
	//	ShaderProgram: Resource. Each shaders in the same program is assumed to have
	//====================================================================================
	ShaderProgram* ShaderProgram::s_pCurrentShaderProgram = nullptr;
	
	bool ShaderProgram::loadFromFile(const std::string& filename, int argc, void *args)
	{
		return parseShaderFile(filename);
	}

	bool ShaderProgram::parseShaderFile(const std::string& filename)
	{
		createShaderProgram();

		XMLDocument shaderDoc;
		const char* filename_c = filename.c_str();
		shaderDoc.LoadFile(filename.c_str());

		XMLElement* pRoot = shaderDoc.FirstChildElement("shaderprogram");

		if (pRoot == nullptr)
		{
			LogError("Error while loading shader program file %-15s : Root node not found.", filename_c);
			return false;
		}

		for (auto element = pRoot->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
		{
			std::string type = element->Name();
			const char* shaderFileName = element->Attribute("filename");

			Shader::ShaderType typeEnum;
			if (type == "vert")
				typeEnum = Shader::ShaderType::VERTEX_SHADER;
			else if (type == "geom")
				typeEnum = Shader::ShaderType::GEOMETRY_SHADER;
			else if (type == "frag")
				typeEnum = Shader::ShaderType::FRAGMENT_SHADER;
			else
				continue;

			if (shaderFileName != nullptr)
			{
				// load from file
				addShaders(shaderFileName, typeEnum, false);
			}
			else
			{
				// is source
				std::string source = element->GetText();
				addShaders(shaderFileName, typeEnum, true);
			}
		}

		linkShaders();

		return true;
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

	Shader* ShaderProgram::addShaders(const std::string& filename, Shader::ShaderType type, bool isSource)
	{
		Shader* shader = new Shader();
		shader->Init(filename, type, isSource);

		m_Shaders[type] = shader;
		return shader;
	}

	void ShaderProgram::linkShaders()
	{
		// TO DO: link to default pipeline if shader is not complete
		// link shader to program
		for (unsigned int i = 0; i < Shader::SHADER_TYPE_MAX; i++)
		{
			Shader* shader = m_Shaders[i];
			if (shader != nullptr)
				glAttachShader(m_ProgramID, shader->GetShaderID());
		}

		glLinkProgram(m_ProgramID);

		// release shader
		for (unsigned int i = 0; i < Shader::SHADER_TYPE_MAX; i++)
		{
			Shader* shader = m_Shaders[i];
			if (shader != nullptr)
				shader->DestroyShader();
		}
	}

	void ShaderProgram::destroyShaderProgram()
	{
		// ensure this program is not being used before deletion
		if (GetCurrentShaderProgram() == this)
		{
			s_pCurrentShaderProgram = nullptr;
			glUseProgram(0);
		}

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
