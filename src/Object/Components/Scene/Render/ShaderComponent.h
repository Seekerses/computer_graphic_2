#pragma once

#include <string>
#include "d3d11.h"
#include "d3dcompiler.h"
#include "../../../../Renderer/Renderer.h"

class Renderer;
class MeshComponent;

class ShaderComponent
{
 private:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;

	static ID3DBlob* CompileShader(const std::wstring& location, const std::string& entrypoint, const std::string& target, const _D3D_SHADER_MACRO* macros, ID3DInclude* pInclude);

 public:
	ShaderComponent(Renderer* renderer, const std::wstring& location, D3D11_INPUT_ELEMENT_DESC* elementDesc, UINT inputElementsNum);
	ShaderComponent(Renderer* renderer, const std::wstring& location, D3D11_INPUT_ELEMENT_DESC* elementDesc, UINT inputElementsNum, const _D3D_SHADER_MACRO* macros);
	ShaderComponent(Renderer* renderer, const std::wstring& location, D3D11_INPUT_ELEMENT_DESC* elementDesc, UINT inputElementsNum, ID3DInclude* pInclude);
	ShaderComponent(Renderer* renderer, const std::wstring& location, D3D11_INPUT_ELEMENT_DESC* elementDesc, UINT inputElementsNum, const _D3D_SHADER_MACRO* macros, ID3DInclude* pInclude);

	ID3D11VertexShader* GetVertexShader() { return vertexShader; }
	ID3D11PixelShader* GetPixelShader() { return pixelShader; }
	ID3D11InputLayout* GetInputLayout() { return inputLayout; }

	void SwapContext(Renderer* renderer);
};
