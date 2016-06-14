#include "TextureHelper.h"

namespace Common {
	std::shared_ptr<TextureHelper> TextureHelper::instance = NULL;

	TextureHelper::TextureHelper()
	{
		m_samplingQuality[0] = GL_NEAREST;
		m_samplingQuality[1] = GL_LINEAR;
		m_samplingQuality[2] = GL_NEAREST_MIPMAP_NEAREST;
		m_samplingQuality[3] = GL_LINEAR_MIPMAP_NEAREST;
	}


	TextureHelper::~TextureHelper()
	{
	}

	std::shared_ptr<TextureHelper> TextureHelper::getInstance() {
		if (instance == NULL) {
			instance = std::shared_ptr<TextureHelper>(new TextureHelper());
		}
		return instance;
	}

	GLuint TextureHelper::getTextureByName(std::string filename) {
		GLenum huboError = glGetError();
		if (huboError){

			std::cout << "There was an error before loading the texture" << std::endl;
		}

		if (m_textureMap.find(filename) == m_textureMap.end()) {
			FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(filename.c_str(), 0);//Automatocally detects the format(from over 20 formats!)
			FIBITMAP* imagen = FreeImage_Load(formato, filename.c_str());

			FIBITMAP* temp = imagen;
			imagen = FreeImage_ConvertTo32Bits(imagen);
			FreeImage_Unload(temp);

			int w = FreeImage_GetWidth(imagen);
			int h = FreeImage_GetHeight(imagen);
			
			GLubyte* textura = new GLubyte[4 * w*h];
			char* pixeles = (char*)FreeImage_GetBits(imagen);
			//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).

			for (int j = 0; j<w*h; j++){
				textura[j * 4 + 0] = pixeles[j * 4 + 2];
				textura[j * 4 + 1] = pixeles[j * 4 + 1];
				textura[j * 4 + 2] = pixeles[j * 4 + 0];
				textura[j * 4 + 3] = pixeles[j * 4 + 3];
			}

			//Now generate the OpenGL texture object 

			GLuint texture;

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)textura);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			GLenum huboError = glGetError();
			if (huboError){

				std::cout << "There was an error loading the texture" << std::endl;
			}

			glBindTexture(GL_TEXTURE_2D, 0);

			m_textureMap[filename] = texture;
			FreeImage_Unload(imagen);
		}

		return m_textureMap[filename];

	}

}