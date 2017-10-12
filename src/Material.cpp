#include <DYEngine\graphics\Material.h>
#include <DYEngine\utilities\XMLParser.h>
#include <DYEngine\utilities\Logger.h>
#include <DYEngine\graphics\Shader.h>

namespace DYE
{
	bool Material::loadFromFile(const std::string& filename, int argc, void *args)
	{
		XMLDocument xmlDoc;
		xmlDoc.LoadFile( filename.c_str() );

		XMLElement* pRoot = xmlDoc.FirstChildElement("material");

		if (pRoot == nullptr)
		{
			LogError("Error while loading material file %-15s : Root node not found.", filename);
			return false;
		}

		// parse render order of the material
		{
			XMLElement* pOrderElement = pRoot->FirstChildElement("order");
			if (pOrderElement == nullptr)
			{
				LogError("Error while loading material file %-15s : Order node not found.", filename);
				return false;
			}

			m_RenderOrder = pOrderElement->IntAttribute("value", 1000);
		}

		// parse each pass shader settings
		for (auto element = pRoot->FirstChildElement("pass"); element != nullptr; element = element->NextSiblingElement())
		{
			XMLElement* pShaderElement = pRoot->FirstChildElement("shaderprogram");
			if (pShaderElement == nullptr)
			{
				LogError("Error while loading material file %-15s : Shaderprogram node not found.", filename);
				return false;
			}

			const char* shaderProgramFileName = pShaderElement->Attribute("filename");
			if (shaderProgramFileName == nullptr)
			{
				LogError("Error while loading material file %-15s : Shaderprogram filename not found.", filename);
				return false;
			}

			// create a new pass
			m_RenderPasses.push_back(RenderPass());
			RenderPass& pass = m_RenderPasses.back();

			// create shader program
			ShaderProgram* program = RESOURCE_MGR->Load<ShaderProgram>(shaderProgramFileName);
			pass.pProgram = program;

			// load attribute (depth, stencil, blend)
			{
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
								LogWarning("Warning while loading material file %-15s : DepthFunc is invalid.", filename);
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
								LogWarning("Warning while loading material file %-15s : StencilFunc is invalid.", filename);
						}

						// loading operation
						const char* opType = element->Attribute("op");
						if (opType != nullptr)
						{
							std::string opStr = opType;
							StencilAttribute::StencilOp op = StringToStencilOp(opStr);
							if (op == StencilAttribute::StencilOp::ErrorOp)
								LogWarning("Warning while loading material file %-15s : StencilOp is invalid.", filename);
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
								LogWarning("Warning while loading material file %-15s : SrcFactor is invalid.", filename);
						}

						// loading dst factor
						const char* dstType = element->Attribute("dst");
						if (dstType != nullptr)
						{
							std::string dstStr = dstType;
							BlendAttribute::BlendFactor dstFactor = StringToBlendFactor(dstStr);
							if (dstFactor == BlendAttribute::BlendFactor::ErrorFactor)
								LogWarning("Warning while loading material file %-15s : DstFactor is invalid.", filename);
						}
					}
					else
						LogWarning("Warning while loading material file %-15s : Attribute type is invalid.", filename);

				}
			}


			// TO DO: load uniform
			{
				
			}
		}
	}

	Material::~Material()
	{
		for (auto const& pass : m_RenderPasses)
		{
			RESOURCE_MGR->Unload( pass.pProgram->GetResourceFileName() );
		}
	}
}