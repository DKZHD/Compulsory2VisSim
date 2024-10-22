#include "pch.h"
#include "Input.h"

#include <algorithm>

#include "../Camera/Camera.h"

void Input::processInput(GLFWwindow* window, Camera& camera)
{
	if(glfwGetKey(window,GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window,true);
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		camera.UpdateCamPos(Mouse::cameraPtr->camSpeed *glm::cross(camera.getCamFwd(),glm::vec3(0.f,1.f,0.f)));
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		camera.UpdateCamPos(-Mouse::cameraPtr->camSpeed * glm::cross(camera.getCamFwd(), glm::vec3(0.f, 1.f, 0.f)));
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		camera.UpdateCamPos(Mouse::cameraPtr->camSpeed * camera.getCamFwd());
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		camera.UpdateCamPos(-Mouse::cameraPtr->camSpeed * camera.getCamFwd());
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		camera.UpdateCamPos(Mouse::cameraPtr->camSpeed * glm::vec3(0.f,1.f,0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
	{
		camera.UpdateCamPos(-Mouse::cameraPtr->camSpeed * glm::vec3(0.f, 1.f, 0.f));
	}
}

void Input::Mouse::MouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	if(firstMouse)
	{
		prevX = xPos;
		prevY = yPos;
		firstMouse = false;
	}
	double xOffset = xPos - prevX;
	double yOffset = prevY - yPos;
	prevX = xPos;
	prevY = yPos;

	float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += static_cast<float>(xOffset);
	pitch += static_cast<float>(yOffset);

	if (pitch > 89.f)
		pitch = 89.f;
	else if (pitch < -89.f)
		pitch = -89.f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	if (cameraPtr)
		cameraPtr->getCamFwd() = glm::normalize(direction);
}

void Input::Mouse::MouseScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
	cameraPtr->camSpeed = std::clamp(cameraPtr->camSpeed + static_cast<float>(y_offset),0.05f,10.f);
}
