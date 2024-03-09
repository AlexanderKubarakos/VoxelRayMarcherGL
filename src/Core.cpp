#include "Core.hpp"

#include "ComputeShader.hpp"

namespace VRM {
	Core::Core() {
		_window = std::make_unique<Window>(800, 800);
	}

	Core::~Core() {

	}

	void Core::run() {
		unsigned int texture;

		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _window->getWidth(), _window->getHeight(), 0, GL_RGBA,
			GL_FLOAT, NULL);

		glBindTexture(GL_TEXTURE_2D, texture);

		ComputeShader rayMarcher {"shaders/RayMarcher.glsl"};

		while (!_window->shouldWindowClose()) {
			glfwPollEvents();
			glfwSwapBuffers(_window->getGLFWWindow());
		}
	}
}