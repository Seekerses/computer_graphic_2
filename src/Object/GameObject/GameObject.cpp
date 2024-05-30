#include "GameObject.h"

GameObject::GameObject(const std::wstring* name) : Object(name)
{

}
void GameObject::Destroy()
{
	Object::Destroy();
}
