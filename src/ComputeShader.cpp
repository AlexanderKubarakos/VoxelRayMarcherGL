#include "ComputeShader.hpp"

#include <fstream>
#include <sstream>

namespace VRM {
	ComputeShader::ComputeShader(const char* shaderPath) {
		unsigned int compute; // compute shader temporary ID
		std::string shaderCode; // the shaders code
		std::ifstream file; // file handle
		int success;
		char infoLog[512];

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// open file
			file.open(shaderPath);
			// dump file to string stream
			std::stringstream codeStream;
			codeStream << file.rdbuf();
			file.close();
			// dump to string
			shaderCode = codeStream.str();
		}
		catch (std::ifstream::failure e) {
			throw std::runtime_error("Failed to read shader");
		}

		const char* computeShaderCode = shaderCode.c_str();

		// create a new shader
		compute = glCreateShader(GL_COMPUTE_SHADER);
		// set the shaders code
		glShaderSource(compute, 1, &computeShaderCode, NULL);
		// compile the shader
		glCompileShader(compute);
		// check for errors
		glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(compute, 512, NULL, infoLog);
			throw std::runtime_error("Failed to compile compute shader, " + std::string(infoLog));
		};

		// create final compute shader program
		_shaderID = glCreateProgram();
		// attach our shader to the program
		glAttachShader(_shaderID, compute);
		// link the program
		glLinkProgram(_shaderID);
		// check for errors
		glGetProgramiv(_shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(_shaderID, 512, NULL, infoLog);
			throw std::runtime_error("Failed to link compute shader program, " + std::string(infoLog));
		}

		// delete tempory shader after linking
		glDeleteShader(compute);
	}

	ComputeShader::~ComputeShader() {
		glDeleteProgram(_shaderID);
	}

	void ComputeShader::bind() {
		// use the shader program
		glUseProgram(_shaderID);
	}
}