#pragma once

#include <string>
#include <d3d11.h>

class ShaderAsset
{
 private:
	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;
	ID3D11InputLayout* _inputLayout;

 public:
	ShaderAsset(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* inputLayout);
	ID3D11VertexShader* GetVertexShader() { return _vertexShader; }
	ID3D11PixelShader* GetPixelShader() { return _pixelShader; }
	ID3D11InputLayout* GetInputLayout() { return _inputLayout; }
};
