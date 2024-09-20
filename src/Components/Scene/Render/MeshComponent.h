#pragma once

#include "Types.h"
#include "Transform.h"
#include "MeshAsset.h"

class MeshComponent
{
 private:
	MeshAsset* _meshAsset;
	ID3D11Buffer* _vertexConstantBuffer = nullptr;
	ID3D11Buffer* _pixelConstantBuffer = nullptr;

	void updateVertexConstantBuffer(Transform transform);
	void updatePixelConstantBuffer(Color color);
 public:
	explicit MeshComponent(MeshAsset* meshAsset);
	~MeshComponent();
	[[nodiscard]] UINT GetIndexesNumber() const { return _meshAsset->GetIndicesNumber(); };
	void SwapContext(Transform transform, Color color);
};
