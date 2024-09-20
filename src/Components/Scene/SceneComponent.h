#pragma once

#include "Types.h"
#include "Component.h"
#include "Transform.h"
#include "Renderable.h"
#include "RenderComponent.h"

class SceneComponent : public Component, public Renderable
{
 private:
	RenderComponent* _renderComponent = nullptr;
	Transform _transform {};
	Color _color {};
	std::vector<SceneComponent*> child;
 public:
	explicit SceneComponent(const Id& name);
	void SetRenderComponent(RenderComponent* renderComponent) { _renderComponent = renderComponent; }
	void AddChild(SceneComponent* children);
	void RemoveChild(SceneComponent* children);
	void Draw() override;
	Transform GetTransform() { return this->_transform; }
	Color GetColor() { return this->_color; }
	void SetTransform(Transform transform) { this->_transform = transform; }
	void SetColor(Color color) { this->_color = color; }
	void AddPosition(DirectX::XMFLOAT3 deltaPosition);
	void SetPosition(DirectX::XMFLOAT4 position) { this->_transform.position = position; }
	void AddScale(DirectX::XMFLOAT3 deltaScale);
	void SetScale(DirectX::XMFLOAT4 scale) { this->_transform.scale = scale; }
	void AddRotation(DirectX::XMFLOAT3 deltaRotation);
	void SetRotation(DirectX::XMFLOAT4 rotation) { this->_transform.rotation = rotation; }
};

