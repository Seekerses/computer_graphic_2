#pragma once

#include "../Components/Scene/Render/RenderComponent.h"
#include "../Components/Scene/Render/ShaderComponent.h"
#include "DirectXMath.h"
#include "../Components/Scene/SceneComponent.h"

class SceneComponent;

class Triangle : public SceneComponent
{
 public:
	Triangle(std::wstring* name, Renderer* renderer, Vertex vertices[3], ShaderComponent* shaderComponent);
};
