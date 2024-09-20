#include "SceneComponent.h"

SceneComponent::SceneComponent(const Id& name)
	: Component(name)
{
	_transform = Transform ();
	_transform.position = DirectX::XMFLOAT4{ .0f, .0f, .0f, .0f };
	_transform.rotation = DirectX::XMFLOAT4{ .0f, .0f, .0f, .0f };
	_transform.scale = DirectX::XMFLOAT4{ 1.f, 1.f, 1.f, 1.f };
}

void SceneComponent::Draw()
{
	_renderComponent->Draw(_transform, _color);
	for (auto children : child)
	{
		children->Draw();
	}
}

void SceneComponent::AddChild(SceneComponent* children)
{
	this->child.emplace_back(children);
}

void SceneComponent::RemoveChild(SceneComponent* children)
{
	auto it = std::find(child.begin(), child.end(), children);
	if (it != child.end())
	{
		child.erase(it);
	}
}
void SceneComponent::AddPosition(DirectX::XMFLOAT3 deltaPosition)
{
	_transform.position.x += deltaPosition.x;
	_transform.position.y += deltaPosition.y;
	_transform.position.z += deltaPosition.z;
}
void SceneComponent::AddScale(DirectX::XMFLOAT3 deltaScale)
{
	_transform.scale.x += deltaScale.x;
	_transform.scale.y += deltaScale.y;
	_transform.scale.z += deltaScale.z;
}

void SceneComponent::AddRotation(DirectX::XMFLOAT3 deltaRotation)
{
	_transform.rotation.x += deltaRotation.x;
	_transform.rotation.y += deltaRotation.y;
	_transform.rotation.z += deltaRotation.z;
}
