#pragma once

#include "External.h"

#include "Shader.h"
#include "Texture.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

class Mesh {
public:
	GLuint VAO, VBO, EBO;
	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	std::vector<Texture> Textures;

	Mesh(std::vector<Vertex>, std::vector<GLuint>, std::vector<Texture>);

	void Draw(GLuint);
	void DrawOther(GLuint);
};

class Model {
private:
	std::vector<Mesh> meshes;
	std::string dir;
public:
	void Draw(GLuint);
	void DrawOther(GLuint);

	Model();
	Model(const std::string &);
private:
	void loadModel(const std::string &);
	void processNode(aiNode *, const aiScene *);
	Mesh processMesh(aiMesh *, const aiScene *);
	std::vector<Texture> loadTexs(aiMaterial *, aiTextureType, const std::string &);
};