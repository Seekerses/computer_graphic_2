#pragma once

#include "Types.h"
#include "Transform.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"

class RenderComponent
{
 private:
	MeshComponent* mesh;
	ShaderComponent* shader;

	void swapContext(Transform transform, Color color);

 public:
	explicit RenderComponent(
		MeshComponent* _mesh,
		ShaderComponent* _shader);
	void Draw(Transform transform, Color color);
};
