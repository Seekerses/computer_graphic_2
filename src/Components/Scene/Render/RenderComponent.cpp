#include "RenderComponent.h"
#include "RenderManager.h"

RenderComponent::RenderComponent(
	MeshComponent* _mesh,
	ShaderComponent* _shader) : mesh(_mesh), shader(_shader)
{

}

void RenderComponent::Draw(Transform transform, Color color)
{
	swapContext(transform, color);
	RenderManager::Get()->GetContext()->DrawIndexed(
		mesh->GetIndexesNumber(),0,0
		);
}

void RenderComponent::swapContext(Transform transform, Color color)
{
	mesh->SwapContext(transform, color);
	shader->SwapContext();
}
