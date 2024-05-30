#pragma once

#include "DirectXMath.h"
#include "../Components/Scene/Render/RenderComponent.h"
#include "../../Renderer/Renderer.h"
#include "../../Renderer/Vertex.h"
#include "../Components/Scene/Render/ShaderComponent.h"
#include "../Components/Scene/SceneComponent.h"

class Rectangle : public SceneComponent
{
 public:
	Rectangle(std::wstring* name, Renderer* renderer, Vertex vertices[4], ShaderComponent* shaderComponent);
};
