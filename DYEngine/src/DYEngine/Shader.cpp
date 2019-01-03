#include <DYEngine/graphics/Shader.h>
#include <DYEngine/utilities/XMLParser.h>
#include <DYEngine/utilities/Logger.h>


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

		// UNDONE: add global uniform to shader (MVP matrix, light positions...)

		if (!isSource)
		{
			std::string source = loadSource(SHADER_PATH + filename);

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
		glCall(glDeleteShader(m_ShaderID));
	}

	std::string Shader::loadSource(const std::string& filename)
	{
		m_pSourceText = RESOURCE_MGR->Load<Text>(filename);

		if (m_pSourceText == nullptr)
			return std::string();
		else
			return m_pSourceText->GetText();
	}

	void Shader::compileShaderFromSource(const std::string& source)
	{
		const char* src = source.c_str();
		glCall(glShaderSource(m_ShaderID, 1, &src, 0));
		glCall(glCompileShader(m_ShaderID));

		// error handling
		GLint statusCode;
		glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &statusCode);
		if (statusCode != GL_TRUE)
		{
			if (m_ShaderID != 0)
			{
				GLint infoLogSize;
				glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogSize);

				GLint length;
				GLchar* infoLog = new GLchar[infoLogSize];
				glGetShaderInfoLog(m_ShaderID, infoLogSize, &length, infoLog);

				std::string errorLog(infoLog);

				LogError("Shader \"%s\" compile error : %s", m_Name.c_str(), errorLog.c_str());

				delete[] infoLog;

				m_HasCompiledError = true;
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

	Shader::Shader(const std::string& shadername) : m_ShaderID(-1), m_pSourceText(nullptr), m_Name(shadername)
	{
		
	}

	Shader::~Shader()
	{
		if (m_pSourceText != nullptr)
			RESOURCE_MGR->Unload(m_pSourceText);
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
		const char* filename_c = filename.c_str();

		createShaderProgram();

		XMLDocument shaderDoc;
		XMLError xmlError = shaderDoc.LoadFile(filename_c);

		if (xmlError != XMLError::XML_SUCCESS)
		{
			LogError("Error while loading shaderprogram file \"%-15s\" : Failed to load file.", filename_c);
			return false;
		}

		XMLElement* pRoot = shaderDoc.FirstChildElement("shaderprogram");

		if (pRoot == nullptr)
		{
			LogError("Error while loading shader program file \"%-15s\" : Root node not found.", filename_c);
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
				std::string shaderFileNameStr(shaderFileName);
				addShaders(shaderFileNameStr, typeEnum, false);
			}
			else
			{
				// is source
				std::string source = element->GetText();
				addShaders(source, typeEnum, true);
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
		glCall(glUseProgram(m_ProgramID));
	}

	void ShaderProgram::createShaderProgram()
	{
		m_ProgramID = glCreateProgram();
	}

	Shader* ShaderProgram::addShaders(const std::string& filename, Shader::ShaderType type, bool isSource)
	{
		Shader* shader = new Shader( (isSource)? this->GetResourceFileName() : filename );
		shader->Init(filename, type, isSource);

		if (shader->HasCompileError())
		{
			delete shader;
			shader = nullptr;
		}

		m_Shaders[type] = shader;
		return shader;
	}

	void ShaderProgram::linkShaders()
	{
		// UNDONE: link to default pipeline if shader is not complete NEXT
		// link shader to program
		for (unsigned int i = 0; i < Shader::SHADER_TYPE_MAX; i++)
		{
			Shader* shader = m_Shaders[i];
			if (shader != nullptr)
				glCall(glAttachShader(m_ProgramID, shader->GetShaderID()));
		}

		glCall(glLinkProgram(m_ProgramID));

		// release shader
		for (unsigned int i = 0; i < Shader::SHADER_TYPE_MAX; i++)
		{
			Shader* shader = m_Shaders[i];
			if (shader != nullptr)
			{
				shader->DestroyShader();
			}
		}
	}

	void ShaderProgram::destroyShaderProgram()
	{
		// ensure this program is not being used before deletion
		if (GetCurrentShaderProgram() == this)
		{
			s_pCurrentShaderProgram = nullptr;
			glCall(glUseProgram(0));
		}

		for (unsigned int i = 0; i < Shader::SHADER_TYPE_MAX; i++)
		{
			Shader* shader = m_Shaders[i];
			if (shader != nullptr)
			{
				delete shader;
			}
		}
		glCall(glDeleteProgram(m_ProgramID));
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
