#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(glm::vec3 pos, glm::vec3 scale) : position(pos),scale(scale)
{
	vertices = {
		glm::vec3(-0.5,-0.5,0.5),
		glm::vec3(0.5,-0.5,0.5),
		glm::vec3(0.5,0.5,0.5),
		glm::vec3(-0.5,0.5,0.5),
		glm::vec3(-0.5,-0.5,-0.5),
		glm::vec3(0.5,-0.5,-0.5),
		glm::vec3(0.5,0.5,-0.5),
		glm::vec3(-0.5,0.5,-0.5)
	};

	indices = {
		0,1,2,2,3,0,
		0,3,7,7,4,0,
		3,2,6,6,7,3,
		1,5,6,6,2,1,
		0,4,5,5,1,0,
		4,5,6,6,7,4
	};
	BindBuffer();
}

void Mesh::UpdatePosition(glm::vec3 pos)
{
	position += pos;
}

void Mesh::Render(uint32_t program) const
{
	glBindVertexArray(vao);
	glm::mat4 model(1.f);
	model = glm::translate(model, position);
	glUniformMatrix4fv(glGetUniformLocation(program, "Model"), 1, GL_FALSE, &model[0][0]);
	glDrawElements(GL_TRIANGLES,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_INT,nullptr);
}

void Mesh::BindBuffer()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1,&ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),nullptr);
	glBindVertexArray(0);
}

MathMesh::MathMesh(std::vector<glm::vec3> v, bool point_cloud)
{
	position = glm::vec3(0.f);
	vertices.reserve(v.size());

	for (auto& vec3 : v)
	{
		vertices.emplace_back(vec3);
	}
	int numPrRow = sqrt(v.size());
	if(!point_cloud)
	{
		for (int i = 0; i < numPrRow - 1; i++)
		{
			for (int j = 0; j < numPrRow - 1; j++)
			{
				indices.emplace_back(i * numPrRow + j);
				indices.emplace_back(i * numPrRow + j + 1);
				indices.emplace_back(i * numPrRow + numPrRow + j + 1);
				indices.emplace_back(i * numPrRow + numPrRow + j + 1);
				indices.emplace_back(i * numPrRow + numPrRow + j);
				indices.emplace_back(i * numPrRow + j);
			}
		}
	}

	BindBuffer();
}




void MathMesh::Render(uint32_t program, bool point_cloud) const
{
	glBindVertexArray(vao);
	glm::mat4 model(1.f);
	model = glm::translate(model, position);
	glUniformMatrix4fv(glGetUniformLocation(program, "Model"), 1, GL_FALSE, &model[0][0]);
	if(point_cloud)
		glDrawArrays(GL_POINTS,0,vertices.size());
	else 
		glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,nullptr);

	GLenum error = glGetError();
	if(error!=GL_NO_ERROR)
	{
		std::cout << "Error: " << error << '\n';
	}
}

void MathMesh::BindBuffer()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glBindVertexArray(0);
}
