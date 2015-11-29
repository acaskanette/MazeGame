#pragma once
#include <GL/glew.h>
#include <GLM/glm.hpp>

struct Position {
	GLfloat x, y, z;

	Position(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z) {}
	Position() : x(0), y(0), z(0) {}
};

struct Color {
	GLfloat r, g, b, a;

	Color(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a) : r(_r), g(_r), b(_b), a(_a) {}
	Color() : r(1.0F), g(1.0F), b(1.0F), a(1.0F) {}
};

struct UV {
	GLfloat u, v;

	UV(GLfloat _u, GLfloat _v) : u(_u), v(_v) {}
	UV() : u(0), v(0) {}
};

struct Normal {
	GLfloat x, y, z;

	Normal(GLfloat _x, GLfloat _y, GLfloat _z) : x(_x), y(_y), z(_z) {}
	Normal() : x(0), y(0), z(0) {}
};

struct Vertex {
	Position position;
	Color color;
	UV uv;
	Normal normal;

	Vertex() {}

	Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 uv, glm::vec3 normal = glm::vec3(0)) {
		SetPosition(position.x, position.y, position.z);
		SetColor(color.r, color.g, color.b, color.a);
		SetUV(uv.x, uv.y);
		SetNormal(normal.x, normal.y, normal.z);
	}

	void SetPosition(GLfloat x, GLfloat y, GLfloat z) {
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void SetUV(GLfloat u, GLfloat v) {
		uv.u = u;
		uv.v = v;
	}

	void SetNormal(GLfloat x, GLfloat y, GLfloat z) {
		normal.x = x;
		normal.y = y;
		normal.z = z;
	}
};