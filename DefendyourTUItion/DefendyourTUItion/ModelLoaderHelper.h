#pragma once
#include "MainHeaders.h"
#include "Model.h"
#include "ObjectLoader.hpp"
#include "TextureHelper.h"

namespace Common {

	class ModelLoaderHelper
	{
	private:
		ModelLoaderHelper();

	public:
		~ModelLoaderHelper();
		static std::shared_ptr<ModelLoaderHelper> getInstance();

		std::shared_ptr<Renderer::Model> getTextureModel(std::string modelString, std::string textureString);
	private:
		static std::shared_ptr<ModelLoaderHelper> m_instance;

	};

}