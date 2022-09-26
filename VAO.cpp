#include"VAO.h"

VAO::VAO() {

	glGenVertexArrays(1, &ID);

	glBindVertexArray(ID);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

};

void VAO::linkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();

};

void VAO::Bind() {
	glBindVertexArray(ID);
};

void VAO::Unbind() {
	glBindVertexArray(0);
};

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
};