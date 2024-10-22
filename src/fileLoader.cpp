#include "pch.h"
#include "fileLoader.h"

#include <fstream>
#include <sstream>

void fileLoader::LoadFile(const char* path)
{
	
	std::ifstream inFile(path);
	if (!inFile.is_open())
		throw;
	while(!inFile.eof())
	{
		if(inFile.peek()=='T')
		{
			std::string s;
			std::getline(inFile, s);
			std::getline(inFile, s);
			std::stringstream ss(s);
			int i;
			ss >> i;
			filePosition.reserve(i);
		}
			
		if(inFile.eof())
			break;
			std::string s;
			std::getline(inFile, s);
			std::stringstream ss(s);

			glm::vec3 p(0.f);
			ss >> p.x >> p.y >> p.z;
			filePosition.emplace_back(p);
		}
	}

void fileLoader::WriteBinaryFile(const char* path)
{
	std::ofstream outFile(path, std::ios::binary);
	if (!outFile.is_open())
		throw;
	size_t size = filePosition.size();
	outFile.write(reinterpret_cast<const char*>(&size),sizeof(size_t));
	for(const auto& pos : filePosition)
	{
		outFile.write(reinterpret_cast<const char*>(&pos), sizeof(glm::vec3));
	}
	outFile.close();
}

void fileLoader::ReadBinaryFile(const char* path)
{
	std::ifstream infile(path, std::ios::binary);
	if (!infile.is_open())
		throw;
	size_t size;
	infile.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	filePosition.reserve(size);

	for(size_t i = 0; i < size; i++)
	{
		glm::vec3 pos(0.f);
		infile.read(reinterpret_cast<char*>(&pos), sizeof(glm::vec3));
		filePosition.emplace_back(pos);
	}
	infile.close();
}
