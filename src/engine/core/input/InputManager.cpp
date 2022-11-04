#include "InputManager.h"

#include <GLFW/glfw3.h>
#include <iostream>

char InputManager::m_keybEvent[512]{ 0 };
f32 InputManager::m_mouseX{ 0.0f };
f32 InputManager::m_mouseY{ 0.0f };
glm::vec2 InputManager::m_offsetPosition(0.0f);

void InputManager::init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, updateKeys);
	glfwSetCursorPosCallback(window, updateMouse);
}

bool InputManager::isPressed(char key)
{
	return m_keybEvent[key] == 1;
}

f32 InputManager::getMouseX()
{
	return m_mouseX;
}

f32 InputManager::getMouseY()
{
	return m_mouseY;
}

glm::vec2 InputManager::getMousePosition()
{
	return glm::vec2(m_mouseX, m_mouseY);
}

glm::vec2 InputManager::getMouseOffset()
{
	return glm::vec2();
}

void InputManager::updateKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		m_keybEvent[key] = 1;
		break;

	case GLFW_RELEASE:
		m_keybEvent[key] = 0;
		break;
	}
}

void InputManager::updateMouse(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	m_offsetPosition.x = xpos - m_mouseX;
	m_offsetPosition.y = m_mouseY - ypos;

	m_mouseX = xpos;
	m_mouseY = ypos;
}
