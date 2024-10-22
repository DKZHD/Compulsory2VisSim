#pragma once

class Window
{
public:
	void init();
	static void ClearBuffers();
	operator GLFWwindow* () const
	{
		return s_window;
	}
private:
	GLFWwindow* s_window = nullptr;
};

