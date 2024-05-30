#pragma once

#include "RenderComponent.h"
#include "ShaderComponent.h"
#include "SceneComponent.h"

class SceneComponent;
class RenderComponent;
class SceneComponent;

class Triangle : public SceneComponent
{
 public:
	Triangle(std::wstring* name, Renderer* renderer, Vertex vertices[3], ShaderComponent* shaderComponent);
};
