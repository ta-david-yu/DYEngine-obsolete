#pragma once

#include <DYEngine\Resource.h>

#include <glad\glad.h>

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
	class Shader
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

		//==========================================
		//	method
		//==========================================
	public:
		void Init(const std::string& filename, ShaderType type);
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
		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
		Shader();
		~Shader();
	};

	//====================================================================================
	//	ShaderProgram: Resource. Each shaders in the same program is assumed to have
	//====================================================================================
	class ShaderProgram : IResourceValue
	{
		friend class Resource<ShaderProgram>;
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
		void loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) override;
		void init(const std::string& filename = "unlit");
	public:
		static ShaderProgram* GetCurrentShaderProgram();
		void Bind();
	private:
		void createShaderProgram();
		Shader* addShaders(const std::string& filename, Shader::ShaderType type);	// can be called multiple times for different shaders of different stages
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