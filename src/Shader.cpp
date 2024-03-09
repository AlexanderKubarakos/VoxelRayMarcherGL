#include "Shader.hpp"

#include <fstream>
#include <sstream>

namespace VRM {
	Shader::Shader(const char* vertexPath, const char* fragmentPath) {
		unsigned int vertex, fragment; //  shader temporary ID
		std::string vertexCode, fragmentCode; // the shaders code
		std::ifstream vertexFile, fragmentFile; // file handles
		int success;
		char infoLog[512];

		vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// open file
			vertexFile.open(vertexPath);
			fragmentFile.open(fragmentPath);
			// dump file to string stream
			std::stringstream vertexStream, fragmentStream;
			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();
			// close files
			vertexFile.close();
			fragmentFile.close();
			// dump to string
			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();
		}
		catch (std::ifstream::failure e) {
			throw std::runtime_error("Failed to read shader");
		}

		const char* vertexShaderCode = vertexCode.c_str();
		const char* fragmentShaderCode = fragmentCode.c_str();

		// create a new shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		// set the shaders code
		glShaderSource(vertex, 1, &vertexShaderCode, NULL);
		// compile the shader
		glCompileShader(vertex);
		// check for errors
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			throw std::runtime_error("Failed to compile vertex shader, " + std::string(infoLog));
		};

		// create a new shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		// set the shaders code
		glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
		// compile the shader
		glCompileShader(fragment);
		// check for errors
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			throw std::runtime_error("Failed to compile fragment shader, " + std::string(infoLog));
		};

		// create final compute shader program
		_shaderID = glCreateProgram();
		// attach our shader to the program
		glAttachShader(_shaderID, vertex);
		glAttachShader(_shaderID, fragment);
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
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader() {
		glDeleteProgram(_shaderID);
	}

	void Shader::bind() {
		// use the shader program
		glUseProgram(_shaderID);
	}
}