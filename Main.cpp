#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// some constants coordinates predefined for next use
const GLfloat topY = 0.5f * float(sqrt(3)) * 2 / 3; // the top in the Y axis
const GLfloat bottomY = -0.5f * float(sqrt(3)) / 3; // the bottom in the Y axis
const GLfloat leftX = -0.5f; // The left in the X axis
const GLfloat rightX = 0.5f; // the right in the X axis
const GLfloat middle = 0.0f; // the middle in both Y and X axis. The point (0,0)
const GLfloat innerMiddleY = 0.5f * float(sqrt(3)) / 6; // inner middle in Y axis of the line between lowers vectors and upper vector

int main() {

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case 3.1 because is my version in my pc
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	// Can't user OpenGL Profile
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); my opengl version is 3.1 and this is for 3.2 and above

	// Vertices coordinates
	GLfloat vertices[] =
	{
		leftX, bottomY, 0.0f, // Lower left corner
		rightX, bottomY, 0.0f, // Lower right corner
		middle, topY, 0.0f, // Upper middle corner
		leftX / 2, innerMiddleY, 0.0f, // Inner left
		rightX / 2, innerMiddleY, 0.0f, // Inner right
		middle, bottomY, 0.0f // Inner down
	};

	GLuint indices[] =
	{
		0, 3, 5, // lower left triangle
		1, 4, 5, // lower right triangle
		2, 3, 4 // upper triangle
	};

	// create GLFW Window with 800 x 800 px, and naming it "Test"
	GLFWwindow* window = glfwCreateWindow(600, 600, "Test", NULL, NULL);

	// error check if the window have problem when creating
	if (window == NULL) {
		const char* description;
		int code = glfwGetError(&description);
		std::cout << "Failed to create the GLFW Window. Error: " << description << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 600, 600);

	// generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertice
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to vertice
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.linkVBO(VBO1, 0);

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangles using the GL_TRIANGLES primitive and the number of vertices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects that we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}