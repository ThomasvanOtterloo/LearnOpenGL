#include "TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

TextureManager::TextureManager(unsigned int size)
{
	if (size > 1)
	{
		texturesId = new unsigned int[size];  // Dynamically allocate array
		glGenTextures(size, texturesId);       // Generate multiple textures
	}
	else
	{
		texturesId = nullptr;                 // No array needed
		glGenTextures(1, &textureId);          // Generate single texture
	}
}

TextureManager::~TextureManager()
{

}

void TextureManager::BindTexture(unsigned int index)
{
	if (texturesId) {
		glBindTexture(GL_TEXTURE_2D, texturesId[index]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textureId); // For single texture case
	}
}

void TextureManager::SetTextureWrappingAndFiltering(GLenum target, GLenum pname, GLint param)
{
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(target, pname, param);

}

void TextureManager::LoadTexture(const char* path)
{
	int nrChannels;
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}


unsigned int TextureManager::getTextureId(unsigned int index)
{
	if (texturesId) {
		return texturesId[0];
	}
	else {
		return textureId; // For single texture case
	}
}

void TextureManager::ActivateTexture(unsigned int textureUnit, unsigned int index)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit); // Activate texture unit

	if (texturesId) {
		glBindTexture(GL_TEXTURE_2D, texturesId[index]); // Bind indexed texture
	}
	else {
		glBindTexture(GL_TEXTURE_2D, textureId); // Bind single texture
	}
}


void TextureManager::FlipTexture()
{
	stbi_set_flip_vertically_on_load(true);
}
