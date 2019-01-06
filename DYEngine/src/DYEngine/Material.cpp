#include <DYEngine/graphics/Material.h>
#include <DYEngine/utilities/Logger.h>
#include <DYEngine/graphics/Shader.h>
#include <DYEngine/graphics/Texture.h>
#include <DYEngine/utilities/Math.h>

#include <tinyxml2.h>

#include <stdexcept>

using namespace tinyxml2;

namespace DYE
{
	bool Material::loadFromFile(const std::string& filename, int argc, void *args)
	{
		const char* filename_c = filename.c_str();

		XMLDocument xmlDoc;
		XMLError xmlError = xmlDoc.LoadFile(filename_c);

		if (xmlError != XMLError::XML_SUCCESS)
		{
			LogError("Error while loading material file \"%-15s\" : Failed to load file.", filename_c);
			return false;
		}

		XMLElement* pRoot = xmlDoc.FirstChildElement("material");

		if (pRoot == nullptr)
		{
			LogError("Error while loading material file \"%-15s\" : Root node not found.", filename_c);
			return false;
		}

		// parse render order of the material
		{
			XMLElement* pOrderElement = pRoot->FirstChildElement("order");
			if (pOrderElement == nullptr)
			{
				LogError("Error while loading material file \"%-15s\" : Order node not found.", filename_c);
				return false;
			}

			m_RenderOrder = pOrderElement->IntAttribute("value", 1000);
		}

		// parse each pass shader settings
		for (auto element = pRoot->FirstChildElement("pass"); element != nullptr; element = element->NextSiblingElement())
		{
			XMLElement* pShaderElement = element->FirstChildElement("shaderprogram");
			if (pShaderElement == nullptr)
			{
				LogError("Error while loading material file \"%-15s\" : Shader program node not found.", filename_c);
				return false;
			}

			const char* shaderProgramFileName = pShaderElement->Attribute("filename");
			if (shaderProgramFileName == nullptr)
			{
				LogError("Error while loading material file \"%-15s\" : Shader program filename not found.", filename_c);
				return false;
			}

			// create a new pass
			m_RenderPasses.push_back(RenderPass());
			RenderPass& pass = m_RenderPasses.back();

			// create shader program
			std::string shaderProgramFileNameStr(shaderProgramFileName);
			ShaderProgram* program = RESOURCE_MGR->Load<ShaderProgram>(shaderProgramFileNameStr);
			pass.pProgram = program;

			// load attribute (depth, stencil, blend)
			XMLElement* pAttriElement = pShaderElement->FirstChildElement("attributes");
			for (auto element = pAttriElement->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
			{
				std::string type = element->Name();
				if (type == "depth")
				{
					DepthAttribute& attr = pass.DepthAttr;
					attr.IsEnabled = true;

					// loading function
					const char* funcType = element->Attribute("func");
					if (funcType != nullptr)
					{
						std::string funcStr = funcType;
						AttribFunc func = StringToAttributFunc(funcStr);
						if (func == AttribFunc::ErrorFunc)
							LogWarning("Warning while loading material file \"%-15s\" : DepthFunc is invalid.", filename_c);
						else
							attr.Func = func;
					}
				}
				else if (type == "stencil")
				{
					StencilAttribute& attr = pass.StencilAttr;
					attr.IsEnabled = true;

					// loading function
					const char* funcType = element->Attribute("func");
					if (funcType != nullptr)
					{
						std::string funcStr = funcType;
						AttribFunc func = StringToAttributFunc(funcStr);
						if (func == AttribFunc::ErrorFunc)
							LogWarning("Warning while loading material file \"%-15s\" : StencilFunc is invalid.", filename_c);
						else
							attr.Func = func;
					}

					// loading operation
					const char* opType = element->Attribute("op");
					if (opType != nullptr)
					{
						std::string opStr = opType;
						StencilAttribute::StencilOp op = StringToStencilOp(opStr);
						if (op == StencilAttribute::StencilOp::ErrorOp)
							LogWarning("Warning while loading material file \"%-15s\" : StencilOp is invalid.", filename_c);
						else
							attr.Op = op;
					}


					// loading reference value
					attr.Ref = element->IntAttribute("ref", 0);

					// loading mask value
					attr.Msk = element->IntAttribute("msk", 0xFFFFFFFF);
					
				}
				else if (type == "blend")
				{
					BlendAttribute& attr = pass.BlendAttr;
					attr.IsEnabled = true;

					// loading src factor
					const char* srcType = element->Attribute("src");
					if (srcType != nullptr)
					{
						std::string srcStr = srcType;
						BlendAttribute::BlendFactor srcFactor = StringToBlendFactor(srcStr);
						if (srcFactor == BlendAttribute::BlendFactor::ErrorFactor)
							LogWarning("Warning while loading material file \"%-15s\" : SrcFactor is invalid.", filename_c);
						else
							attr.SrcFactor = srcFactor;
					}

					// loading dst factor
					const char* dstType = element->Attribute("dst");
					if (dstType != nullptr)
					{
						std::string dstStr = dstType;
						BlendAttribute::BlendFactor dstFactor = StringToBlendFactor(dstStr);
						if (dstFactor == BlendAttribute::BlendFactor::ErrorFactor)
							LogWarning("Warning while loading material file \"%-15s\" : DstFactor is invalid.", filename_c);
						else
							attr.DstFactor = dstFactor;
					}
				}
				else
					LogWarning("Warning while loading material file \"%-15s\" : Attribute type is invalid.", filename_c);
			}


			// load uniform data
			XMLElement* pUniformElement = pShaderElement->FirstChildElement("uniforms");
			for (auto element = pUniformElement->FirstChildElement("uniform"); element != nullptr; element = element->NextSiblingElement())
			{
				// loading uniform name
				std::string name(element->Attribute("name"));

				// loading uniform type
				std::string typeS(element->Attribute("type"));

				// loading uniform value
				std::string valueS(element->Attribute("value"));

				if (typeS == "float")
				{
					float f;
					try
					{
						f = std::stof(valueS);
					}
					catch (...)
					{
						f = 0.0f;
						LogWarning("Warning while loading material file \"%-15s\" : Float uniform %s has an invalid value.", filename_c, name.c_str());
					}

					pass.AddUniform(name, f);
				}
				else if (typeS == "vec2")
				{
					int numOfComp = 2;

					Vector2f vec;
					auto toks = StringTokenizer(valueS, " ");

					int index = 0;
					for (auto& tok : toks)
					{
						if (index >= numOfComp)
						{
							LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has too much components.", filename_c, name.c_str());

							break;
						}

						float f;
						try
						{
							f = std::stof(tok);
						}
						catch ( ... )
						{
							f = 0.0f;
							LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has an invalid component.", filename_c, name.c_str());
						}
						vec[index] = f;
						index++;
					}

					if (index < numOfComp)
					{
						LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has too few components.", filename_c, name.c_str());
					}

					pass.AddUniform(name, vec);
				}
				else if (typeS == "vec3")
				{
					int numOfComp = 3;

					Vector3f vec;
					auto toks = StringTokenizer(valueS, " ");

					int index = 0;
					for (auto& tok : toks)
					{
						if (index >= numOfComp)
						{
							LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has too much components.", filename_c, name.c_str());

							break;
						}

						float f;
						try
						{
							f = std::stof(tok);
						}
						catch (...)
						{
							f = 0.0f;
							LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has an invalid component.", filename_c, name.c_str());
						}
						vec[index] = f;
						index++;
					}

					if (index < numOfComp)
					{
						LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has too few components.", filename_c, name.c_str());
					}

					pass.AddUniform(name, vec);
				}
				else if (typeS == "vec4")
				{
					int numOfComp = 4;

					Vector3f vec;
					auto toks = StringTokenizer(valueS, " ");

					int index = 0;
					for (auto& tok : toks)
					{
						if (index >= numOfComp)
						{
							LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has too much components.", filename_c, name.c_str());

							break;
						}

						float f;
						try
						{
							f = std::stof(tok);
						}
						catch (...)
						{
							f = 0.0f;
							LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has an invalid component.", filename_c, name.c_str());
						}
						vec[index] = f;
						index++;
					}

					if (index < numOfComp)
					{
						LogWarning("Warning while loading material file \"%-15s\" : Vec2 uniform %s has too few components.", filename_c, name.c_str());
					}

					pass.AddUniform(name, vec);
				}
				else if (typeS == "sampler2D")
				{
					Texture* texture = RESOURCE_MGR->Load<Texture>(valueS);

					if (texture == nullptr)
					{
						LogWarning("Warning while loading material file \"%-15s\" : Sampler2D uniform %s is not properly loaded: %s.", filename_c, name.c_str(), valueS.c_str());
					}
					else
					{
						pass.AddUniform(name, texture);
					}
				}
			}
		}
		return true;
	}

	Material::~Material()
	{
		for (auto const& pass : m_RenderPasses)
		{
			RESOURCE_MGR->Unload( pass.pProgram );
		}
	}
}