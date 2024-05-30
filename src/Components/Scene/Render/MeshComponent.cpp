#include "MeshComponent.h"

MeshComponent::MeshComponent(Renderer* renderer,
	D3D_PRIMITIVE_TOPOLOGY topology,
	Vertex* vertices,
	UINT verticesNum,
	const UINT* indices,
	UINT indicesNum,
	const UINT* strides,
	const UINT* offsets)
	:
	primitiveTopology(topology),
	indicesNumber(indicesNum),
	strides(strides),
	offsets(offsets)
{
	D3D11_BUFFER_DESC vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(Vertex) * verticesNum;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	renderer->GetDevice()->CreateBuffer(&vertexBufDesc, &vertexData, &verticesBuffer);

	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(UINT) * indicesNum;

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	renderer->GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &indicesBuffer);
}

MeshComponent::~MeshComponent() {
	delete strides;
	delete offsets;
}

void MeshComponent::SwapContext(Renderer* renderer)
{
	ID3D11DeviceContext* context = renderer->GetContext();
	context->IASetPrimitiveTopology(primitiveTopology);
	context->IASetIndexBuffer(indicesBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &verticesBuffer, strides, offsets);
}
