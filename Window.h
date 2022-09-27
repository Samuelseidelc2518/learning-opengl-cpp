#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Window
{
	public:

		GLFWwindow* window;
		GLfloat bgColor[4];

		Window();

		Window& setBgColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
		Window& activateResize();
		Window& Eliminate();
		Window& swapBuffers();
		Window& useUniform();
};

#endif