#include "MeshComponent.h"
#include "RenderManager.h"

MeshComponent::MeshComponent(MeshAsset* meshAsset) : _meshAsset(meshAsset)
{
	D3D11_BUFFER_DESC vertexConstBufDesc = {};
	vertexConstBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexConstBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vertexConstBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexConstBufDesc.MiscFlags = 0;
	vertexConstBufDesc.StructureByteStride = 0;
	vertexConstBufDesc.ByteWidth = sizeof(Transform);

	RenderManager::Get()->GetDevice()->CreateBuffer(&vertexConstBufDesc, nullptr, &_vertexConstantBuffer);

	D3D11_BUFFER_DESC pixelConstBufDesc = {};
	pixelConstBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	pixelConstBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pixelConstBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pixelConstBufDesc.MiscFlags = 0;
	pixelConstBufDesc.StructureByteStride = 0;
	pixelConstBufDesc.ByteWidth = sizeof(Color);

	RenderManager::Get()->GetDevice()->CreateBuffer(&pixelConstBufDesc, nullptr, &_pixelConstantBuffer);
}

MeshComponent::~MeshComponent()
{
	_vertexConstantBuffer->Release();
	_pixelConstantBuffer->Release();
}

void MeshComponent::SwapContext(Transform transform, Color color)
{
	RenderManager* renderer = RenderManager::Get();
	ID3D11DeviceContext* context = renderer->GetContext();
	updateVertexConstantBuffer(transform);
	updatePixelConstantBuffer(color);
	context->IASetPrimitiveTopology(_meshAsset->GetPrimitiveTopology());
	ID3D11Buffer* verticesBuffer = _meshAsset->GetVerticesBuffer();
	context->IASetVertexBuffers(0, 1,
		&verticesBuffer,_meshAsset->GetStrides(),_meshAsset->GetOffsets());
	context->IASetIndexBuffer(_meshAsset->GetIndicesBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->VSSetConstantBuffers(0, 1, &_vertexConstantBuffer);
	context->PSSetConstantBuffers(1, 1, &_pixelConstantBuffer);
}

void MeshComponent::updateVertexConstantBuffer(Transform transform)
{
	RenderManager* renderer = RenderManager::Get();
	transform.scale.x /= renderer->GetWindow()->GetRatio();
	D3D11_MAPPED_SUBRESOURCE data;
	renderer->GetContext()->Map(
		_vertexConstantBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0,
		&data);
	memcpy(data.pData, &transform, sizeof(Transform));
	renderer->GetContext()->Unmap(_vertexConstantBuffer, 0);
}

void MeshComponent::updatePixelConstantBuffer(Color color)
{
	RenderManager* renderer = RenderManager::Get();
	D3D11_MAPPED_SUBRESOURCE data;
	renderer->GetContext()->Map(
		_pixelConstantBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0,
		&data);
	memcpy(data.pData, &color, sizeof(Color));
	renderer->GetContext()->Unmap(_pixelConstantBuffer, 0);
}
