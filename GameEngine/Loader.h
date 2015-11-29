#pragma once
#include "GLTexture.h"
#include <string>

class Loader {
public:
	static GLTexture LoadPNG(std::string _filePath);
};