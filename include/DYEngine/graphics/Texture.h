#pragma once

#include <DYEngine\Resource.h>

#include <glad\glad.h>

namespace DYE
{
	class Image;

	//====================================================================================
	//	Texture: texture file
	//====================================================================================
	class Texture : public IResourceValue
	{
		friend class Resource<Texture>;
	public:
		DYE_RESOURCE_PATH(TEXTURE_PATH)
	public:
		enum TextureType
		{
			Texture2D = GL_TEXTURE_2D,

			ErrorTextureType
			// TO DO: add more texture type
		};

		enum FilteringType
		{
			Nearest = GL_NEAREST,
			Linear = GL_LINEAR,

			ErrorFilteringType
		};

		enum WrappingType
		{
			Repeat = GL_REPEAT,
			ClampToBorder = GL_CLAMP_TO_BORDER,
			ClampToEdge = GL_CLAMP_TO_EDGE,
			MirroredRepeat = GL_MIRRORED_REPEAT,

			ErrorWrappingType
		};
		//==========================================
		//	memeber/variable
		//==========================================
	private:
		Image* m_pImage;
		GLuint m_TextureID;
		GLuint m_TextureUnit;

		TextureType m_TextureType = TextureType::Texture2D;
		FilteringType m_FilteringType = FilteringType::Linear;
		WrappingType m_WrappingType = WrappingType::Repeat;
		GLint m_MipMapLevel = 0;
		bool m_UseMipMap = true;

		//==========================================
		//	method
		//==========================================
	protected:
		bool loadFromFile(const std::string& filename, int argc = 0, void *args = nullptr) override;

		void glInitializeTexture();			// initialize gl texture object based on Texture member data

		void createTexture();
		void bindTexture();
		void setTextureImage();

		void deleteTexture();
		void unloadImage();

		//==========================================
		//	getter
		//==========================================
		Image* GetImage() const;
		GLuint GetTextureID() const;
		GLuint GetTextureUnit() const;

		//==========================================
		//	setter
		//==========================================

		//==========================================
		//	constructor/destructor
		//==========================================
		~Texture();
	};

	//=========================================================================================
	//	Utilities Function
	//=========================================================================================
	inline Texture::TextureType StringToTextureType(const std::string& texStr)
	{
		if (texStr == "tex2d")
			return Texture::TextureType::Texture2D;
		else
			return Texture::TextureType::ErrorTextureType;
	}

	inline Texture::FilteringType StringToFilteringType(const std::string& filterStr)
	{
		if (filterStr == "nearest")
			return Texture::FilteringType::Nearest;
		else if (filterStr == "linear")
			return Texture::FilteringType::Linear;
		else
			return Texture::FilteringType::ErrorFilteringType;
	}

	inline Texture::WrappingType StringToWrappingType(const std::string& wrapStr)
	{
		if (wrapStr == "repeat")
			return Texture::WrappingType::Repeat;
		else if (wrapStr == "clamp_to_border")
			return Texture::WrappingType::ClampToBorder;
		else if (wrapStr == "clamp_to_edge")
			return Texture::WrappingType::ClampToEdge;
		else if (wrapStr == "mirrored_repeat")
			return Texture::WrappingType::MirroredRepeat;
		else
			return Texture::WrappingType::ErrorWrappingType;
	}
	
}