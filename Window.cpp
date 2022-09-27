#include"Window.h"

void error_callback(int error, const char* description)
{
	std::cout << "Error: " << description << std::endl;
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
};

Window::Window() {
	// initialize the background color variables rgba
	this->bgColor[0] = 0.07f;
	this->bgColor[1] = 0.13f;
	this->bgColor[2] = 0.17f;
	this->bgColor[3] = 1.0f;
	// Set error callback for GFLW
	glfwSetErrorCallback(error_callback);

	// Initialize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// Tell GLFW what version of OpenGL we are using
	// In this case 3.1 because is my version in my pc
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	// Can't user OpenGL Profile
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); my opengl version is 3.1 and this is for 3.2 and above

	// create GLFW Window with 600 x 600 px, and naming it "Test"
	window = glfwCreateWindow(600, 600, "Test", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 600, y = 600
	glViewport(0, 0, 600, 600);

}

Window& Window::setBgColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	// set the background color variables rgba
	this->bgColor[0] = r;
	this->bgColor[1] = g;
	this->bgColor[2] = b;
	this->bgColor[3] = a;

	// Specify the color of the background
	glClearColor(this->bgColor[0], this->bgColor[1], this->bgColor[2], this->bgColor[3]);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	return *this;
}

Window& Window::activateResize() {

	// create the width and height variables for resize window
	int width, height;

	// get the size of the window and store in the variabler
	glfwGetFramebufferSize(window, &width, &height);
	// set viewport of the gl with the new window sizes
	glViewport(0, 0, width, height);
	return *this;
}

Window& Window::swapBuffers() {
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
	return *this;
}

Window& Window::Eliminate() {
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return *this;
}