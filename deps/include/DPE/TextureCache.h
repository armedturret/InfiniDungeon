#pragma once
#include <map>
#include "GLTexture.h"
namespace DPE {
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		DPE::GLTexture getTexture(std::string texturePath);

		void registerPreload(std::string textureId, DPE::GLTexture texture);

	private:
		std::map<std::string, DPE::GLTexture> m_textureMap;

	};
}
