#pragma once
#include "TextureCache.h"
#include <string>
namespace DPE {
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

		static void preloadTexture(std::string textureId, DPE::GLTexture texture);

	private:
		static TextureCache m_textureCache;
	};
}
