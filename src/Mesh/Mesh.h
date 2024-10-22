#pragma once
struct Vertex
{
	glm::vec3 pos;
	Vertex(glm::vec3 pos) : pos(pos){}
};
class Mesh
{
public:
	Mesh() = default;
	Mesh(glm::vec3 pos, glm::vec3 scale);
	void UpdatePosition(glm::vec3 pos);
	void Render(uint32_t program) const;
private:

	void BindBuffer();

	uint32_t vbo = 0, ebo = 0, vao = 0;
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	glm::vec3 position;
	glm::vec3 scale;
};
class MathMesh
{
public:
	MathMesh() = default;
	MathMesh(std::vector<glm::vec3> v, bool point_cloud = false);
	void SetPosition(glm::vec3 v) { position = v; }
	void Render(uint32_t program, bool point_cloud = false) const;
private:
	void BindBuffer();
	uint32_t vbo = 0, ebo = 0, vao = 0;
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<glm::vec3> normals;

	glm::vec3 position;
	glm::vec3 scale;
};

