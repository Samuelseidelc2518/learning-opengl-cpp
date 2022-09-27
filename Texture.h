#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	
	// ID of the texture
	GLuint ID;
	// Type of texture
	GLenum type;

	// Contruct the texture with the image path
	Texture(const char* image, GLenum textType, GLenum slot, GLenum format, GLenum pixelType);
	// set the uniform variable from the fragment of the shader to unit
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	void Bind();
	void Unbind();
	void Delete();
};


#endif // !TEXTURE_CLASS_H
