#include"triangles.h"


// some constants coordinates predefined for next use
const GLfloat topY = 0.5f * float(sqrt(3)) * 2 / 3;		// the top in the Y axis
const GLfloat bottomY = -0.5f * float(sqrt(3)) / 3;		// the bottom in the Y axis
const GLfloat leftX = -0.5f;							// The left in the X axis
const GLfloat rightX = 0.5f;							// the right in the X axis
const GLfloat middle = 0.0f;							// the middle in both Y and X axis. The point (0,0)
const GLfloat innerMiddleY = 0.5f * float(sqrt(3)) / 6; // inner middle in Y axis of the line between lowers vectors and upper vector


// Vertices coordinates
GLfloat vertices[] =
{
	//			Coodinates				 	/		Colors				/	Description
		leftX,		bottomY,		0.0f,		0.13f, 0.26f, 0.53f,		// Lower left corner
		rightX,		bottomY,		0.0f,		0.13f, 0.26f, 0.53f,		// Lower right corner
		middle,		topY,			0.0f,		0.13f, 0.26f, 0.53f,		// Upper middle corner
		leftX / 2,	innerMiddleY,	0.0f,		0.13f, 0.26f, 0.53f,		// Inner left
		rightX / 2, innerMiddleY,	0.0f,		0.13f, 0.26f, 0.53f,		// Inner right
		middle,		bottomY,		0.0f,		0.13f, 0.26f, 0.53f,		// Inner down
};

// Selection of indices of the vertices array to know which vertices use for each triangle
GLuint indices[] =
{
	2, 3, 4,	// Upper Triangle
	0, 3, 5,	// Lower Left Triangle
	1, 4, 5		// Lower Right Triangle
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
	VAO1->linkAttrib(*VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1->linkAttrib(*VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1->Unbind();
	VBO1->Unbind();
	EBO1->Unbind();

	uniID = glGetUniformLocation(program->ID, "scale");



}

void Triangle::render(float multiple) {

	program->Activate();

	glUniform1f(uniID, multiple);

	VAO1->Bind();
	// Draw the triangles using the GL_TRIANGLES primitive and the number of vertices
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

void Triangle::clean() {
	// Delete all the objects that we created
	VAO1->Delete();
	VBO1->Delete();
	EBO1->Delete();
	program->Delete();
}