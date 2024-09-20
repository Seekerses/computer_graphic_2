#include "AssetManager.h"
#include <iostream>

void AssetManager::Init()
{
	// TODO support for subdirectory
	// Loading meshes
	std::cout << "Loading meshes..." << std::endl;
	for (const auto& entry : std::filesystem::directory_iterator("./Resources/Meshes/"))
	{
		if (entry.is_regular_file())
		{
#ifdef _DEBUG
			std::cout << entry.path().filename() << std::endl;
#endif
			LoadMesh(entry.path());
		}

	}
	std::cout << "Meshes loaded." << std::endl;

	// Loading shaders
	std::cout << "Loading shaders..." << std::endl;
	for (const auto& entry : std::filesystem::directory_iterator("./Resources/Shaders/"))
	{
		// load only .hlsl files
		if (entry.is_regular_file() && entry.path().extension().generic_string() == ".hlsl")
		{
#ifdef _DEBUG
			std::cout << entry.path().filename() << std::endl;
#endif
			LoadShader(entry.path());
		}
	}
	std::cout << "Shaders loaded." << std::endl;
	_instance = this;
}

void AssetManager::Release()
{

}

AssetManager* AssetManager::Get()
{
	return _instance;
}

MeshAsset* AssetManager::GetMeshAsset(const Id& id)
{
	return _meshAssets[id];
}

ShaderAsset* AssetManager::GetShaderAsset(const Id& id)
{
	return _shaderAssets[id];
}
AssetManager::AssetManager()
{
	AssetManager::_instance = this;
}
