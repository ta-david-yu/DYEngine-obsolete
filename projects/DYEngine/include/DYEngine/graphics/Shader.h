#pragma once

#include <DYEngine/Core.h>

#include <DYEngine/Resource.h>
#include <DYEngine/utilities/OpenGL.h>

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <type_traits>
#include <cassert>

namespace DYE
{
	class ShaderProgram;

	//====================================================================================
	//	Shader: Managed by Shader Program, have many types
	//====================================================================================
	class DYE_API Shader
	{
	public:
		enum ShaderType
		{
			VERTEX_SHADER,
			GEOMETRY_SHADER,
			FRAGMENT_SHADER,

			SHADER_TYPE_MAX
		};

		//==========================================
		//	memeber/variable
		//==========================================
	private:
		GLuint m_ShaderID;
		ShaderType m_Type;
		bool m_HasCompiledError = false;
		Text* m_pSourceText;
		std::string m_Name;

		//==========================================
		//	method
		//==========================================
	public:
		void Init(const std::string& filename, ShaderType type, bool isSource = false);
	private:
		void createShader();
	public:
		void DestroyShader();	// called by program after being linked
	private:
		std::string loadSource(const std::string& filename);
		void compileShaderFromSource(const std::string& source);

		//==========================================
		//	getter
		//==========================================
	public:
		GLuint GetShaderID() const;
		ShaderType GetShaderType() const;
		inline bool HasCompileError() const { return m_HasCompiledError; }

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
		Shader(const std::string& shadername);
		~Shader();
	};

	//====================================================================================
	//	ShaderProgram: Resource. Each shaders in the same program is assumed to have
	//====================================================================================
	class DYE_API ShaderProgram : public IResourceValue
	{
		friend class Resource<ShaderProgram>;
	public:
		DYE_RESOURCE_PATH(SHADER_PATH)
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		static ShaderProgram* s_pCurrentShaderProgram;
	private:
		GLuint m_ProgramID;
		Shader* m_Shaders[Shader::ShaderType::SHADER_TYPE_MAX];	// shaders are own by program

		//==========================================
		//	method
		//==========================================
		// TO DO: add defulat value unlit
		bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) override;
		bool parseShaderFile(const std::string& filename = "unlit");
	public:
		static ShaderProgram* GetCurrentShaderProgram();
		void Bind();
	private:
		void createShaderProgram();
		Shader* addShaders(const std::string& filename, Shader::ShaderType type, bool isSource = false);	// can be called multiple times for different shaders of different stages
		void linkShaders();
		void destroyShaderProgram();
		//==========================================
		//	getter
		//==========================================
	public:
		GLuint GetProgramID() const;

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
		ShaderProgram();
		~ShaderProgram();
	};
}