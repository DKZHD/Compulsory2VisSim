#pragma once
class Camera;

namespace Input
{
	void processInput(GLFWwindow* window, Camera& camera);

	class Mouse
	{
	public:
		static void MouseMoveCallback(GLFWwindow* window, double xPos, double yPos);
		static void MouseScrollCallback(GLFWwindow* window, double x_offset, double y_offset);
		inline static Camera* cameraPtr = nullptr;
	private:
		inline static bool firstMouse = true;
		inline static double prevX = 0, prevY = 0;
		inline static float pitch = 0.f, roll = 0.f, yaw = -90.f;
	};
	
};

