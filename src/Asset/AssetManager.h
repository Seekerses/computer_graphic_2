#pragma once

#include <map>
#include <string>
#include <filesystem>
#include "SingletonManager.h"
#include "MeshAsset.h"
#include "ShaderAsset.h"
#include "Types.h"


class AssetManager : public SingletonManager
{
 private:
	static AssetManager* _instance;
	std::map<Id, MeshAsset*> _meshAssets;
	std::map<Id, ShaderAsset*> _shaderAssets;

	static ID3DBlob* CompileShader(
		const std::wstring& location,
		const std::string& entrypoint,
		const std::string& target,
		const _D3D_SHADER_MACRO* macros,
		ID3DInclude* pInclude);
	static D3D11_INPUT_ELEMENT_DESC ReadElementDesc(std::ifstream* file);

 public:
	AssetManager();
	~AssetManager() override = default;
	void Init();
	void Release() override;
	static AssetManager* Get();
	MeshAsset* GetMeshAsset(const Id& id);
	ShaderAsset* GetShaderAsset(const Id& id);
	Id LoadMesh(const std::filesystem::path& path);
	Id LoadShader(const std::filesystem::path& path);
};
