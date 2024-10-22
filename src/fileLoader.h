#pragma once
#include "Mesh/Mesh.h"

class fileLoader
{
public:
	static inline std::vector<glm::vec3> filePosition;
	static void LoadFile(const char* path);
	static void WriteBinaryFile(const char* path);
	static void ReadBinaryFile(const char* path);
};
