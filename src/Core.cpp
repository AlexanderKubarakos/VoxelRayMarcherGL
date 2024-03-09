#include "Core.hpp"

#include "ComputeShader.hpp"
#include "Shader.hpp"

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

		glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

		ComputeShader rayMarcher {"shaders/RayMarcher.glsl"};
		Shader graphicsShader {"shaders/Vertex.glsl", "shaders/Fragment.glsl"};

		while (!_window->shouldWindowClose()) {
			glfwPollEvents();

			rayMarcher.bind();
			glDispatchCompute((unsigned int)_window->getWidth(), (unsigned int)_window->getHeight(), 1);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// make sure writing to image has finished before read
			glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

			glfwSwapBuffers(_window->getGLFWWindow());
		}
	}
}