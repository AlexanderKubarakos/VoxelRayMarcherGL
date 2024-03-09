#include "Core.hpp"

namespace VRM {
	Core::Core() {
		_window = std::make_unique<Window>(800, 800);
	}

	Core::~Core() {

	}

	void Core::run() {
		while (!_window->shouldWindowClose()) {
			glfwPollEvents();
			glfwSwapBuffers(_window->getGLFWWindow());
		}
	}
}