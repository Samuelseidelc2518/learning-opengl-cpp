#include"Window.h"
#include"triangles.h"

int main() {

	// instantiate the window object
	Window window;
	
	// instantiate the triangle object
	Triangle triangle;

	// Set background color and swap back buffer with front buffer
	window.setBgColor(0.07f, 0.13f, 0.17f, 1.0f).swapBuffers();


	// Main while loop
	while (!glfwWindowShouldClose(window.window)) {

		// activate resize option and set the background Color
		window.activateResize().setBgColor(0.07f, 0.13f, 0.17f, 1.0f);

		triangle.render(0.5f);

		window.swapBuffers();
		// Take care of all GLFW events
		glfwPollEvents();
	}

	triangle.clean();

	window.Eliminate();

	return 0;
}