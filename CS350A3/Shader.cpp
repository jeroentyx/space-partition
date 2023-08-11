/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Shader.cpp
Purpose:  Use for sending uniforms to gpu, some helpers to debug for openGL errors
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

#include <vector>
#include "Shader.h"
#include <iostream>
#include "glad/glad.h"

//Shader file
Shader::Shader(bool GeoUse, Type type)
	:m_programId(0), m_vertexId(0), m_fragmentId(0), m_geometryId(0),
	m_infoLogLength(0), m_result(GL_FALSE), isGeoUse(GeoUse), m_norm(type)
{
	const char* noGeometryShader = "";
	//normal shader is vertex and fragment only
	if (type == NORMAL)
	{
		Create("shaders\\m_vertexShader.vert", "shaders\\m_fragmentShader.frag", noGeometryShader);
	}
	//check if we are using geometry shader
	if(GeoUse == true)
	{
		if (type == VERTEX)
		{
			Create("shaders\\m_vertexShader_2.vert", "shaders\\m_fragmentShader_2.frag", "shaders\\m_geometryShader.geom");
		}
		else if (type == FACE)
		{
			Create("shaders\\m_vertexShader_2.vert", "shaders\\m_fragmentShader_2.frag", "shaders\\m_geometryShader_2.geom");
		}
	}
	if (type == DEFFERED)
	{
		Create("shaders\\deferred_shading.vert", "shaders\\deferred_shading.frag", noGeometryShader);
	}
	if (type == G_BUFFER)
	{
		Create("shaders\\g_buffer.vert", "shaders\\g_buffer.frag", noGeometryShader);
	}
	if (type == OCTREE)
	{
		Create("shaders\\m_octree.vert", "shaders\\m_octree.frag", noGeometryShader);
	}
}

//Destructor
Shader::~Shader()
{
	//empty for now
}

void Shader::Create(const char* vert_path, const char* frag_path, const char* geo_path)
{
	//taken from learnOpenGL
	std::string vertexShaderCode, fragmentShaderCode, geometryShaderCode;
	
	std::ifstream VertexShadereStream(vert_path, std::ios::in);
	std::ifstream FragmentShaderStream(frag_path, std::ios::in);
	std::ifstream GeometryShaderStream(geo_path, std::ios::in);
	if (VertexShadereStream.is_open())
	{
		std::stringstream vShaderStream;
		vShaderStream << VertexShadereStream.rdbuf();
		VertexShadereStream.close();
		vertexShaderCode = vShaderStream.str();
	}
	if (FragmentShaderStream.is_open())
	{
		std::stringstream fShaderStream;
		fShaderStream << FragmentShaderStream.rdbuf();
		FragmentShaderStream.close();
		fragmentShaderCode = fShaderStream.str();
	}
	if (GeometryShaderStream.is_open())
	{
		std::stringstream gShaderStream;
		gShaderStream << GeometryShaderStream.rdbuf();
		GeometryShaderStream.close();
		geometryShaderCode = gShaderStream.str();
	}
	const char* vShaderCode = vertexShaderCode.c_str();
	const char* fShaderCode = fragmentShaderCode.c_str();
	const char* gShaderCode = geometryShaderCode.c_str();

	m_vertexId = glCreateShader(GL_VERTEX_SHADER);
	char const* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(m_vertexId, 1, &vertexSourcePointer, NULL);
	glCompileShader(m_vertexId);
	glGetShaderiv(m_vertexId, GL_COMPILE_STATUS, &m_result);
	if (m_result == GL_FALSE)
	{
		glGetShaderiv(m_vertexId, GL_INFO_LOG_LENGTH, &m_infoLogLength);
		std::vector<char> ShaderErrorMessage(m_infoLogLength + 1);
		glGetShaderInfoLog(m_vertexId, 1024, &m_infoLogLength, &ShaderErrorMessage[0]);
		std::cout << "Shader vertex problem" << &ShaderErrorMessage[0] << std::endl;
	}

	m_fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	char const* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(m_fragmentId, 1, &fragmentSourcePointer, NULL);
	glCompileShader(m_fragmentId);
	glGetShaderiv(m_fragmentId, GL_COMPILE_STATUS, &m_result);
	if (m_result == GL_FALSE) {

		glGetShaderiv(m_fragmentId, GL_INFO_LOG_LENGTH, &m_infoLogLength);
		std::vector<char> ShaderErrorMessage(m_infoLogLength + 1);
		glGetShaderInfoLog(m_fragmentId, 1024, &m_infoLogLength, &ShaderErrorMessage[0]);
		std::cout << "Shader frag problem" << &ShaderErrorMessage[0] << std::endl;
	}

	//Check if geometry shader is in used, if true create the geometry shader
	if (isGeoUse == true)
	{
		m_geometryId = glCreateShader(GL_GEOMETRY_SHADER);
		char const* geometrySourcePointer = geometryShaderCode.c_str();
		glShaderSource(m_geometryId, 1, &geometrySourcePointer, NULL);
		glCompileShader(m_geometryId);
		glGetShaderiv(m_geometryId, GL_COMPILE_STATUS, &m_result);
		if (m_result == GL_FALSE) {

			glGetShaderiv(m_result, GL_INFO_LOG_LENGTH, &m_infoLogLength);
			std::vector<char> ShaderErrorMessage(m_infoLogLength + 1);
			glGetShaderInfoLog(m_result, 1024, &m_infoLogLength, &ShaderErrorMessage[0]);
			std::cout << "Shader - %4s\n geo problem" << &ShaderErrorMessage[0] << std::endl;
		}
	}

	m_programId = glCreateProgram();

	if (m_programId == 0)
	{
		std::cout << "Shader - Shader couldn't get program id." << std::endl;
	}
	else 
	{
		glAttachShader(m_programId, m_vertexId);
		glAttachShader(m_programId, m_fragmentId);
		if (isGeoUse == true)
		{
			glAttachShader(m_programId, m_geometryId);
		}
		glLinkProgram(m_programId);

		glGetProgramiv(m_programId, GL_LINK_STATUS, &m_result);

		if (m_infoLogLength > 0) {
			glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &m_infoLogLength);
			std::vector<char> ProgramErrorMessage(m_infoLogLength + 1);
			glGetProgramInfoLog(m_programId, 1024, &m_infoLogLength, &ProgramErrorMessage[0]);
			printf("Shader: %4s\n wrong", &ProgramErrorMessage[0]);
		}
		glDeleteShader(m_vertexId);
		glDeleteShader(m_fragmentId);
		if (isGeoUse == true)
		{
			glDeleteShader(m_geometryId);
		}
	}
}

//Pass uniforms data to the GPU side

//Bind the shader Program
void Shader::Use() const
{
	glUseProgram(m_programId);
}

void Shader::SetBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::SetuInt(const std::string &name, unsigned value) const
{
	glUniform1ui(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

