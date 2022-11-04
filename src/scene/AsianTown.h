#pragma once

#include "../engine/rendering/Object.h"

class System;


class AsianTown : public Object
{
public:
	AsianTown(System& system);
	~AsianTown() override = default;

	virtual void update() override;

private:
	System& m_system;
};

