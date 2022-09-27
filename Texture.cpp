#include"Texture.h"


Texture::Texture(const char* image, GLenum textType, GLenum slot, GLenum format, GLenum pixelType) {

	this->type = textType;

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &this->ID);
	glActiveTexture(slot); // GL_TEXTURE0
	glBindTexture(type, this->ID);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(type, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(type);

	stbi_image_free(bytes);
	glBindTexture(type, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	// get the uniform tex0 from the fragment
	GLuint tex0Uni = glGetUniformLocation(shader.ID, "tex0");
	// Activate the shader program
	shader.Activate();
	// Specify the value of a uniform variable for the current program object
	glUniform1i(tex0Uni, unit); // 0
}

void Texture::Bind() {
	glBindTexture(type, this->ID);
}
void Texture::Unbind() {
	glBindTexture(type, 0);
}
void Texture::Delete() {
	glDeleteTextures(1, &this->ID);
}