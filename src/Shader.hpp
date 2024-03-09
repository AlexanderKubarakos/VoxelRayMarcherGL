#pragma once

#include <glad/glad.h>

#include <string>

namespace VRM {
	class Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		// remove copy constructor

		void bind();

	private:
		unsigned int _shaderID;
	};
}