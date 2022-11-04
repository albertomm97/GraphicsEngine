#pragma once

#include "../engine/rendering/Object.h"

class System;

class Bunny : public Object
{
public:
	Bunny(System& system);
	~Bunny() override = default;

	virtual void update() override;

private:
	System& m_system;
};

