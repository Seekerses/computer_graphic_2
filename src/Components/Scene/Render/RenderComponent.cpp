#include "RenderComponent.h"

RenderComponent::RenderComponent(
	MeshComponent* _mesh,
	ShaderComponent* _shader) : mesh(_mesh), shader(_shader)
{

}

void RenderComponent::Draw(Renderer* renderer, Transform* transform)
{
	swapContext(renderer);
	renderer->GetContext()->DrawIndexed(
		mesh->GetIndexesNumber(),0,0
		);
}

void RenderComponent::swapContext(Renderer* renderer)
{
	shader->SwapContext(renderer);
	mesh->SwapContext(renderer);
}
