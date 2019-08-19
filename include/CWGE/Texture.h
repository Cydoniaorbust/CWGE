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
	void LoadFromFile(std::string);
	
	Texture();
	Texture(std::string, std::string);
	Texture(const Texture &);
	Texture(Texture &&);
	~Texture();

	void Swap(Texture &);
	Texture& operator=(const Texture &);
	Texture& operator=(Texture &&);
};