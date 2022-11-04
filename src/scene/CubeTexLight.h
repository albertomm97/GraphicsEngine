#pragma once

#include "../engine/rendering/Object.h"

class System;

class CubeTexLight : public Object
{
public:
	CubeTexLight(System& system);
	~CubeTexLight() override = default;

	virtual void update() override;

private:
	System& m_system;
};

