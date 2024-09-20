#pragma once

class SingletonManager
{
 public:
	virtual void Release() = 0;
	virtual ~SingletonManager() = default;
};
