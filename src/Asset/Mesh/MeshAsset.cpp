#include "MeshAsset.h"

#include <utility>
#include "RenderManager.h"

MeshAsset::MeshAsset(
	D3D_PRIMITIVE_TOPOLOGY topology,
	Vertex* vertices,
	UINT verticesNum,
	const UINT* indices,
	UINT indicesNum,
	std::vector<UINT> strides,
	std::vector<UINT> offsets)
	:
	_primitiveTopology(topology),
	_indicesNumber(indicesNum),
	_strides(std::move(strides)),
	_offsets(std::move(offsets))
{
	RenderManager* renderer = RenderManager::Get();

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

	renderer->GetDevice()->CreateBuffer(&vertexBufDesc, &vertexData, &_verticesBuffer);

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

	renderer->GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &_indicesBuffer);
}
MeshAsset::~MeshAsset()
{
	_verticesBuffer->Release();
	_indicesBuffer->Release();
}
