#pragma once

#include "RenderComponent.h"
#include "Component.h"
#include "Transform.h"

class RenderComponent;
class Renderer;
class Component;
class Transform;

class SceneComponent : public Component
{
 private:
	RenderComponent* _renderComponent = nullptr;
	Transform* _transformComponent = nullptr;
	std::vector<SceneComponent*> child;
 public:
	explicit SceneComponent(const std::wstring* name);
	void SetRenderComponent(RenderComponent* renderComponent) { _renderComponent = renderComponent; }
	void AddChild(SceneComponent* children);
	void RemoveChild(SceneComponent* children);
	void Draw(Renderer* renderer);
};

