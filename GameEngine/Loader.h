#pragma once
#include "Texture.h"
#include "Model.h"
#include <assimp/scene.h>

class Loader {
public:
	static Texture LoadImage(std::string path);
	static Model* LoadModel(std::string path);

private:
	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, std::string directory);
	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string directory);
	static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, std::string directory);
};