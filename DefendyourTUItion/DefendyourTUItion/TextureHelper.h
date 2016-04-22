#pragma once
#include "MainHeaders.h"
#include "FreeImage.h"


namespace Common {

	class TextureHelper
	{
	private:
		TextureHelper();

	public:
		~TextureHelper();
		
		static std::shared_ptr<TextureHelper> getInstance();
		GLuint getTextureByName(std::string filename);


	private:
		static std::shared_ptr<TextureHelper> instance;
		std::map<std::string, GLuint> m_textureMap;
	};
}