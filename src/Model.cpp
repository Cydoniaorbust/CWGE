#include "Model.h"

Mesh::Mesh(std::vector<Vertex> ver, std::vector<GLuint> ind, std::vector<Texture> tex) : Vertices(ver), Indices(ind), Textures(tex) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1); glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2); glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(3); glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	glEnableVertexAttribArray(4); glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}

void Mesh::Draw(GLuint _shader) {
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	for (GLuint i = 0; i < Textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string name = Textures[i].Type;
		std::string number = (name == "texture_diffuse") ? std::to_string(diffuseNr++) : std::to_string(specularNr++);
		Shader::SetInt(_shader, "material." + name + number, i);
		Textures[i].Bind();
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
void Mesh::DrawOther(GLuint _shader) {
	glActiveTexture(GL_TEXTURE0 + 2);
	Shader::SetInt(_shader, "Texture", 2);
	Textures[0].Bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Model::Draw(GLuint shader) { 
	for (GLuint i = 0; i < meshes.size(); i++) meshes[i].Draw(shader); 
}
void Model::DrawOther(GLuint shader) { 
	for (GLuint i = 0; i < meshes.size(); i++) meshes[i].DrawOther(shader);
}

Model::Model() {};
Model::Model(const std::string & path) {
	loadModel(path); 
}

void Model::loadModel(const std::string & path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); // | aiProcess_GenNormals | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	dir = path.substr(0, path.find_last_of('/'));
	AI_MATKEY_TEXFLAGS(aiTextureFlags::aiTextureFlags_UseAlpha, 1);
	processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene) {
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (GLuint i = 0; i < node->mNumChildren; i++) processNode(node->mChildren[i], scene);
}
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> texs;

	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		//vector.x = mesh->mTangents[i].x;
		//vector.y = mesh->mTangents[i].y;
		//vector.z = mesh->mTangents[i].z;
		//vertex.Tangent = vector;
		//vector.x = mesh->mBitangents[i].x;
		//vector.y = mesh->mBitangents[i].y;
		//vector.z = mesh->mBitangents[i].z;
		//vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
	}

	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<Texture> diffuseMaps = loadTexs(mat, aiTextureType_DIFFUSE, "tex_diffuse"); texs.insert(texs.end(), diffuseMaps.begin(), diffuseMaps.end());
	std::vector<Texture> specularMaps = loadTexs(mat, aiTextureType_SPECULAR, "tex_specular"); texs.insert(texs.end(), specularMaps.begin(), specularMaps.end());
	std::vector<Texture> normalMaps = loadTexs(mat, aiTextureType_NORMALS, "tex_normal"); texs.insert(texs.end(), normalMaps.begin(), normalMaps.end());
	std::vector<Texture> heightMaps = loadTexs(mat, aiTextureType_HEIGHT, "tex_height"); texs.insert(texs.end(), heightMaps.begin(), heightMaps.end());
	std::vector<Texture> opacityMaps = loadTexs(mat, aiTextureType_OPACITY, "tex_opacity"); texs.insert(texs.end(), opacityMaps.begin(), opacityMaps.end());

	return Mesh(vertices, indices, texs);
}
std::vector<Texture> Model::loadTexs(aiMaterial *mat, aiTextureType type, const std::string & typeName) {
	std::vector<Texture> texs;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;

		mat->GetTexture(type, i, &str);
		texs.push_back(Texture(dir + '/' + str.C_Str(), typeName));
	}

	return texs;
}