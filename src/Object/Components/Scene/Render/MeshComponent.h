#pragma once

#include "../../../../Renderer/Renderer.h"
#include "../../../../Renderer/Vertex.h"

class ShaderComponent;
class Renderer;

class MeshComponent
{
 private:
	D3D_PRIMITIVE_TOPOLOGY primitiveTopology;
	ID3D11Buffer* verticesBuffer = nullptr;
	ID3D11Buffer* indicesBuffer = nullptr;
	UINT indicesNumber;
	const UINT* strides;
	const UINT* offsets;
 public:
	MeshComponent(Renderer* renderer, D3D_PRIMITIVE_TOPOLOGY topology, Vertex* vertices, UINT vertexNum, const UINT* indices, UINT indicesNum, const UINT* strides, const UINT* offsets);
	~MeshComponent();
	ID3D11Buffer* GetVertexBuffer() { return verticesBuffer; };
	ID3D11Buffer* GetIndexBuffer() { return indicesBuffer; };
	[[nodiscard]] UINT GetIndexesNumber() const { return indicesNumber; };
	[[nodiscard]] D3D_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() const { return primitiveTopology; };
	void SwapContext(Renderer* renderer);
};
