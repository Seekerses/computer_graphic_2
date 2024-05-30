#pragma once

#include "RenderComponent.h"
#include "Vertex.h"
#include "ShaderComponent.h"
#include "SceneComponent.h"

class RenderComponent;
class ShaderComponent;
class SceneComponent;

class Rectangle : public SceneComponent
{
 public:
	Rectangle(std::wstring* name, Renderer* renderer, Vertex vertices[4], ShaderComponent* shaderComponent);
};
