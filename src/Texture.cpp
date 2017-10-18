#include <DYEngine\graphics\Texture.h>
#include <DYEngine\utilities\XMLParser.h>
#include <DYEngine\utilities\Logger.h>
#include <DYEngine\graphics\Image.h>

namespace DYE
{
	bool Texture::loadFromFile(const std::string& filename, int argc, void *args)
	{
		const char* filename_c = filename.c_str();

		// load image name from xml
		m_pImage = RESOURCE_MGR->Load<Image>("temp.png");

		if (!m_pImage->IsLoaded())
		{
			LogError("Error while loading texture file %-15s : image file is not properly loaded.", filename_c);
			return false;
		}

		// TO DO: load texture file (which is a xml file)
		/*
		
		// load image name from xml
		m_pImage = RESOURCE_MGR->Load<Image>("temp.png");	

		
		
		*/

		this->glInitializeTexture();
		return true;
	}

	void Texture::glInitializeTexture()
	{
		createTexture();

		bindTexture();

		glTexParameteri(m_TextureType, GL_TEXTURE_MIN_FILTER, m_FilteringType);
		glTexParameteri(m_TextureType, GL_TEXTURE_MAG_FILTER, m_FilteringType);

		glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_T, m_WrappingType);
		glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_S, m_WrappingType);

		setTextureImage();
	}

	void Texture::createTexture()
	{
		glGenTextures(1, &m_TextureID);
	}

	void Texture::bindTexture()
	{
		glActiveTexture(GL_TEXTURE0 + m_TextureUnit);
		glBindTexture(m_TextureType, m_TextureID);
	}

	void Texture::setTextureImage()
	{
		// TO DO: add more texture type
		glTexImage2D(
			m_TextureType,
			m_MipMapLevel,
			m_pImage->GetChannelType(),
			m_pImage->GetWidth(),
			m_pImage->GetHeight(),
			0,
			m_pImage->GetChannelType(),
			GL_UNSIGNED_BYTE,
			m_pImage->GetImageData()
		);

		if (m_UseMipMap)
			glGenerateMipmap(m_TextureType);
	}

	void Texture::deleteTexture()
	{
		glDeleteTextures(1, &m_TextureID);
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

	Texture::~Texture()
	{
		deleteTexture();
	}
}
