#include <DYEngine/graphics/Texture.h>

#include <DYEngine/utilities/Logger.h>
#include <DYEngine/graphics/Image.h>

#include <tinyxml2.h>

using namespace tinyxml2;

namespace DYE
{
	bool Texture::loadFromFile(const std::string& filename, int argc, void *args)
	{
		const char* filename_c = filename.c_str();

		XMLDocument xmlDoc;
		XMLError xmlError = xmlDoc.LoadFile(filename_c);

		if (xmlError != XMLError::XML_SUCCESS)
		{
			LogError("Error while loading texture file \"%-15s\" : Failed to load file.", filename_c);
			return false;
		}

		XMLElement* pRoot = xmlDoc.FirstChildElement("texture");

		if (pRoot == nullptr)
		{
			LogError("Error while loading texture file \"%-15s\" : Root node not found.", filename_c);
			return false;
		}

		// load image file
		{
			XMLElement* pImageNode = pRoot->FirstChildElement("image");
			if (pImageNode == nullptr)
			{
				LogError("Error while loading texture file \"%-15s\" : Image node not found.", filename_c);
				return false;
			}

			const char* imageFileName = pImageNode->Attribute("filename");
			if (imageFileName == nullptr)
			{
				LogError("Error while loading texture file \"%-15s\" : Image filename not specified.", filename_c);
				return false;
			}

			const char* desiredChannelType = pImageNode->Attribute("channel");
			if (desiredChannelType != nullptr)
			{
				std::string texFormatTypeStr = desiredChannelType;
				Texture::TextureFormat type = StringToTextureFormat(texFormatTypeStr);
				if (type == Texture::TextureFormat::FormatError)
					LogWarning("Warning while loading texture file \"%-15s\" : TextureChannel is invalid.", filename_c);
				else
					m_TextureChannelFormat = type;
			}
			else
				LogWarning("Warning while loading texture file \"%-15s\" : TextureChannel value not specified.", filename_c);

			m_pImage = RESOURCE_MGR->Load<Image>(imageFileName, TextureFormatToChannelNumber(m_TextureChannelFormat));

			if (m_pImage == nullptr)
			{
				LogError("Error while loading texture file \"%-15s\" : Image file is not properly loaded.", filename_c);
				return false;
			}

		}

		// load texture type and parameters
		{
			XMLElement* pTypeNode = pRoot->FirstChildElement("type");
			XMLElement* pFilterNode = pRoot->FirstChildElement("filter");
			XMLElement* pWrapNode = pRoot->FirstChildElement("wrapping");
			XMLElement* pMipMapNode = pRoot->FirstChildElement("mipmap");

			if (pTypeNode == nullptr)
			{
				LogWarning("Warning while loading texture file \"%-15s\" : TextureType not specified.", filename_c);
			}
			else
			{
				const char* texType = pTypeNode->Attribute("value");
				if (texType != nullptr)
				{
					std::string texTypeStr = texType;
					Texture::TextureType type = StringToTextureType(texTypeStr);
					if (type == Texture::TextureType::ErrorTextureType)
						LogWarning("Warning while loading texture file \"%-15s\" : TextureType is invalid.", filename_c);
					else
						m_TextureType = type;
				}
				else
					LogWarning("Warning while loading texture file \"%-15s\" : TextureType value not specified.", filename_c);
			}

			if (pFilterNode == nullptr)
			{
				LogWarning("Warning while loading texture file \"%-15s\" : FilterType not specified.", filename_c);
			}
			else
			{
				const char* filterType = pFilterNode->Attribute("value");
				if (filterType != nullptr)
				{
					std::string filterTypeStr = filterType;
					Texture::FilteringType type = StringToFilteringType(filterTypeStr);
					if (type == Texture::FilteringType::ErrorFilteringType)
						LogWarning("Warning while loading texture file \"%-15s\" : FilteringType is invalid.", filename_c);
					else
						m_FilteringType = type;
				}
				else
					LogWarning("Warning while loading texture file \"%-15s\" : FilteringType value not specified.", filename_c);
			}

			if (pWrapNode == nullptr)
			{
				LogWarning("Warning while loading texture file \"%-15s\" : WrappingType not specified.", filename_c);
			}
			else
			{
				const char* wrapType = pWrapNode->Attribute("value");
				if (wrapType != nullptr)
				{
					std::string wrapTypeStr = wrapType;
					Texture::WrappingType type = StringToWrappingType(wrapTypeStr);
					if (type == Texture::WrappingType::ErrorWrappingType)
						LogWarning("Warning while loading texture file \"%-15s\" : WrappingType is invalid.", filename_c);
					else
						m_WrappingType = type;
				}
				else
					LogWarning("Warning while loading texture file \"%-15s\" : WrappingType value not specified.", filename_c);
			}

			if (pMipMapNode == nullptr)
			{
				LogWarning("Warning while loading texture file \"%-15s\" : MipmapSettings not specified.", filename_c);
			}
			else
			{
				m_UseMipMap = pMipMapNode->BoolAttribute("use");
				m_MipMapLevel = pMipMapNode->IntAttribute("level");
			}
		}

		this->glInitializeTexture();
		return true;
	}

	void Texture::glInitializeTexture()
	{
		createTexture();

		bindTexture();

		glCall(glTexParameteri(m_TextureType, GL_TEXTURE_MIN_FILTER, m_FilteringType));
		glCall(glTexParameteri(m_TextureType, GL_TEXTURE_MAG_FILTER, m_FilteringType));

		glCall(glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_T, m_WrappingType));
		glCall(glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_S, m_WrappingType));

		setTextureImage();
	}

	void Texture::createTexture()
	{
		glCall(glGenTextures(1, &m_TextureID));
	}

	void Texture::bindTexture()
	{
		glCall(glActiveTexture(GL_TEXTURE0 + m_TextureUnit));
		glCall(glBindTexture(m_TextureType, m_TextureID));
	}

	void Texture::setTextureImage()
	{
		// UNDONE: add more texture type
		glCall(glTexImage2D(
			m_TextureType,
			m_MipMapLevel,
			m_pImage->GetChannelType() - Image::ChannelType::Base,
			m_pImage->GetWidth(),
			m_pImage->GetHeight(),
			0,
			m_TextureChannelFormat,
			GL_UNSIGNED_BYTE,
			m_pImage->GetImageData()
		));

		if (m_UseMipMap)
			glCall(glGenerateMipmap(m_TextureType));
	}

	void Texture::deleteTexture()
	{
		glCall(glDeleteTextures(1, &m_TextureID));
	}

	void Texture::unloadImage()
	{
		RESOURCE_MGR->Unload(m_pImage);
	}

	Image* Texture::GetImage() const
	{
		return m_pImage;
	}

	GLuint Texture::GetTextureID() const
	{
		return m_TextureID;
	}

	GLuint Texture::GetTextureUnit() const
	{
		return m_TextureUnit;
	}

	Texture::Texture() : m_pImage(nullptr)
	{

	}

	Texture::~Texture()
	{
		deleteTexture();
		if (m_pImage != nullptr)
			unloadImage();
	}
}
