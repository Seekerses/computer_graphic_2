#pragma once

#include "Render/RenderComponent.h"
#include "../Component.h"
#include "Transform.h"

class RenderComponent;

class SceneComponent : public Component
{
 private:
	RenderComponent* render = nullptr;
	Transform* transform = nullptr;
	std::vector<SceneComponent*> child;
 public:
	explicit SceneComponent(std::wstring* name);
	void SetRenderComponent(RenderComponent* renderComponent) { this->render = renderComponent; }
	void AddChild(SceneComponent* children);
	void RemoveChild(SceneComponent* children);
	void PrintHierarchy(int depth);
	void Draw();
};

