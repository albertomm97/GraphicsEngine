#pragma once
#include "common/Types.h"

#include <string>
#include <glm/glm.hpp>

struct GLFWwindow;

struct WindowParameters
{
	std::string name;
	u32 width;
	u32 height;
	u32 majorVersion{ 4 };
	u32 minorVersion{ 3 };
	u32 resizable;
};

class Window
{
public:
	Window(WindowParameters& parameters);
	~Window();
	void poolEvents() const;
	void swapBuffers() const;
	bool windowShouldClose() const;
	GLFWwindow* get() const;
	glm::vec2 getWindowExtent();

private:
	GLFWwindow* m_window;
	WindowParameters& m_parameters;
};

