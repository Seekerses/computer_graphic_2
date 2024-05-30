#include "ShaderComponent.h"
#include <iostream>

ShaderComponent::ShaderComponent(Renderer* renderer, const std::wstring& location, D3D11_INPUT_ELEMENT_DESC* elementDesc, UINT inputElementsNum)
	:
	ShaderComponent(renderer, location, elementDesc, inputElementsNum, nullptr, nullptr)
{
}

ShaderComponent::ShaderComponent(Renderer* renderer, const std::wstring& location, D3D11_INPUT_ELEMENT_DESC* elementDesc, UINT inputElementsNum, const _D3D_SHADER_MACRO* macros)
	:
	ShaderComponent(renderer, location, elementDesc, inputElementsNum, macros, nullptr)
{
}

ShaderComponent::ShaderComponent(Renderer* renderer, const std::wstring& location, D3D11_INPUT_ELEMENT_DESC* elementDesc, UINT inputElementsNum, ID3DInclude* pInclude)
	:
	ShaderComponent(renderer, location, elementDesc, inputElementsNum, nullptr, pInclude)
{
}

ShaderComponent::ShaderComponent(Renderer* renderer, const std::wstring& location, D3D11_INPUT_ELEMENT_DESC* elementDesc, UINT inputElementsNum, const _D3D_SHADER_MACRO* macros, ID3DInclude* pInclude)
{
	ID3DBlob* vertexBytecode = CompileShader(location, "VSMain", "vs_5_0", macros, pInclude);
	renderer->GetDevice()->CreateVertexShader(
		vertexBytecode->GetBufferPointer(),
		vertexBytecode->GetBufferSize(),
		nullptr,&vertexShader);

	ID3DBlob* pixelBytecode = CompileShader(location, "PSMain", "ps_5_0", macros, pInclude);
	renderer->GetDevice()->CreatePixelShader(
		pixelBytecode->GetBufferPointer(),
		pixelBytecode->GetBufferSize(),
		nullptr,&pixelShader);

	renderer->GetDevice()->CreateInputLayout(
		elementDesc,
		inputElementsNum,
		vertexBytecode->GetBufferPointer(),
		vertexBytecode->GetBufferSize(),
		&inputLayout);
}

ID3DBlob* ShaderComponent::CompileShader(const std::wstring& location, const std::string& entrypoint, const std::string& target, const _D3D_SHADER_MACRO* macros, ID3DInclude* pInclude)
{
	ID3DBlob* bytecode;
	ID3DBlob* errorVertexCode = nullptr;
	auto res = D3DCompileFromFile(location.c_str(),
		macros,
		pInclude,
		entrypoint.c_str(),
		target.c_str(),
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&bytecode,
		&errorVertexCode);

	if (FAILED(res))
	{
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode)
		{
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
			exit(1);
		}
			// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			std::cout << "Couldn't find shader file:" << location.c_str() << std::endl;
			exit(1);
		}
	}
	return bytecode;
}

void ShaderComponent::SwapContext(Renderer* renderer)
{
	// TODO minimize context swap
	ID3D11DeviceContext* context = renderer->GetContext();
	context->IASetInputLayout(inputLayout);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);
}
