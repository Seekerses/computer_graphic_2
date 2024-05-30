#include "SceneComponent.h"

SceneComponent::SceneComponent(const std::wstring* name) : Component(name)
{
	_transformComponent = new Transform();
}

void SceneComponent::Draw(Renderer* renderer)
{
	_renderComponent->Draw(renderer, _transformComponent);
	for (auto children: child) {
		children->Draw(renderer);
	}
}

void SceneComponent::AddChild(SceneComponent* children)
{
	this->child.emplace_back(children);
}

void SceneComponent::RemoveChild(SceneComponent* children)
{
	auto it = std::find(child.begin(), child.end(), children);
	if (it != child.end()) {
		child.erase(it);
	}
}
