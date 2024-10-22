#pragma once
#include "ShaderLoader.h"
#include "Window.h"
#include "Camera/Camera.h"
#include "Mesh/Mesh.h"

class Core
{
public:
	Window window;
	Camera camera;
	Shader shader;
	Mesh mesh;
	MathMesh m_mesh;
	MathMesh m_points;
	void Init();
	void Run();
	static Core& GetInstance();
};
