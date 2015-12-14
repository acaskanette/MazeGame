#include "Loader.h"
#include "picoPNG.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Texture Loader::LoadImage(std::string path) {
	// Create a GLTexture and initialize all its fields to 0
	Texture texture;

	// This is the input data to decodePNG, which we load from a file
	std::vector<unsigned char> in;
	// This is the output data from decodePNG, which is the pixel data for our texture
	std::vector<unsigned char> out;
	// Width and height of the image
	unsigned long width, height;

	// Start reading in the image file contents to the buffer
	// Open the PNG file
	std::ifstream file(path, std::ios::binary);
	if (file.fail())
		LogManager::GetInstance()->LogFatal("Failed to load PNG file to buffer!: " + path);

	// Seek to the end
	file.seekg(0, std::ios::end);

	// Get the file size
	int fileSize = (int)file.tellg();
	file.seekg(0, std::ios::beg);

	// Reduce the file size by any header bytes that might be present
	fileSize -= (int)file.tellg();

	in.resize(fileSize);
	file.read((char *)&(in[0]), fileSize);
	file.close();

	// Decode the .png format into an array of pixels
	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0)
		LogManager::GetInstance()->LogFatal("decodePNG failed with error: " + std::to_string(errorCode));

	// Generate the OpenGL texture object
	glGenTextures(1, &texture.id);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture.id);
	// Upload the pixels to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	// Set some texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Generate the mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Return a copy of the texture data
	return texture;
}

Model* Loader::LoadModel(std::string path) {
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		LogManager::GetInstance()->LogFatal("AssImp error: " + std::string(import.GetErrorString()));

	std::vector<Mesh> meshes;
	std::string directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene, meshes, directory);

	return new Model(meshes);
}

void Loader::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, std::string directory) {
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene, directory));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
		ProcessNode(node->mChildren[i], scene, meshes, directory);
}

Mesh Loader::ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string directory) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		// Process vertex positions, normals and texture coordinates
		glm::vec3 vector;

		// Get position data
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;
		// Get normal data
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;
		// Get UV data
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.uv = vec;
		} else
			vertex.uv = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	// Process indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Process material
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", directory);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Loader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, std::string directory) {
	std::vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture = ResourceManager::GetInstance()->LoadTexture(directory + "/" + str.C_Str());
		texture.type = typeName;
		textures.push_back(texture);
	}
	return textures;
}