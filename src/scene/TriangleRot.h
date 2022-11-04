#pragma once

#include "../engine/rendering/Object.h"

class System;

class TriangleRot : public Object
{
public:
	TriangleRot(System& system);
	~TriangleRot() override = default;

	virtual void update() override;

private:
	System& m_system;
};

