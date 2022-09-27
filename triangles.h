#ifndef TRIANGLES_CLASS_H
#define TRIANGLES_CLASS_H


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

class Triangle
{

	public:
		Shader* program;
		Texture* popCat;
		VAO* VAO1;
		VBO* VBO1;
		EBO* EBO1;
		GLuint uniID;

		Triangle();

		void render(float multiple);
		void clean();
	private:

};

#endif