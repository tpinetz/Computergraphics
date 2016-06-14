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
		inline GLint getTextureSamplingQuality() {
			return m_samplingQuality[m_currentSamplingQuality];
		}

		inline void nextSamplingQuality() {
			m_currentSamplingQuality = (m_currentSamplingQuality + 1) % 2;
		}

	private:
		static std::shared_ptr<TextureHelper> instance;
		std::map<std::string, GLuint> m_textureMap;
		GLint m_samplingQuality[2];
		int m_currentSamplingQuality = 0;
	};
}