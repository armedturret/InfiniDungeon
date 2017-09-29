#pragma once
#include "GLTexture.h"

#include <string>
namespace DPE {
	class ImageLoader
	{
	public:
		static DPE::GLTexture loadPNG(const char* filePath);
	};
}
