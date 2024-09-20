#pragma once

#include <string>
#include "Types.h"

class Object
{
 private:
	Id name;
 public:
	explicit Object(Id name);
	~Object();
	[[nodiscard]] Id GetName() const { return this->name; };
	virtual void Destroy();
};
