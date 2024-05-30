#include "Rectangle.h"

Rectangle::Rectangle(std::wstring* name, Renderer* renderer, Vertex* vertices, ShaderComponent* shaderComponent) : SceneComponent(name)
{
	const UINT indices[] = {0, 1, 2, 1, 0, 3};
	const UINT* strides = new UINT[] { sizeof(Vertex) };
	const UINT* offsets = new UINT[] { 0 };
	auto* mesh = new MeshComponent(
		renderer,
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		vertices, 4,
		indices, 6,
		strides, offsets);
	SceneComponent::SetRenderComponent(new RenderComponent(mesh, shaderComponent));
}