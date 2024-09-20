#pragma once

#include <d3dcommon.h>
#include <d3d11.h>
#include "Types.h"

class MeshAsset
{
 private:
	D3D_PRIMITIVE_TOPOLOGY _primitiveTopology;
	ID3D11Buffer* _verticesBuffer = nullptr;
	ID3D11Buffer* _indicesBuffer = nullptr;
	UINT _indicesNumber;
	const std::vector<UINT> _strides;
	const std::vector<UINT> _offsets;
 public:
	MeshAsset(D3D_PRIMITIVE_TOPOLOGY topology, Vertex* vertices, UINT vertexNum, const UINT* indices, UINT indicesNum, std::vector<UINT> strides, std::vector<UINT> offsets);
	~MeshAsset();
	[[nodiscard]] D3D_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() const {return _primitiveTopology; }
	[[nodiscard]] ID3D11Buffer* GetVerticesBuffer() const { return _verticesBuffer; }
	[[nodiscard]] ID3D11Buffer* GetIndicesBuffer() const { return _indicesBuffer; }
	[[nodiscard]] UINT GetIndicesNumber() const { return _indicesNumber; }
	[[nodiscard]] const UINT* GetStrides() const { return _strides.data(); }
	[[nodiscard]] const UINT* GetOffsets() const { return _offsets.data(); }
};
