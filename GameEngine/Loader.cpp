#include "Loader.h"
#include "picoPNG.h"
#include "LogManager.h"

GLTexture Loader::LoadPNG(std::string _filePath) {
	// Create a GLTexture and initialize all its fields to 0
	GLTexture texture = {};

	// This is the input data to decodePNG, which we load from a file
	std::vector<unsigned char> in;
	// This is the output data from decodePNG, which is the pixel data for our texture
	std::vector<unsigned char> out;
	// Width and height of the image
	unsigned long width, height;

	// Start reading in the image file contents to the buffer
	// Open the PNG file
	std::ifstream file(_filePath, std::ios::binary);
	if (file.fail())
		LogManager::getInstance().logFatal("Failed to load PNG file to buffer!: " + _filePath);

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
		LogManager::getInstance().logFatal("decodePNG failed with error: " + std::to_string(errorCode));

	// Generate the OpenGL texture object
	glGenTextures(1, &texture.id);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture.id);
	// Upload the pixels to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	// Get the format of the image
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPONENTS, &texture.format);

	// Set some texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Generate the mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	// Return a copy of the texture data
	return texture;
}