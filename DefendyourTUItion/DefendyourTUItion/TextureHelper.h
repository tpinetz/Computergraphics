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
			if (!m_currentMipMapQuality) return m_samplingQuality[m_currentSamplingQuality];
			else {
				return m_samplingQuality[m_currentMipMapQuality + 1];
			}
		}

		inline GLint getMagFilterQuality() {
			return m_samplingQuality[m_currentMipMapQuality];
		}

		inline void nextSamplingQuality() {
			m_currentSamplingQuality = (m_currentSamplingQuality + 1) % 2;
		}

		inline void nextMipMapQuality() {
			m_currentMipMapQuality = (m_currentMipMapQuality + 1) % 3;
		}

	private:
		static std::shared_ptr<TextureHelper> instance;
		std::map<std::string, GLuint> m_textureMap;
		GLint m_samplingQuality[2];
		int m_currentSamplingQuality = 0;
		int m_currentMipMapQuality = 0;
	};
}