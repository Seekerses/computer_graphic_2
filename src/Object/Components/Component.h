//
// Created by seekerses on 30.05.2024.
//

#pragma once

#include "../Object.h"

class Component : public Object
{
 public:
	explicit Component(std::wstring* name);
};
