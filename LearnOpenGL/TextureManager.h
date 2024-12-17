#pragma once

#include <glad/glad.h>

class TextureManager
{
private:
	unsigned int textureId;
	unsigned int* texturesId;

	int width, height, nrChannels;
	unsigned char* data;
public:
	TextureManager(unsigned int amount);
	~TextureManager();
	void BindTexture(unsigned int index = 0);
	void SetTextureWrappingAndFiltering(GLenum target, GLenum pname, GLint param);
	void LoadTexture(const char* path, GLuint colorchannel);
	unsigned int getTextureId(unsigned int index = 0);
	void ActivateTexture(unsigned int textureUnit, unsigned int index = 0);
	void FlipTexture();
};