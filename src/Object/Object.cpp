#include "Object.h"
Object::Object(std::wstring* name) : name(name)
{

}
Object::~Object()
{
	delete name;
}
