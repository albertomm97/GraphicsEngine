#pragma once

#include "../engine/rendering/Object.h"

class System;

class TriangleRotTex : public Object
{
public:
	TriangleRotTex(System& system);
	~TriangleRotTex() override = default;

	virtual void update() override;

private:
	System& m_system;
};

