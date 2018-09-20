#ifndef _UTILS_H__
#define _UTILS_H__
#pragma once

#include "Dependencies\glew\glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

enum ModelType {

	TRIANGLE = 0,
	QUAD = 1,
	CUBE = 2,
	SPHERE = 3,
	SKYBOXSHAPE
};

struct Position {

	float x, y, z;

	Position(float _x, float _y, float _z) {

		x = _x; y = _y; z = _z;
	}

	Position() {}
};

struct TexCoord {

	float u, v;

	TexCoord(float _u, float _v) {
		u = _u; v = _v;
	}

	TexCoord() {}

};

struct Normals {

	float x, y, z;

	Normals(float _x, float _y, float _z) {

		x = _x; y = _y; z = _z;
	}

	Normals() {}
};

struct VertexFormat {

	Position pos;
	TexCoord texCoord;
	Normals normal;

	VertexFormat(Position _pos, TexCoord _texCoord, Normals _normal) {

		pos = _pos;
		texCoord = _texCoord;
		normal = _normal;

	}

	VertexFormat() {
	}
};

struct IndexFormat {

	int x; int y; int z;

	IndexFormat(int _x, int _y, int _z) {

		x = _x; y = _y; z = _z;
	}
};


class Utils {

public:
	const static int WIDTH = 1280;
	const static int HEIGHT = 720;

	static void setTriData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
	static void setQuadData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
	static void setCubeData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
	static void setSkyBoxData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
	static void setSphereData(std::vector<VertexFormat>& _vertices, std::vector<GLuint>& _indices);
};

#endif // !_UTILS_H__