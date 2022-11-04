#pragma once
#include "../engine/rendering/Object.h"

class System;

class CubeTex : public Object
{
public:
	CubeTex(System& system);
	~CubeTex() override = default;

	virtual void update() override;

private:
	System& m_system;
};

