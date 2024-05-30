#pragma once

#include <vector>
#include "Object.h"
#include "Component.h"

class Component;

class GameObject : public Object
{
 private:
	std::vector<Component*> components;
 public:
	explicit GameObject(const std::wstring* name);
	void Destroy() override;
};
