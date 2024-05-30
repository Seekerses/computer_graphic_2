#pragma once

#include "../../../../Renderer/Renderer.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"

class Renderer;
class ShaderComponent;
class MeshComponent;

class RenderComponent
{
 private:
	Renderer *renderer;
	MeshComponent* mesh;
	ShaderComponent* shader;

	void fitContext();

 public:
	explicit RenderComponent(
		Renderer* _renderer,
		MeshComponent* _mesh,
		ShaderComponent* _shader);
	void Draw();
};
