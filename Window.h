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

		void setBgColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
		void activateResize();
		void Eliminate();
		void swapBuffers();
		void useUniform();
};

#endif