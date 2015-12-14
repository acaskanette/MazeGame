#include "ResourceManager.h"
#include "Loader.h"
#include "LogManager.h"
#include <utility>

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::GetInstance() {
	if (instance == nullptr)
		instance = new ResourceManager();

	return instance;
}

void ResourceManager::DestroyResourceManager(ResourceManager*& resourceManagerPointer) {
	if (instance) {
		delete instance;
		instance = nullptr;
		resourceManagerPointer = nullptr;
	}
}

Texture ResourceManager::LoadTexture(std::string path) {
	return textureCache.GetTexture(path);
}

Model* ResourceManager::LoadModel(std::string path) {
	return modelCache.GetModel(path);
}

Texture TextureCache::GetTexture(std::string path) {
	auto mit = textureMap.find(path);

	// Check if its not in the map
	if (mit == textureMap.end()) {
		// Load the texture
		Texture texture = Loader::LoadImage(path);

		// Insert it into the map
		textureMap.insert(std::make_pair(path, texture));

		LogManager::GetInstance()->LogInfo("Loaded new texture: " + path);
		return texture;
	}

	// If it was in the map already
	LogManager::GetInstance()->LogInfo("Loaded texture from cache: " + path);
	return mit->second;
}

Model* ModelCache::GetModel(std::string path) {
	auto mit = modelMap.find(path);

	// Check if its not in the map
	if (mit == modelMap.end()) {
		// Load the texture
		Model* model = Loader::LoadModel(path);

		// Insert it into the map
		modelMap.insert(std::make_pair(path, model));

		LogManager::GetInstance()->LogInfo("Loaded new model: " + path);
		return model;
	}

	// If it was in the map already
	LogManager::GetInstance()->LogInfo("Loaded model from cache: " + path);
	return mit->second;
}