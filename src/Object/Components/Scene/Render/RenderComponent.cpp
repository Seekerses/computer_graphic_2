#include "RenderComponent.h"

RenderComponent::RenderComponent(
	Renderer* _renderer,
	MeshComponent* _mesh,
	ShaderComponent* _shader)
	:
	renderer(_renderer),
	mesh(_mesh),
	shader(_shader)
{
}

void RenderComponent::Draw()
{
	fitContext();
	renderer->GetContext()->DrawIndexed(
		mesh->GetIndexesNumber(),
		0,
		0);
}

void RenderComponent::fitContext()
{
	shader->SwapContext(renderer);
	mesh->SwapContext(renderer);
}
