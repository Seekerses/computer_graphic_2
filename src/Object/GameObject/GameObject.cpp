#include "GameObject.h"
#include "RenderManager.h"

GameObject::GameObject(const Id& name) : Object(name)
{

}
void GameObject::Destroy()
{
	Object::Destroy();
}
Component* GameObject::GetComponent(Id name)
{
	auto it = std::find_if(this->components.begin(), this->components.end(), [&name](const auto* val) {
		return val->GetName() == name;
	});
	if (it == components.end()) {
		return nullptr;
	}
	else{
		return *it;
	}
}
void GameObject::OnCollisionEnter(DirectX::XMFLOAT4 rec)
{

}

DirectX::XMFLOAT4 GameObject::GetCollision()
{
	DirectX::XMFLOAT4 rect = {};
	rect.x = -GetSceneComponent()->GetTransform().scale.x;
	rect.y = -GetSceneComponent()->GetTransform().scale.y;
	rect.x /= RenderManager::Get()->GetWindow()->GetRatio();
	rect.z = 1 * collision.x;
	rect.w = 1 * collision.y;
	rect.x += GetSceneComponent()->GetTransform().position.x;
	rect.y += GetSceneComponent()->GetTransform().position.y;
	rect.z *= GetSceneComponent()->GetTransform().scale.x * 2;
	rect.w *= GetSceneComponent()->GetTransform().scale.y * 2;

	rect.z /= RenderManager::Get()->GetWindow()->GetRatio();
	return rect;
}
