/**
 * Imported from TI
*/
#include "Texture.hpp"


Texture::Texture(const std::string& fileName)
{
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	// Generate the textures
	glGenTextures(1, &id);
	// Bind the textures
	bind();
	// Standard parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load the image
	unsigned char* image = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

	if (image)
	{
		// Check whether to use rgb or rgba
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}

		if (nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}
	}

	stbi_image_free(image);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}

Texture::~Texture()
{
	// Delete from graphics card
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &id);
}
