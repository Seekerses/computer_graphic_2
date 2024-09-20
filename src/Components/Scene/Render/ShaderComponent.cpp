#include "ShaderComponent.h"
#include "RenderManager.h"

ShaderComponent::ShaderComponent(ShaderAsset* shaderAsset)
	:
	_shaderAsset(shaderAsset)
{
}

void ShaderComponent::SwapContext()
{
	// TODO minimize _context swap
	ID3D11DeviceContext* context = RenderManager::Get()->GetContext();
	context->IASetInputLayout(_shaderAsset->GetInputLayout());
	context->VSSetShader(_shaderAsset->GetVertexShader(), nullptr, 0);
	context->PSSetShader(_shaderAsset->GetPixelShader(), nullptr, 0);
}

