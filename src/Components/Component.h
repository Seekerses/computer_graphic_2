#pragma once

#include "Object.h"

class Component : public Object
{
 public:
	explicit Component(const std::wstring* name);
};
