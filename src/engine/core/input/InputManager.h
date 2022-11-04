#pragma once
#include "../common/Types.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager
{
public:
	InputManager() = delete;
	~InputManager() = delete;

	static void init(GLFWwindow* window);
	static bool isPressed(char key);
	static f32 getMouseX();
	static f32 getMouseY();
	static glm::vec2 getMousePosition();
	static glm::vec2 getMouseOffset();

private:
	static void updateKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void updateMouse(GLFWwindow* window, double xposIn, double yposIn);
	static char m_keybEvent[512];
	static f32 m_mouseX, m_mouseY;
	static glm::vec2 m_offsetPosition;
};