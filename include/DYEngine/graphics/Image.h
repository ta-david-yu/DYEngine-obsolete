#pragma once

#include <DYEngine\Resource.h>

#include <stb\stb_image.h>

namespace DYE
{
	//====================================================================================
	//	Image: native image file
	//====================================================================================
	class Image : public IResourceValue
	{

	public:
		enum ChannelType
		{
			Base = STBI_default,

			Grey = STBI_grey,
			GreyA = STBI_grey_alpha,
			RGB = STBI_rgb,
			RGBA = STBI_rgb_alpha,

			Error
		};

		friend class Resource<Image>;
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		unsigned char* m_pData;
		int m_Width, m_Height;
		ChannelType m_ChannelType;

		//==========================================
		//	method
		//==========================================
	protected:
		bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) override;

		//==========================================
		//	getter
		//==========================================
	public:
		unsigned char* GetImageData() const;
		ChannelType GetChannelType() const;
		int GetWidth() const;
		int GetHeight() const;
		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
		~Image();
	};
}