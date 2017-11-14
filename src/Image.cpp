#include <DYEngine\graphics\Image.h>
#include <DYEngine\utilities\XMLParser.h>
#include <DYEngine\utilities\Logger.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

namespace DYE
{
	bool Image::loadFromFile(const std::string& filename, int argc, void *args)
	{
		const char* filename_c = filename.c_str();

		int numOfChannel;

		m_pData = stbi_load(filename_c, &m_Width, &m_Height, &numOfChannel, argc);

		if (m_pData == NULL)
		{
			LogError("Error while loading image file \"%-15s\" : Image file not found.", filename_c);
			return false;
		}

		if (numOfChannel >= ChannelType::Error)
		{
			LogError("Error while loading image file \"%-15s\" : Channel components are invalid (%d).", filename_c, numOfChannel);
			return false;
		}

		m_ChannelType = (ChannelType) (ChannelType::Base + numOfChannel);

		return true;
	}

	unsigned char* Image::GetImageData() const
	{
		return m_pData;
	}

	Image::ChannelType Image::GetChannelType() const
	{
		return m_ChannelType;
	}

	int Image::GetWidth() const
	{
		return m_Width;
	}

	int Image::GetHeight() const
	{
		return m_Height;
	}

	Image::~Image()
	{
		stbi_image_free(m_pData);
	}
}