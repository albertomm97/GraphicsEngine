#pragma once

#include "Object.h"

class Object3D : public Object
{
public:
	Object3D() = default;
	virtual ~Object3D() override = default;

	//void loadDataFromFile(const std::string& filePath) override;
};

