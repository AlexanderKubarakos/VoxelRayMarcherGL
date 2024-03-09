#pragma once

#include <glad/glad.h>

#include <string>

namespace VRM {
	class ComputeShader {
	public:
		ComputeShader(const char* shaderPath);
		~ComputeShader();

		// remove copy constructor

		void bind();

	private:
		unsigned int _shaderID;
	};
}