#include "Object.h"

Object::Object(const std::wstring* name) : name(name)
{

}
Object::~Object()
{
	delete name;
}

void Object::Destroy()
{

}
