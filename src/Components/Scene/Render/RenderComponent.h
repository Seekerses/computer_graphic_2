#pragma once

#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "Transform.h"

class ShaderComponent;
class MeshComponent;
class Transform;

class RenderComponent
{
 private:
	MeshComponent* mesh;
	ShaderComponent* shader;

	void swapContext(Renderer* renderer);

 public:
	explicit RenderComponent(
		MeshComponent* _mesh,
		ShaderComponent* _shader);
	void Draw(Renderer* renderer, Transform* transform);
};
