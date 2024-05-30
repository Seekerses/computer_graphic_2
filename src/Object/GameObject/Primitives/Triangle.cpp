#include "Triangle.h"

Triangle::Triangle(std::wstring* name, Renderer* renderer, Vertex vertices[3], ShaderComponent* shaderComponent) : SceneComponent(name)
{
	const UINT indices[] = {0, 1, 2};
	const UINT* strides = new UINT[] { sizeof(Vertex) };
	const UINT* offsets = new UINT[] { 0 };
	auto* mesh = new MeshComponent(
		renderer,
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		vertices, 3,
		indices, 3,
		strides, offsets);
	SetRenderComponent(new RenderComponent(mesh, shaderComponent));
}