#include "pch.h"
#include "Core.h"

#include "fileLoader.h"
#include "Input/Input.h"
#include "Math/Math.h"

void Core::Init()
{
	window.init();
	Input::Mouse::cameraPtr = &camera;
	shader.loadShader("ShaderSrc/VertexShader.glsl", "ShaderSrc/FragmentShader.glsl");
	mesh = Mesh(glm::vec3(0.f), glm::vec3(1.f));

	std::vector<std::vector<glm::vec3>> controlPoints = {
		{ glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(2, 0, 0), glm::vec3(3, 0, 0) },
		{ glm::vec3(0, 1, 0), glm::vec3(1, 1, 2), glm::vec3(2, 1, 2), glm::vec3(3, 1, 0) },
		{ glm::vec3(0, 2, 0), glm::vec3(1, 2, 0), glm::vec3(2, 2, 0), glm::vec3(3, 2, 0) }
	};
	m_mesh = MathMesh(Math::CalculateSurface(50,controlPoints));
	m_mesh.SetPosition(glm::vec3(-3.f, 0.f, 0.f));
	fileLoader::ReadBinaryFile("PointsBin.dat");
	m_points = MathMesh(fileLoader::filePosition,true);
}

void Core::Run()
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		Window::ClearBuffers();
		shader.Use();

		camera.UpdateMats(shader.GetProgram());
		//mesh.Render(shader.GetProgram());
		m_mesh.Render(shader.GetProgram());
		m_points.Render(shader.GetProgram(),true);
		Input::processInput(window,camera);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

Core& Core::GetInstance()
{
	static Core core;
	return core;
}
