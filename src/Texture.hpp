#pragma once

#include "stb_image.h"

#include <GL/glew.h>
#include <string>

class Texture
{
	GLuint id;
public:
	Texture(const std::string& fileName);
	~Texture();
	void bind();
};