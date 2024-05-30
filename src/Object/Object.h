#pragma once

#include <string>

class Object
{
 private:
	const std::wstring* name;
 public:
	explicit Object(const std::wstring* name);
	~Object();
	[[nodiscard]] const std::wstring* GetName() const { return this->name; };
	virtual void Destroy();
};
