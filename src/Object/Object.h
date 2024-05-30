#pragma once

#include <string>
class Object
{
 private:
	std::wstring* name;
 public:
	explicit Object(std::wstring* name);
	~Object();
	std::wstring* GetName() { return this->name; };
};
