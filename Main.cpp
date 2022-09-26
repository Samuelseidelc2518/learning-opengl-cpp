#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


// some constants coordinates predefined for next use
const GLfloat topY = 0.5f * float(sqrt(3)) * 2 / 3;
const GLfloat bottomY = -0.5f * float(sqrt(3)) / 3;
const GLfloat leftX = -0.5f;
const GLfloat rightX = 0.5f;
const GLfloat middle = 0.0f;

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
		middle, topY, 0.0f // Upper middle corner
	};

	// create GLFW Window with 800 x 800 px, and naming it "Test"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Test", NULL, NULL);

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
	glViewport(0, 0, 800, 800);


	// Create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader Source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into Machine Code
	glCompileShader(vertexShader);

	// Create fragment shader object and get its reference
	GLuint fragmetShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmetShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment Shader into Machine Code
	glCompileShader(fragmetShader);

	// Create Shader Program and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and the Fragment Shader to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmetShader);
	// Wrap-up/Link all the Shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader Objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmetShader);



	// Create the reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Binding the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects that we created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}