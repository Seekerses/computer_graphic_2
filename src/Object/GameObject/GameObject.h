#pragma once

#include <vector>
#include "Types.h"
#include "Object.h"
#include "Component.h"
#include "SceneComponent.h"

class GameObject : public Object
{
 private:
	SceneComponent* sceneComponent = nullptr;
	std::vector<Component*> components;
 public:
	DirectX::XMFLOAT4 collision;
	explicit GameObject(const Id& name);
	void AddComponent(Component* component) { this->components.emplace_back(component); }
	Component* GetComponent(Id name);
	void Destroy() override;
	virtual void FixedUpdate(float deltaTime) {};
	SceneComponent* GetSceneComponent() { return sceneComponent; }
	void SetSceneComponent(SceneComponent* _sceneComponent) { this->sceneComponent = _sceneComponent; }
	void SetCollision(DirectX::XMFLOAT4 rect) { this->collision = rect; };
	virtual void OnCollisionEnter(DirectX::XMFLOAT4 rec);
	virtual DirectX::XMFLOAT4 GetCollision();
};
