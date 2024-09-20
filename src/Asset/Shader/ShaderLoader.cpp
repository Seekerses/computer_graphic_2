#include "AssetManager.h"
#include <fstream>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <iostream>
#include "RenderManager.h"
#include "StringUtils.h"

// TODO add macros and pInclude handling (if really needed)
Id AssetManager::LoadShader(const std::filesystem::path& path) {
	RenderManager* renderer = RenderManager::Get();
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;

	ID3DBlob* vertexBytecode = CompileShader(path.generic_wstring(), "VSMain", "vs_5_0", nullptr, nullptr);
	renderer->GetDevice()->CreateVertexShader(
		vertexBytecode->GetBufferPointer(),
		vertexBytecode->GetBufferSize(),
		nullptr,&vertexShader);

	ID3DBlob* pixelBytecode = CompileShader(path.generic_wstring(), "PSMain", "ps_5_0", nullptr, nullptr);
	renderer->GetDevice()->CreatePixelShader(
		pixelBytecode->GetBufferPointer(),
		pixelBytecode->GetBufferSize(),
		nullptr,&pixelShader);

	// Creating input layout from description file
	std::ifstream shaderDescriptionFile;
	std::filesystem::path shaderDescriptionPath = path;
	shaderDescriptionPath = shaderDescriptionPath.replace_extension(".shader");
	shaderDescriptionFile.open(shaderDescriptionPath);
	std::string currentLine;

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements;
	std::vector<std::string*> semanticNames;
	while(std::getline(shaderDescriptionFile, currentLine)) {
		std::vector<std::string> inputElementString = split(currentLine, " ");
		auto* pSemanticName = new std::string(inputElementString[0]);
		semanticNames.emplace_back(pSemanticName);
		LPCSTR semanticName = pSemanticName->c_str();

		inputElements.push_back( D3D11_INPUT_ELEMENT_DESC{
			semanticName,
			std::stoul(inputElementString[1]),
			static_cast<DXGI_FORMAT>(std::stoi(inputElementString[2])),
			std::stoul(inputElementString[3]),
			std::stoul(inputElementString[4]),
			static_cast<D3D11_INPUT_CLASSIFICATION>(std::stoi(inputElementString[5])),
			std::stoul(inputElementString[6]) });
	}

	renderer->GetDevice()->CreateInputLayout(
		inputElements.data(),
		inputElements.size(),
		vertexBytecode->GetBufferPointer(),
		vertexBytecode->GetBufferSize(),
		&inputLayout);
	std::for_each(semanticNames.begin(), semanticNames.end(), [](std::string* name) { delete name; });

	Id shaderId = Id(path.filename().generic_wstring());
	_shaderAssets[shaderId] = new ShaderAsset(vertexShader, pixelShader, inputLayout);

	return shaderId;
}

ID3DBlob* AssetManager::CompileShader(const std::wstring& location, const std::string& entrypoint, const std::string& target, const _D3D_SHADER_MACRO* macros, ID3DInclude* pInclude)
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
		if (errorVertexCode)
		{
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
			exit(1);
		}
		else
		{
			std::cout << "Couldn't find shader file:" << location.c_str() << std::endl;
			exit(1);
		}
	}
	return bytecode;
}

D3D11_INPUT_ELEMENT_DESC AssetManager::ReadElementDesc(std::ifstream* fileStream) {
	std::string currentLine;
	std::string semanticName;
	UINT semanticIndex;
	uint16_t format;
	UINT inputSlot;
	UINT alignedByteOffset;
	uint8_t inputSlotClass;
	UINT instanceDataStepRate;

	*fileStream >> semanticName;
	*fileStream >> semanticIndex;
	*fileStream >> format;
	*fileStream >> inputSlot;
	*fileStream >> alignedByteOffset;
	*fileStream >> inputSlotClass;
	*fileStream >> instanceDataStepRate;


	return D3D11_INPUT_ELEMENT_DESC{
		semanticName.c_str(),
		semanticIndex,
		static_cast<DXGI_FORMAT>(format),
		inputSlot,
		alignedByteOffset,
		static_cast<D3D11_INPUT_CLASSIFICATION>(inputSlotClass),
		instanceDataStepRate };
}