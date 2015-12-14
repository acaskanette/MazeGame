#pragma once
#include "Texture.h"
#include "Model.h"
#include <map>

class TextureCache {
public:
	Texture GetTexture(std::string path);

	TextureCache() {}
private:
	std::map<std::string, Texture> textureMap;
};

class ModelCache {
public:
	Model* GetModel(std::string path);

	ModelCache() {};
private:
	std::map<std::string, Model*> modelMap;
};

class ResourceManager {
public:
	// Get (and create) the ResourceManager instance
	static ResourceManager* GetInstance();
	// Deletes the resource manager and the pointer to it
	void DestroyResourceManager(ResourceManager*& rmPtr);

	Texture LoadTexture(std::string path);
	Model* LoadModel(std::string path);
private:
	static ResourceManager* instance;

	TextureCache textureCache;
	ModelCache modelCache;

	ResourceManager() {}
	~ResourceManager() {}
};