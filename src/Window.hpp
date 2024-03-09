#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace VRM {
class Window {
public:
	Window(int width, int height);
	~Window();

	// remove copy constructor

	GLFWwindow* getGLFWWindow();
	bool shouldWindowClose();
private:
	GLFWwindow* _window;
	int _height;
	int _width;
};
}