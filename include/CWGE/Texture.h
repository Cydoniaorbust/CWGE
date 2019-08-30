#pragma once

#include "External.h"

class Texture {
public:
	GLuint Id;
	std::string Path;
	std::string Type;

	void Bind();
	void Unbind();
	void Generate(unsigned char*, GLenum, GLuint, GLuint);
	void LoadFromFile(const std::string &);
	
	Texture();
	Texture(const std::string &, const std::string &);
	Texture(const Texture &);
	Texture(Texture &&);
	~Texture();

	void Swap(Texture &);
	Texture& operator=(const Texture &);
	Texture& operator=(Texture &&);
};