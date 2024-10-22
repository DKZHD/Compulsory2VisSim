#include "pch.h"
#include "Window.h"

#include "Input/Input.h"

void Window::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	s_window = glfwCreateWindow(1920, 1080, "Compulsory2", nullptr, nullptr);
	if (!s_window)
		throw;
	glfwMakeContextCurrent(s_window);
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw;
	glViewport(0, 0, 1920, 1080);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(s_window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(s_window, &Input::Mouse::MouseMoveCallback);
	glfwSetScrollCallback(s_window, Input::Mouse::MouseScrollCallback);
	glPointSize(5.f);
}

void Window::ClearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.3f, 0.6f, 1.f);
}
