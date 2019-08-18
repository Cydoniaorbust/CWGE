#pragma once

#include "External.h"

class Shader {
public:
	static void Use				(GLuint);
	static void CreateShader	(const char*, GLuint, GLuint);
	static GLuint CreateProgram	(const char*, const char*, const char* = nullptr);

	static void SetBool			(GLuint, const std::string &, bool);
	static void SetInt			(GLuint, const std::string &, int);
	static void SetFloat		(GLuint, const std::string &, float);

	static void SetVec2			(GLuint, const std::string &, const glm::vec2 &);
	static void SetVec3			(GLuint, const std::string &, const glm::vec3 &);
	static void SetVec4			(GLuint, const std::string &, const glm::vec4 &);

	static void SetVec2			(GLuint, const std::string &, float, float);
	static void SetVec3			(GLuint, const std::string &, float, float, float);
	static void SetVec4			(GLuint, const std::string &, float, float, float, float);

	static void SetMat2			(GLuint, const std::string &, const glm::mat2 &);
	static void SetMat3			(GLuint, const std::string &, const glm::mat3 &);
	static void SetMat4			(GLuint, const std::string &, const glm::mat4 &);
private:
	Shader() {}
	~Shader() {}

	Shader(const Shader &) = delete;
	Shader& operator=(const Shader &) = delete;
	
	Shader(Shader &&) = delete;
	Shader& operator=(Shader &&) = delete;
};