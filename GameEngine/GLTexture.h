#pragma once
#include <GL/glew.h>

struct GLTexture {
	GLuint id;
	GLint width;
	GLint height;
	GLint format;

	GLTexture() : id(0), width(0), height(0), format(0) {}
};