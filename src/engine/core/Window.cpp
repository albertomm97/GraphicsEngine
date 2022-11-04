#include "Window.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

Window::Window(WindowParameters& parameters)
	: m_parameters{ parameters }
{
	int glfwState = glfwInit();
	if (!glfwState)
		throw std::runtime_error("Error initializing glfw");

	m_window = glfwCreateWindow(parameters.width, parameters.height, parameters.name.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_window);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, parameters.majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, parameters.minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, parameters.resizable);

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);

	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("INFO max settings supported");
	printf("GL Vendor : %s\n", vendor);
	printf("GL Renderer : %s\n", renderer);
	printf("GL Version (string) : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version : %s\n", glslVersion);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::poolEvents() const
{
	glfwPollEvents();
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_window);
}

bool Window::windowShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::get() const
{
	return m_window;
}

glm::vec2 Window::getWindowExtent()
{
	return glm::vec2(m_parameters.width, m_parameters.height);
}
