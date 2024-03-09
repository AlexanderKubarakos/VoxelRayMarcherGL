#include "Window.hpp"

#include <stdexcept>

namespace VRM {
	Window::Window(int width, int height) : _width{ width }, _height{ height } {
		// start glfw 
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		_window = glfwCreateWindow(_width, _height, "VoxelRayMarcher", NULL, NULL);

		if (!_window) {
			throw std::runtime_error("Failed to create window!");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(_window);

		// load opengl functions using glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD");
			return;
		}

		// set viewport
		glViewport(0, 0, _width, _height);
	}

	Window::~Window() {
		glfwTerminate();
	}

	GLFWwindow* Window::getGLFWWindow() {
		return _window;
	}

	bool Window::shouldWindowClose() {
		return glfwWindowShouldClose(_window);
	}
}