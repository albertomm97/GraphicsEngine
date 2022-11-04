#pragma once

#include "../engine/rendering/Object.h"

class System;

class CubeIndices : public Object
{
public:
	CubeIndices(System& system);
	~CubeIndices() override = default;

	virtual void update() override;

private:
	System& m_system;
};

