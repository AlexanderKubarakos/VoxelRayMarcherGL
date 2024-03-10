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

		

		// VBO AND VAO

		float vertices[] = {
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f  // bottom right
		};
		unsigned int indices[] = {  
			0, 1, 2,
			2, 3, 1
		};

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		ComputeShader rayMarcher {"shaders/RayMarcher.glsl"};
		Shader graphicsShader {"shaders/Vertex.glsl", "shaders/Fragment.glsl"};

		while (!_window->shouldWindowClose()) {
			glfwPollEvents();

			glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
			rayMarcher.bind();
			glDispatchCompute((unsigned int)_window->getWidth(), (unsigned int)_window->getHeight(), 1);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// make sure writing to image has finished before read
			glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);


			graphicsShader.bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(_window->getGLFWWindow());
		}
	}
}