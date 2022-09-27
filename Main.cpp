#include"Window.h"
#include"triangles.h"

int main() {

	// instantiate the window object
	Window window;
	
	// instantiate the triangle object
	Triangle triangle;

	// Set background color
	window.setBgColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Swap the back buffer with the front buffer
	window.swapBuffers();

	// Main while loop
	while (!glfwWindowShouldClose(window.window)) {

		window.activateResize();

		window.setBgColor(1.0f, 1.0f, 1.0f, 1.0f);

		triangle.render(0.5f);

		window.swapBuffers();
		// Take care of all GLFW events
		glfwPollEvents();
	}

	triangle.clean();

	window.Eliminate();

	return 0;
}