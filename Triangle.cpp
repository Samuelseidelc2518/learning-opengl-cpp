#include"triangles.h"
#include<stb/stb_image.h>

// Vertices coordinates
GLfloat vertices[] =
{
	//			Coodinates				 	/		Colors				/	Description
	-0.5f,	-0.5f,	0.0f,				1.0f, 0.0f, 0.0f,	0.0f,  0.0f,		// upper left
	-0.5f,	0.5f,	0.0f,				0.0f, 1.0f, 0.0f,	0.0f,  1.0f,		// lower left
	0.5f,	0.5f,	0.0f,				0.0f, 0.0f, 1.0f,	1.0f,  1.0f,		// upper right
	0.5f,	-0.5f,	0.0f,				1.0f, 1.0f, 1.0f,	1.0f,  0.0f,		// lower right
};

// Selection of indices of the vertices array to know which vertices use for each triangle
GLuint indices[] =
{
	0, 1, 2,	// Upper left Triangle  
	0, 2, 3,	// Lower right Triangle
};

Triangle::Triangle() {

	// generates Shader object using shaders default.vert and default.frag
	program = new Shader("default.vert", "default.frag");

	VAO1 = new VAO();

	// Generates Vertex Array Object and binds it
	VAO1->Bind();

	// Generates Vertex Buffer Object and links it to vertice
	VBO1 = new VBO(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to vertice
	EBO1 = new EBO(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1->linkAttrib(*VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1->linkAttrib(*VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1->linkAttrib(*VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1->Unbind();
	VBO1->Unbind();
	EBO1->Unbind();

	uniID = glGetUniformLocation(program->ID, "scale");

	// Texture
	// 
	// create the texture instance
	popCat = new Texture("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	// set the tex0 uniform variable to 0
	popCat->texUnit(*program, "tex0", 0);
}

void Triangle::render(float multiple) {

	program->Activate();

	glUniform1f(uniID, multiple);
	glBindTexture(GL_TEXTURE_2D, this->popCat->ID);

	VAO1->Bind();
	// Draw the triangles using the GL_TRIANGLES primitive and the number of vertices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Triangle::clean() {
	// Delete all the objects that we created
	VAO1->Delete();
	VBO1->Delete();
	EBO1->Delete();
	popCat->Delete();
	program->Delete();
}