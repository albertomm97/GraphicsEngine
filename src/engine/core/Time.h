#pragma once

#include "../core/common/Types.h"

#include <GLFW/glfw3.h>

class Time
{
public:
	static f64 deltaTimeInMs();
	static f64 deltaTime;

	friend class System;
private:
	static void update();
	static f64 m_lastFrameTime;
};
