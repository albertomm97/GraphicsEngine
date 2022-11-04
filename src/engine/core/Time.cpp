#include "Time.h"

#include <iostream>

f64 Time::deltaTime = 0.0f;
f64 Time::m_lastFrameTime = 0.0f;

void Time::update()
{
	f64 time = static_cast<f64>(glfwGetTime());
	deltaTime = time - m_lastFrameTime;
	m_lastFrameTime = time;
}

f64 Time::deltaTimeInMs()
{
	return deltaTime * 1000.0f;
}
